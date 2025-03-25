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

	//-----Input-----//
#pragma region Input
	bool isMovingForward = input->isKeyHeld(ActionKey[MoveForward]);
	bool isMovingBackward = input->isKeyHeld(ActionKey[MoveBackward]);
	bool isMovingLeft = input->isKeyHeld(ActionKey[MoveLeft]);
	bool isMovingRight = input->isKeyHeld(ActionKey[MoveRight]);
	bool isSprinting = input->isKeyHeld(ActionKey[Sprint]);
	float forwardMotion = input->isKeyHeld(ActionKey[MoveForward]) - input->isKeyHeld(ActionKey[MoveBackward]);
	float lateralMotion = input->isKeyHeld(ActionKey[MoveRight]) - input->isKeyHeld(ActionKey[MoveLeft]);
	bool isJumping = input->isKeyPressed(ActionKey[Jump]);
	bool isSliding = input->isKeyPressed(ActionKey[Slide]);
#pragma endregion
	//GamePad Input
#pragma region GamePad
	if (gp != nullptr) {
		if (gp->update()) {
			if (gp->leftStickY != 0) forwardMotion = gp->leftStickY;
			if (gp->leftStickX != 0) lateralMotion = gp->leftStickX;
			if (gp->isPressed(XINPUT_GAMEPAD_LEFT_THUMB)) 
				isSprinting = gp->isPressed(XINPUT_GAMEPAD_LEFT_THUMB);
			if (gp->isPressed(XINPUT_GAMEPAD_B))
				isJumping = gp->isPressed(XINPUT_GAMEPAD_B);
			if (gp->isPressed(XINPUT_GAMEPAD_X))
				isSliding = gp->isPressed(XINPUT_GAMEPAD_X);
		}
	}
#pragma endregion
	//-----Handling Camera Movement-----//
#pragma region Camera
	//Get Mouse State Data
	MouseState mouseState = input->getMouseState();
	float mouseXDelta = 0.0f;
	float mouseYDelta = 0.0f;
	if (mouseState.deltaX != 0) {
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
#pragma endregion

	//-----Grounded-----//
#pragma region Grounded
	RaycastHit hitGround;
	isGrounded = RaycastManager::Instance().Raycast(
		Ray(body->getWorldTransform().getPosition(), -body->getUpVector()),
		hitGround, (body->getWorldTransform().getScaling().z) * 2 + 0.25
	);
	if (isGrounded) {
		physicsBody->setDrag(0.3f);
	}
	else {
		physicsBody->setDrag(0.1f);
	}
#pragma endregion

	//-----Wall Checks-----//
#pragma region WallChecks
	Ray leftRay = Ray(body->getLocalPosition(), -body->getRightVector());
	Ray left45Ray = Ray(body->getLocalPosition(), (-body->getRightVector() + body->getForwardVector()).normalized());
	RaycastHit leftWallHit;
	isLeftWall = RaycastManager::Instance().Raycast(leftRay, leftWallHit, rayDist) ||
				 RaycastManager::Instance().Raycast(left45Ray, leftWallHit, rayDist);
	//Check Wall on Right
	Ray rightRay = Ray(body->getLocalPosition(), body->getRightVector());
	Ray right45Ray = Ray(body->getLocalPosition(), (body->getRightVector() + body->getForwardVector()).normalized());
	RaycastHit rightWallHit;
	isRightWall = RaycastManager::Instance().Raycast(rightRay, rightWallHit, rayDist) ||
				  RaycastManager::Instance().Raycast(right45Ray, rightWallHit, rayDist);

	if (isLeftWall || isRightWall) {
		//std::cout << "Here" << std::endl;
	}

	debugCheck();

#pragma endregion

	//-----Timers-----//
#pragma region Timers

	jumpCooldownTimer += deltaTime;
	wallrunCooldownTimer += deltaTime;

#pragma endregion

	//------------------------------STATES------------------------------//
	if (playerState == Free) {

		RigidBody* rb = static_cast<RigidBody*>(physicsBody);
		rb->usingGravity(true);

		//-----First Person Movement-----//
#pragma region FPC Movement
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
#pragma endregion

		//-----Handle Jumping-----//
#pragma region Jumping
		//Track the last time the player was ground
		if (isGrounded) {
			lastTimeGrounded = 0.0f;
		}
		else {
			lastTimeGrounded += deltaTime;
		}
		//Track Last Time Jump was pressed
		if (isJumping) {
			lastTimeJumpPressed = 0.0f;
		}
		else {
			lastTimeJumpPressed += deltaTime;
		}
		//Apply Jump
		bool canJump = (isGrounded || lastTimeGrounded < coyoteTime) 
					&& (lastTimeJumpPressed < jumpBufferTime) 
					&& (jumpCooldownTimer > jumpCooldown);
		if (canJump) {
			//Reset Cooldown Timer
			jumpCooldownTimer = 0.0f;
			//Apply Jump Force
			Vector3 currentVelocity = physicsBody->getVelocity();
			Vector3 newVelocity = Vector3(currentVelocity.x, jumpSpeed, currentVelocity.z);
			physicsBody->setVelocity(newVelocity);
			
			// Prevent multiple jumps until grounded again
			lastTimeJumpPressed = jumpBufferTime + 1.0f;
			lastTimeGrounded = coyoteTime + 1.0f;
		}
#pragma endregion

		//-----Handle Sliding-----//
#pragma region Sliding
		slideCoolDownTimer += 0.01;
		if (slideCoolDownTimer >= slideCoolDown  && isSliding) {
			//Reset Timer
			slideCoolDownTimer = 0;
			
			//Apply a Slide Force
			slideVector = combinedMotionVector * slideForce;
			physicsBody->setVelocity(slideVector);

			// Force Transition State
			playerState = Sliding;
		}
#pragma endregion

		//-----WallRunning Check-----//
#pragma region Wallrunning Check
		//If Wallrun off cooldown
		if (wallrunCooldownTimer > wallrunCooldown) {
			//If Not Grounded and moving forward
			if (!isGrounded && input->isKeyHeld(ActionKey[MoveForward])) {

				//If Left is a Wall and moving left
				if (isLeftWall && input->isKeyHeld(ActionKey[MoveLeft])) {
					playerState = WallRunning;
					runningWall = leftWallHit.object;
					wallNormal = leftWallHit.normal;
					isWallRunning = true;
				}
				//If Right is a wall and moving right
				else if (isRightWall && input->isKeyHeld(ActionKey[MoveRight])) {
					playerState = WallRunning;
					runningWall = rightWallHit.object;
					wallNormal = rightWallHit.normal;
					isWallRunning = true;
				}
			}
		}
#pragma endregion

	}//End Free State
	else if (playerState == WallRunning) {

		//Keep Timer at 0
		wallrunCooldownTimer = 0.0f;

		//Disable Gravity
  		RigidBody* rb = static_cast<RigidBody*>(physicsBody);
		rb->usingGravity(false);

		//Get the direction to move along the wall in
		Vector3 wallRunDirection = Vector3(0, 1, 0).cross(wallNormal);
		if (wallRunDirection.dot(physicsBody->getVelocity()) < 0) {
			wallRunDirection = -wallRunDirection; // Ensure correct movement direction
		}

		// Apply movement along the wall
		physicsBody->setVelocity(wallRunDirection * wallRunSpeed);

		const float wallWidth = (wallNormal * runningWall->getLocalScaling()).magnitude();
		const float playerWidth = 1.415;
		const float wallOffset = wallWidth/2 + playerWidth/2;

		// Maintain floating offset from the wall
		Vector3 currentPos = body->getLocalPosition();
		float distanceToWall = wallNormal.dot(currentPos - runningWall->getLocalPosition());
		Vector3 correctedPosition = currentPos - wallNormal * (distanceToWall - wallOffset);
		body->setLocalPosition(correctedPosition);

		//Jump Off of the Wall
		if (isJumping) {
			Vector3 currentVelocity = physicsBody->getVelocity();
			Vector3 wallJumpVelocity = wallNormal * wallJumpForce + Vector3(0.0f, wallJumpForce, 0.0f);
			Vector3 combinedVelocity = (currentVelocity + wallJumpVelocity) / 2.0f;
			physicsBody->setVelocity(combinedVelocity);

			playerState = Free; // Exit wallrunning
			isWallRunning = false;
			runningWall = nullptr;
		}

		//Exit Wall Running if there is no more Wall
		if ((!isLeftWall && !isRightWall) || isGrounded || !isMovingForward) {
  			playerState = Free;
			isWallRunning = false;
			runningWall = nullptr;
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

		if (isJumping) {
			//Apply Jump Force
			Vector3 currentVelocity = physicsBody->getVelocity();
			Vector3 newVelocity = Vector3(currentVelocity.x / 2, jumpSpeed * 1.5f, currentVelocity.z / 2);
			physicsBody->setVelocity(newVelocity);
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
FirstPersonControllerComponent::setGamePad(GamePad* _gp) {
	gp = _gp;
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
