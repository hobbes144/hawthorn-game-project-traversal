#include "precompiled.h"
#include "FirstPersonControllerComponent.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "RaycastManager.h"
#include "RigidBody.h"

void FirstPersonControllerComponent::initialize()
{

	//Checks to make sure the values have been initialized
	assert(input && "Input system is null!");
	assert(physicsBody && "Physics body is null!");
	assert(body && "Body (GameObject) is null!");
	assert(camera && "Camera is null!");

}

void FirstPersonControllerComponent::update(float deltaTime)
{

	if (playerState == Free) {

		//-----First Person Movement-----//
		//Temp States
		bool isSprinting = input->isKeyHeld(ActionKey[Sprint]);
		float forwardMotion = input->isKeyHeld(ActionKey[MoveForward]) - input->isKeyHeld(ActionKey[MoveBackward]);
		float lateralMotion = input->isKeyHeld(ActionKey[MoveRight]) - input->isKeyHeld(ActionKey[MoveLeft]);
		//Check if Grounded
		RaycastHit hitGround;
		isGrounded = RaycastManager::Instance().Raycast(
			Ray(body->getWorldTransform().getPosition(), -body->getUpVector()),
			hitGround, (body->getLocalScaling().z) * 2 + 0.25
		);

		//---Applying Movement Force---
		float movementForce = (isSprinting ? runForce : walkForce) * 100;
		float maxMovementSpeed = isSprinting ? maxRunSpeed : maxWalkSpeed;
		//Forward
		Vector3 forwardVector = body->getForwardVector();
		Vector3 forwardMotionVector = forwardVector * forwardMotion;
		//Lateral
		Vector3 rightVector = body->getRightVector();
		Vector3 lateralMotionVector = rightVector * lateralMotion;
		//Combine Forward and Lateral Movement and Apply Force
		Vector3 combinedMotionVector = forwardMotionVector + lateralMotionVector;
		if (combinedMotionVector.magnitude() > 0) {
			Vector3 movementVector = combinedMotionVector.normalized() * movementForce;
			physicsBody->applyForce(movementVector);
		}
		//Clamp Speed
		Vector3 pbVelocity = physicsBody->getVelocity();
		float pbVelocityMag = pbVelocity.magnitude();
		if (pbVelocityMag > maxMovementSpeed) {
			pbVelocity = (pbVelocity / pbVelocityMag) * maxMovementSpeed;
			physicsBody->setVelocity(pbVelocity);
		}

		debugCheck();

		//-----Handling Camera Movement-----//
		//Update Camera Position
		float cameraHeight = 1.5f;
		camera->setLocalPosition(body->getLocalPosition() + Vector3(0.0f, cameraHeight, 0.0f));
		//Get Mouse State Data
		MouseState mouseState = input->getMouseState();
		float mouseXDelta = 0.0f;
		float mouseYDelta = 0.0f;
		if (mouseState.deltaX != 0) {
			mouseXDelta = static_cast<float>(mouseState.deltaX) * mouseSensitivity;
		}
		if (mouseState.deltaY != 0) {
			mouseYDelta = static_cast<float>(mouseState.deltaY) * mouseSensitivity;
		}
		//Rotate Body
		Quaternion bodyRotation = body->getLocalRotation();
		float horizontalRotation = -mouseXDelta;  // Use the mouseXDelta to rotate around Y-axis (Horizontal)
		bodyRotation = bodyRotation * Quaternion::fromEuler(0.0f, horizontalRotation, 0.0f);
		body->setLocalRotation(bodyRotation);
		//Rotate Camera
		Quaternion cameraRotation = camera->getLocalRotation();
		float verticalRotation = -mouseYDelta;
		float currentPitch = cameraRotation.toEuler().x;
		float newPitch = currentPitch + verticalRotation;
		newPitch = std::clamp(newPitch, -89.0f, 89.0f);
		cameraRotation = Quaternion::fromEuler(newPitch, 0.0f, 0.0f);
		camera->setLocalRotation(cameraRotation);
		//Reset Mouse Delta
		input->resetMouseDelta();

		//-----Handle Jumping-----//
		//Track the last time the player was ground
		if (isGrounded) {
			lastTimeGrounded = 0.0f;
		}
		else {
			lastTimeGrounded += deltaTime;
		}
		//Track Last Time Jump was pressed
		if (input->isKeyPressed(ActionKey[Jump])) {
			lastTimeJumpPressed = 0.0f;
		}
		else {
			lastTimeJumpPressed += deltaTime;
		}
		//Apply Jump
		bool canJump = (isGrounded || lastTimeGrounded < coyoteTime) && (lastTimeJumpPressed < jumpBufferTime);
		if (canJump) {
			physicsBody->applyImpulse(Vector3(0.0f, jumpForce, 0.0f));

			// Prevent multiple jumps until grounded again
			lastTimeJumpPressed = jumpBufferTime + 1.0f;
			lastTimeGrounded = coyoteTime + 1.0f;
		}

		//-----Handle Sliding-----//
		slideCoolDownTimer += 0.01;
		if (slideCoolDownTimer >= slideCoolDown  && input->isKeyPressed(ActionKey[Slide])) {
			//Reset Timer
			slideCoolDownTimer = 0;
			
			//Apply a Slide Force
			slideVector = combinedMotionVector * slideForce;
			physicsBody->applyImpulse(slideVector);
			
			// Force Transition State
			playerState = Sliding;
		}

		//-----WallRunning Check-----//
		//Check Wall on Left
		Ray leftRay = Ray(body->getLocalPosition(), -body->getRightVector());
		RaycastHit leftWallHit;
		isLeftWall = RaycastManager::Instance().Raycast(leftRay, leftWallHit, 1.0f);
		//Check Wall on Right
		Ray rightRay = Ray(body->getLocalPosition(), body->getRightVector());
		RaycastHit rightWallHit;
		isRightWall = RaycastManager::Instance().Raycast(rightRay, rightWallHit, 1.0f);
		//If Not Grounded
		if (!isGrounded) {
			//If Left is a Wall and moving left
			if (isLeftWall && input->isKeyHeld(ActionKey[MoveLeft])) {
				playerState = WallRunning;
				wallNormal = leftWallHit.normal;
				isWallRunning = true;
				RigidBody* rb = static_cast<RigidBody*>(physicsBody);
				rb->usingGravity(false);
			}
			//If Right is a wall and moving right
			else if (isRightWall && input->isKeyHeld(ActionKey[MoveRight])) {
				playerState = WallRunning;
				wallNormal = rightWallHit.normal;
				isWallRunning = true;
				RigidBody* rb = static_cast<RigidBody*>(physicsBody);
				rb->usingGravity(false);
			}
		}

	}//End Free State
	else if (playerState == WallRunning) {

		//Continue performing Wall Checks
		Ray leftRay = Ray(body->getLocalPosition(), -body->getRightVector());
		RaycastHit leftWallHit;
		isLeftWall = RaycastManager::Instance().Raycast(leftRay, leftWallHit, 1.0f);
		//Check Wall on Right
		Ray rightRay = Ray(body->getLocalPosition(), body->getRightVector());
		RaycastHit rightWallHit;
		isRightWall = RaycastManager::Instance().Raycast(rightRay, rightWallHit, 1.0f);

		//Get the direction to move along the wall in
		Vector3 wallRunDirection = Vector3(0, 1, 0).cross(wallNormal);
		if (wallRunDirection.dot(physicsBody->getVelocity()) < 0) {
			wallRunDirection = -wallRunDirection; // Ensure correct movement direction
		}

		// Apply movement along the wall
		physicsBody->setVelocity(wallRunDirection * wallRunSpeed);

		//Jump Off of the Wall
		if (input->isKeyPressed(ActionKey[Jump])) {
			Vector3 jumpDirection = wallNormal * wallJumpForce + Vector3(0.0f, wallJumpForce, 0.0f);
			physicsBody->applyImpulse(jumpDirection);

			playerState = Free; // Exit wallrunning
			RigidBody* rb = static_cast<RigidBody*>(physicsBody);
			rb->usingGravity(true);
		}

		//Exit Wall Running if there is no more Wall
		if ((!isLeftWall && !isRightWall) || isGrounded || input->isKeyHeld(ActionKey[MoveBackward])) {
			playerState = Free;
			isWallRunning = false;
			RigidBody* rb = static_cast<RigidBody*>(physicsBody);
			rb->usingGravity(true);
		}

	}//End Wallrunning State
	else if (playerState = Sliding) {

		//Continue to Apply force?
		physicsBody->applyForce(slideVector);

		//increment slide timer
		slideCoolDownTimer += 0.01;

		if (slideCoolDownTimer >= (slideCoolDown/2)) {
			playerState = Free;
		}

	}//End Sliding State

}

void FirstPersonControllerComponent::shutdown()
{
}

std::shared_ptr<FirstPersonControllerComponent> 
	FirstPersonControllerComponent::setInputSystem(Input* _inputSystem)
{
	input = _inputSystem;
	return shared_from_this();
}

std::shared_ptr<FirstPersonControllerComponent> 
	FirstPersonControllerComponent::setPhysicsBody(PhysicsBody* _physicsBody)
{
	physicsBody = _physicsBody;
	return shared_from_this();
}

std::shared_ptr<FirstPersonControllerComponent> 
	FirstPersonControllerComponent::setBody(GameObject* _body)
{
	body = _body;
	return shared_from_this();
}

std::shared_ptr<FirstPersonControllerComponent> 
	FirstPersonControllerComponent::setCamera(Camera* _camera)
{
	camera = _camera;
	return shared_from_this();
}
 
std::shared_ptr<FirstPersonControllerComponent> 
	FirstPersonControllerComponent::setActionKey(Action _action, Key _key)
{
	ActionKey[_action] = _key;
	return shared_from_this();
}

void FirstPersonControllerComponent::debugCheck()
{

	if (input->isKeyPressed(ActionKey[Debug])) {
		std::cout << "Here" << std::endl;
	}

	Vector3 test = camera->getForwardVector();

}
