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
	const float rayDist = parent->getWorldTransform().getScaling().x * 3; 

	if (playerState == Free) {

		RigidBody* rb = static_cast<RigidBody*>(physicsBody);
		rb->usingGravity(true);

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

		debugCheck();

		if (isGrounded) {
			physicsBody->setDrag(0.3f);
		}
		else {
			physicsBody->setDrag(0.0f);
		}

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

		//-----Handling Camera Movement-----//
		//Get Mouse State Data
		MouseState mouseState = input->getMouseState();
		float mouseXDelta = 0.0f;
		float mouseYDelta = 0.0f;
		if (mouseState.deltaX != 0) {
			debugCheck();
			mouseXDelta = static_cast<float>(mouseState.deltaX) * mouseXSensitivity;
			//Rotate Body
			Quaternion currentBodyRotation = body->getLocalRotation();
			Quaternion mouseRotation = Quaternion::axisAngleToQuaternion(Vector3(0.0f, 1.0f, 0.0f), (-mouseXDelta * 3.14159265f / 180.0f));
			body->setLocalRotation(currentBodyRotation * mouseRotation);
		}
		if (mouseState.deltaY != 0) {
			mouseYDelta = static_cast<float>(mouseState.deltaY) * mouseYSensitivity;
			//Rotate Camera
			Quaternion currentCameraRoation = camera->getLocalRotation();
			Vector3 currentEuler = currentCameraRoation.toEuler();
			float newPitch = currentEuler.x + (-mouseYDelta * 3.14159265f / 180.0f);
			newPitch = std::clamp(newPitch, -pitchLimit * (3.14159265f / 180.0f), pitchLimit * (3.14159265f / 180.0f)); // Convert degrees to radians
			Quaternion newCameraRotation = Quaternion::fromEuler(Vector3(newPitch, currentEuler.y, currentEuler.z));
			camera->setLocalRotation(newCameraRotation);
		}
		
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
			//Apply Jump Force
			Vector3 currentVelocity = physicsBody->getVelocity();
			Vector3 newVelocity = Vector3(currentVelocity.x, jumpSpeed, currentVelocity.z);
			physicsBody->setVelocity(newVelocity);
			
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
			physicsBody->setVelocity(slideVector);

			// Force Transition State
			playerState = Sliding;
		}

		//-----WallRunning Check-----//
		//If Not Grounded and moving forward
		if (!isGrounded && input->isKeyHeld(ActionKey[MoveForward])) {
			
			//Wall Checks
			//Continue performing Wall Checks
			Ray leftRay = Ray(body->getLocalPosition(), -body->getRightVector());
			Ray left45Ray = Ray(body->getLocalPosition(), (-body->getRightVector() + body->getForwardVector()).normalized());
			RaycastHit leftWallHit;
			isLeftWall = RaycastManager::Instance().Raycast(leftRay, leftWallHit, rayDist) || RaycastManager::Instance().Raycast(left45Ray, leftWallHit, 2.0f);
			//Check Wall on Right
			Ray rightRay = Ray(body->getLocalPosition(), body->getRightVector());
			Ray right45Ray = Ray(body->getLocalPosition(), (body->getRightVector() + body->getForwardVector()).normalized());
			RaycastHit rightWallHit;
			isRightWall = RaycastManager::Instance().Raycast(rightRay, rightWallHit, rayDist) || RaycastManager::Instance().Raycast(right45Ray, rightWallHit, 2.0f);
			
			//If Left is a Wall and moving left
			if (isLeftWall && input->isKeyHeld(ActionKey[MoveLeft])) {
				playerState = WallRunning;
				runningWall = leftWallHit.object;
				wallNormal = leftWallHit.normal;
				isWallRunning = true;
				RigidBody* rb = static_cast<RigidBody*>(physicsBody);
				rb->usingGravity(false);
			}
			//If Right is a wall and moving right
			else if (isRightWall && input->isKeyHeld(ActionKey[MoveRight])) {
				playerState = WallRunning;
				runningWall = rightWallHit.object;
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
		Ray left45Ray = Ray(body->getLocalPosition(), (-body->getRightVector() + body->getForwardVector()) * 0.5f);
		RaycastHit leftWallHit;
		isLeftWall = RaycastManager::Instance().Raycast(leftRay, leftWallHit, 2.0f) || RaycastManager::Instance().Raycast(left45Ray, leftWallHit, 2.0f);
		//Check Wall on Right
		Ray rightRay = Ray(body->getLocalPosition(), body->getRightVector());
		Ray right45Ray = Ray(body->getLocalPosition(), (body->getRightVector() + body->getForwardVector()) * 0.5f);
		RaycastHit rightWallHit;
		isRightWall = RaycastManager::Instance().Raycast(rightRay, rightWallHit, 2.0f) || RaycastManager::Instance().Raycast(right45Ray, rightWallHit, 2.0f);

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
			isWallRunning = false;
			runningWall = nullptr;
			RigidBody* rb = static_cast<RigidBody*>(physicsBody);
			rb->usingGravity(true);
		}

		//Exit Wall Running if there is no more Wall
		if ((!isLeftWall && !isRightWall) || isGrounded || !input->isKeyHeld(ActionKey[MoveForward])) {
			playerState = Free;
			isWallRunning = false;
			runningWall = nullptr;
			RigidBody* rb = static_cast<RigidBody*>(physicsBody);
			rb->usingGravity(true);
		}

	}//End Wallrunning State
	else if (playerState = Sliding) {

		Vector3 driftVector = Vector3(0.0f, 0.0f, 0.0f);  
		Vector3 driftDirection = Vector3(-slideVector.z, 0.0f, slideVector.x).normalized();

		if (input->isKeyHeld(ActionKey[MoveLeft])) {
			driftVector = driftDirection * -0.2f;
		}
		if (input->isKeyHeld(ActionKey[MoveRight])) {
			driftVector = driftDirection * 0.2f;
		}

		Vector3 newSlideVector = slideVector + driftVector;
		newSlideVector = newSlideVector.normalized() * slideVector.magnitude();

		//Continue to Maintain Velocity
		physicsBody->setVelocity(newSlideVector);

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

bool FirstPersonControllerComponent::getIsGrounded()
{
	return isGrounded;
}

std::shared_ptr<GameObject> FirstPersonControllerComponent::getRunningWall()
{
	return runningWall;
}

void FirstPersonControllerComponent::debugCheck()
{

	if (input->isKeyPressed(ActionKey[Debug])) {
		std::cout << "Here" << std::endl;
	}

}
