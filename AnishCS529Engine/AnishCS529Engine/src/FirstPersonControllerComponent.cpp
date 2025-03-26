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

	//-----Handling Camera Movement-----//
#pragma region Camera
	//Get Mouse State Data
	const MouseState mouseState = input->getMouseState();
	float mouseXDelta = 0.0f;
	float mouseYDelta = 0.0f;
	if (mouseState.deltaX != 0) {
		mouseXDelta = static_cast<float>(mouseState.deltaX) * mouseXSensitivity;
		//Rotate Body
		const Quaternion currentBodyRotation = body->getLocalRotation();
		const Quaternion mouseRotation = Quaternion::axisAngleToQuaternion(Vector3(0.0f, 1.0f, 0.0f), (-mouseXDelta * 3.14159265f / 180.0f));
		body->setLocalRotation(currentBodyRotation * mouseRotation);
	}
	if (mouseState.deltaY != 0) {
		mouseYDelta = static_cast<float>(mouseState.deltaY) * mouseYSensitivity;
		//Rotate Camera
		const Vector3 currentEuler = camera->getLocalRotation().toEuler();
		float newPitch = currentEuler.x + (-mouseYDelta * 3.14159265f / 180.0f);
		newPitch = std::clamp(newPitch, -pitchLimit * (3.14159265f / 180.0f), pitchLimit * (3.14159265f / 180.0f)); // Convert degrees to radians
		const Quaternion newCameraRotation = Quaternion::fromEuler(Vector3(newPitch, currentEuler.y, currentEuler.z));
		camera->setLocalRotation(newCameraRotation);
	}
	//Reset Mouse Delta
	input->resetMouseDelta();
#pragma endregion


	//-----Input-----//
#pragma region Input
	const bool isMovingForward = input->isKeyHeld(ActionKey[MoveForward]);
	const bool isMovingBackward = input->isKeyHeld(ActionKey[MoveBackward]);
	const bool isMovingLeft = input->isKeyHeld(ActionKey[MoveLeft]);
	const bool isMovingRight = input->isKeyHeld(ActionKey[MoveRight]);

	const float forwardMotion = isMovingForward - isMovingBackward;
	const float lateralMotion = isMovingRight - isMovingLeft;

	const bool isSprinting = input->isKeyHeld(ActionKey[Sprint]);
	const bool isJumping = input->isKeyPressed(ActionKey[Jump]);
	const bool isSliding = input->isKeyPressed(ActionKey[Slide]);
#pragma endregion

	//----Some Cached Variables----//
	const Vector3 forwardVector = body->getForwardVector();
	const Vector3 upVector = body->getUpVector();
	const Vector3 rightVector = body->getRightVector();
	const Transform bodyWorldTransform = body->getWorldTransform();
	const Transform bodyLocalTransform = body->getLocalTransform();
	const Vector3 currentPos = bodyLocalTransform.getPosition();
	const float rayDist = parent->getWorldTransform().getScaling().x * 3;
	RigidBody * const rb = static_cast<RigidBody*>(physicsBody);

	//-----Grounded-----//
#pragma region Grounded
	RaycastHit hitGround;
	isGrounded = RaycastManager::Instance().Raycast(
		Ray(bodyWorldTransform.getPosition(), -upVector),
		hitGround, (bodyWorldTransform.getScaling().z) * 2 + 0.25
	);
	if (isGrounded) {
		anchorSurface = hitGround.object;
		physicsBody->setDrag(0.3f);
		if((playerState == Free))
			rb->usingGravity(true);
	}
	else {
		physicsBody->setDrag(0.1f);
	}
#pragma endregion

	//-----Timers-----//
#pragma region Timers

	jumpCooldownTimer += deltaTime;
	wallrunCooldownTimer += deltaTime;

#pragma endregion

	//------------------------------STATES------------------------------//
	if (playerState == Free) {

		//-----First Person Movement-----//
#pragma region FPC Movement
		//---Applying Movement Force---//
		/* Todo : consider changing this for not grounded so that the player
		* doesn't abuse physics too much.
		*/
		const float movementForce = (isSprinting ? runForce : walkForce) * 100.0f;
		const float maxMovementSpeed = isSprinting ? maxRunSpeed : maxWalkSpeed;
		//Forward
		const Vector3 forwardMotionVector = forwardVector * forwardMotion;
		//Lateral
		const Vector3 lateralMotionVector = rightVector * lateralMotion;
		//Combine Forward and Lateral Movement and Apply Force
		const Vector3 combinedMotionVector = forwardMotionVector + lateralMotionVector;
		if (combinedMotionVector.magnitude() > 0.0f) {
			const Vector3 movementVector = combinedMotionVector.normalized() * movementForce;
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
		const bool canJump = (isGrounded || lastTimeGrounded < coyoteTime) 
					&& (lastTimeJumpPressed < jumpBufferTime) 
					&& (jumpCooldownTimer > jumpCooldown);
		if (canJump) {
			//Reset Cooldown Timer
			jumpCooldownTimer = 0.0f;
			//Apply Jump Force
			const Vector3 currentVelocity = physicsBody->getVelocity();
			const Vector3 newVelocity = Vector3(currentVelocity.x, jumpSpeed, currentVelocity.z);
			physicsBody->setVelocity(newVelocity);
			
			// Prevent multiple jumps until grounded again
			lastTimeJumpPressed = jumpBufferTime + 1.0f;
			lastTimeGrounded = coyoteTime + 1.0f;

			/* Todo: Add logic to reparent here. */
		}
#pragma endregion

		//-----Handle Sliding-----//
#pragma region Sliding
		slideCoolDownTimer += 0.01;
		if (slideCoolDownTimer >= slideCoolDown && isSliding) {
			//Reset Timer
			slideCoolDownTimer = 0.0f;
			
			//Apply a Slide Force
			slideVector = combinedMotionVector * slideForce;
			if (slideVector.magnitude() == 0) {
				slideVector = forwardVector * slideForce;
			}
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
			if (!isGrounded && isMovingForward) {

				//-----Wall Checks-----//
#pragma region WallChecks
				const Ray leftRay = Ray(currentPos, -rightVector);
				const Ray left45Ray = Ray(currentPos, (-rightVector + forwardVector).normalized());
				RaycastHit leftWallHit;
				isLeftWall = RaycastManager::Instance().Raycast(leftRay, leftWallHit, rayDist) ||
					RaycastManager::Instance().Raycast(left45Ray, leftWallHit, rayDist);
				//Check Wall on Right
				const Ray rightRay = Ray(currentPos, rightVector);
				const Ray right45Ray = Ray(currentPos, (rightVector + forwardVector).normalized());
				RaycastHit rightWallHit;
				isRightWall = RaycastManager::Instance().Raycast(rightRay, rightWallHit, rayDist) ||
					RaycastManager::Instance().Raycast(right45Ray, rightWallHit, rayDist);

				//if (isLeftWall || isRightWall) {
				//	std::cout << "Here" << std::endl;
				//}

				debugCheck();

#pragma endregion

				//If Left is a Wall and moving left
				if (isLeftWall && isMovingLeft) {
					playerState = WallRunning;
					runningWall = leftWallHit.object;
					wallNormal = leftWallHit.normal;
					anchorSurface = leftWallHit.object;
					isWallRunning = true;
				}
				//If Right is a wall and moving right
				else if (isRightWall && isMovingRight) {
					playerState = WallRunning;
					runningWall = rightWallHit.object;
					wallNormal = rightWallHit.normal;
					anchorSurface = rightWallHit.object;
					isWallRunning = true;
				}
			}
		}
#pragma endregion

	}//End Free State
	else if (playerState == WallRunning) {
		/* Todo: verify that this code works regardless of wall angle. */
		/* Todo: consider wallrun max time */

		//Keep Timer at 0
		wallrunCooldownTimer = 0.0f;

		//Disable Gravity
		rb->usingGravity(false);

		//Get the direction to move along the wall in
		Vector3 wallRunDirection = Vector3(0, 1, 0).cross(wallNormal);
		if (wallRunDirection.dot(physicsBody->getVelocity()) < 0.0f) {
			wallRunDirection = -wallRunDirection; // Ensure correct movement direction
		}

		// Apply movement along the wall
		physicsBody->setVelocity(wallRunDirection * wallRunSpeed);

		const float wallWidth = (wallNormal * runningWall->getLocalScaling()).magnitude();
		const float playerWidth = 1.415;
		const float wallOffset = wallWidth/2 + playerWidth/2;

		// Maintain floating offset from the wall
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
	} //End Wallrunning State
	else if (playerState = Sliding) {

		Vector3 driftVector = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 driftDirection = Vector3(-slideVector.z, 0.0f, slideVector.x).normalized();

		if (isMovingLeft) {
			driftVector = driftDirection * -0.2f;
		}
		if (isMovingRight) {
			driftVector = driftDirection * 0.2f;
		}

		Vector3 newSlideVector = slideVector + driftVector;
		newSlideVector = newSlideVector.normalized() * slideVector.magnitude();

		//Continue to Maintain Velocity
		physicsBody->setVelocity(newSlideVector);

		//increment slide timer
		slideCoolDownTimer += 0.01f;

		if (slideCoolDownTimer >= (slideCoolDown/2.0f)) {
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

/*!****************************************************************************
 * \brief Set Camera rotation to a specific angle
 * 
 * This function can be used to specifically set the camera to look at a
 * specific X and Y axis rotation. Note, this is disabled for Z axis.
 * 
 * \param rotation Pitch and Yaw to set the camera to, as specified by the
 * first two elements of the Vector3.
 * \return \b std::shared_ptr<FirstPersonControllerComponent> Self.
 *****************************************************************************/
std::shared_ptr<FirstPersonControllerComponent> 
	FirstPersonControllerComponent::setCameraRotation(Vector3 rotation)
{
	body->setLocalRotation(
		body->getLocalRotation() * 
		Quaternion::fromEuler(Vector3(0.0f, rotation.y, 0.0f)));

	Quaternion currentCameraRoation = camera->getLocalRotation();
	Vector3 currentEuler = currentCameraRoation.toEuler();
	float newPitch = currentEuler.x + rotation.x;
	newPitch = std::clamp(
		newPitch, 
		-pitchLimit * (3.14159265f / 180.0f), 
		pitchLimit * (3.14159265f / 180.0f)); // Convert degrees to radians
	Quaternion newCameraRotation = Quaternion::fromEuler(
		Vector3(newPitch, currentEuler.y, currentEuler.z));
	camera->setLocalRotation(newCameraRotation);
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
