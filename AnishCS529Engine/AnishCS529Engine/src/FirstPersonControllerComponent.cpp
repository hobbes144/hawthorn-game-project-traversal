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

//void FirstPersonControllerComponent::update(float deltaTime)
//{
//
//	//-----Handling Camera Movement-----//
//#pragma region Camera
//	//Get Mouse State Data
//	const MouseState mouseState = input->getMouseState();
//	float mouseXDelta = 0.0f;
//	float mouseYDelta = 0.0f;
//	if (mouseState.deltaX != 0) {
//		mouseXDelta = static_cast<float>(mouseState.deltaX) * mouseXSensitivity;
//		//Rotate Body
//		const Quaternion currentBodyRotation = body->getLocalRotation();
//		const Quaternion mouseRotation = Quaternion::axisAngleToQuaternion(Vector3(0.0f, 1.0f, 0.0f), (-mouseXDelta * 3.14159265f / 180.0f));
//		body->setLocalRotation(currentBodyRotation * mouseRotation);
//	}
//	if (mouseState.deltaY != 0) {
//		mouseYDelta = static_cast<float>(mouseState.deltaY) * mouseYSensitivity;
//		//Rotate Camera
//		const Vector3 currentEuler = camera->getLocalRotation().toEuler();
//		float newPitch = currentEuler.x + (-mouseYDelta * 3.14159265f / 180.0f);
//		newPitch = std::clamp(newPitch, -pitchLimit * (3.14159265f / 180.0f), pitchLimit * (3.14159265f / 180.0f)); // Convert degrees to radians
//		const Quaternion newCameraRotation = Quaternion::fromEuler(Vector3(newPitch, currentEuler.y, currentEuler.z));
//		camera->setLocalRotation(newCameraRotation);
//	}
//	//Reset Mouse Delta
//	input->resetMouseDelta();
//#pragma endregion
//
//
//	//-----Input-----//
//#pragma region Input
//	const bool isMovingForward = input->isKeyHeld(ActionKey[MoveForward]);
//	const bool isMovingBackward = input->isKeyHeld(ActionKey[MoveBackward]);
//	const bool isMovingLeft = input->isKeyHeld(ActionKey[MoveLeft]);
//	const bool isMovingRight = input->isKeyHeld(ActionKey[MoveRight]);
//
//	const float forwardMotion = isMovingForward - isMovingBackward;
//	const float lateralMotion = isMovingRight - isMovingLeft;
//
//	const bool isSprinting = input->isKeyHeld(ActionKey[Sprint]);
//	const bool isJumping = input->isKeyPressed(ActionKey[Jump]);
//	const bool isSliding = input->isKeyPressed(ActionKey[Slide]);
//#pragma endregion
//
//	//----Some Cached Variables----//
//	const Vector3 forwardVector = body->getForwardVector();
//	const Vector3 upVector = body->getUpVector();
//	const Vector3 rightVector = body->getRightVector();
//	const Transform bodyWorldTransform = body->getWorldTransform();
//	const Transform bodyLocalTransform = body->getLocalTransform();
//	const Vector3 currentPos = bodyLocalTransform.getPosition();
//	const float rayDist = parent->getWorldTransform().getScaling().x * 3;
//	RigidBody * const rb = static_cast<RigidBody*>(physicsBody);
//
//	//-----Grounded-----//
//#pragma region Grounded
//	RaycastHit hitGround;
//	isGrounded = RaycastManager::Instance().Raycast(
//		Ray(bodyWorldTransform.getPosition(), -upVector),
//		hitGround, (bodyWorldTransform.getScaling().z) * 2 + 0.25
//	);
//	if (isGrounded) {
//		anchorSurface = hitGround.object;
//		physicsBody->setDrag(0.3f);
//		if((playerState == Free))
//			rb->usingGravity(true);
//	}
//	else {
//		physicsBody->setDrag(0.1f);
//	}
//#pragma endregion
//
//	//-----Timers-----//
//#pragma region Timers
//
//	jumpCooldownTimer += deltaTime;
//	wallrunCooldownTimer += deltaTime;
//
//#pragma endregion
//
//	//------------------------------STATES------------------------------//
//	if (playerState == Free) {
//
//		//-----First Person Movement-----//
//#pragma region FPC Movement
//		//---Applying Movement Force---//
//		/* Todo : consider changing this for not grounded so that the player
//		* doesn't abuse physics too much.
//		*/
//		const float movementForce = (isSprinting ? runForce : walkForce) * 100.0f;
//		const float maxMovementSpeed = isSprinting ? maxRunSpeed : maxWalkSpeed;
//		//Forward
//		const Vector3 forwardMotionVector = forwardVector * forwardMotion;
//		//Lateral
//		const Vector3 lateralMotionVector = rightVector * lateralMotion;
//		//Combine Forward and Lateral Movement and Apply Force
//		const Vector3 combinedMotionVector = forwardMotionVector + lateralMotionVector;
//		if (combinedMotionVector.magnitude() > 0.0f) {
//			const Vector3 movementVector = combinedMotionVector.normalized() * movementForce;
//			physicsBody->applyForce(movementVector);
//		}
//#pragma endregion
//
//		//-----Handle Jumping-----//
//#pragma region Jumping
//		//Track the last time the player was ground
//		if (isGrounded) {
//			lastTimeGrounded = 0.0f;
//		}
//		else {
//			lastTimeGrounded += deltaTime;
//		}
//		//Track Last Time Jump was pressed
//		if (isJumping) {
//			lastTimeJumpPressed = 0.0f;
//		}
//		else {
//			lastTimeJumpPressed += deltaTime;
//		}
//		//Apply Jump
//		const bool canJump = (isGrounded || lastTimeGrounded < coyoteTime)
//					&& (lastTimeJumpPressed < jumpBufferTime)
//					&& (jumpCooldownTimer > jumpCooldown);
//		if (canJump) {
//			//Reset Cooldown Timer
//			jumpCooldownTimer = 0.0f;
//			//Apply Jump Force
//			const Vector3 currentVelocity = physicsBody->getVelocity();
//			const Vector3 newVelocity = Vector3(currentVelocity.x, jumpSpeed, currentVelocity.z);
//			physicsBody->setVelocity(newVelocity);
//
//			// Prevent multiple jumps until grounded again
//			lastTimeJumpPressed = jumpBufferTime + 1.0f;
//			lastTimeGrounded = coyoteTime + 1.0f;
//
//			/* Todo: Add logic to reparent here. */
//		}
//#pragma endregion
//
//		//-----Handle Sliding-----//
//#pragma region Sliding
//		slideCoolDownTimer += 0.01;
//		if (slideCoolDownTimer >= slideCoolDown && isSliding) {
//			//Reset Timer
//			slideCoolDownTimer = 0.0f;
//			
//			//Apply a Slide Force
//			slideVector = combinedMotionVector * slideForce;
//			if (slideVector.magnitude() == 0) {
//				slideVector = forwardVector * slideForce;
//			}
//			physicsBody->setVelocity(slideVector);
//
//			// Force Transition State
//			playerState = Sliding;
//		}
//#pragma endregion
//
//		//-----WallRunning Check-----//
//#pragma region Wallrunning Check
//		//If Wallrun off cooldown
//		if (wallrunCooldownTimer > wallrunCooldown) {
//			//If Not Grounded and moving forward
//			if (!isGrounded && isMovingForward) {
//
//				//-----Wall Checks-----//
//#pragma region WallChecks
//				const Ray leftRay = Ray(currentPos, -rightVector);
//				const Ray left45Ray = Ray(currentPos, (-rightVector + forwardVector).normalized());
//				RaycastHit leftWallHit;
//				isLeftWall = RaycastManager::Instance().Raycast(leftRay, leftWallHit, rayDist) ||
//					RaycastManager::Instance().Raycast(left45Ray, leftWallHit, rayDist);
//				//Check Wall on Right
//				const Ray rightRay = Ray(currentPos, rightVector);
//				const Ray right45Ray = Ray(currentPos, (rightVector + forwardVector).normalized());
//				RaycastHit rightWallHit;
//				isRightWall = RaycastManager::Instance().Raycast(rightRay, rightWallHit, rayDist) ||
//					RaycastManager::Instance().Raycast(right45Ray, rightWallHit, rayDist);
//
//				//if (isLeftWall || isRightWall) {
//				//	std::cout << "Here" << std::endl;
//				//}
//
//				debugCheck();
//
//#pragma endregion
//
//				//If Left is a Wall and moving left
//				if (isLeftWall && isMovingLeft) {
//					playerState = WallRunning;
//					runningWall = leftWallHit.object;
//					wallNormal = leftWallHit.normal;
//					anchorSurface = leftWallHit.object;
//					isWallRunning = true;
//				}
//				//If Right is a wall and moving right
//				else if (isRightWall && isMovingRight) {
//					playerState = WallRunning;
//					runningWall = rightWallHit.object;
//					wallNormal = rightWallHit.normal;
//					anchorSurface = rightWallHit.object;
//					isWallRunning = true;
//				}
//			}
//		}
//#pragma endregion
//
//	}//End Free State
//	else if (playerState == WallRunning) {
//		/* Todo: verify that this code works regardless of wall angle. */
//		/* Todo: consider wallrun max time */
//
//		//Keep Timer at 0
//		wallrunCooldownTimer = 0.0f;
//
//		//Disable Gravity
//		rb->usingGravity(false);
//
//		//Get the direction to move along the wall in
//		Vector3 wallRunDirection = Vector3(0, 1, 0).cross(wallNormal);
//		if (wallRunDirection.dot(physicsBody->getVelocity()) < 0.0f) {
//			wallRunDirection = -wallRunDirection; // Ensure correct movement direction
//		}
//
//		// Apply movement along the wall
//		physicsBody->setVelocity(wallRunDirection * wallRunSpeed);
//
//		const float wallWidth = (wallNormal * runningWall->getLocalScaling()).magnitude();
//		const float playerWidth = 1.415;
//		const float wallOffset = wallWidth/2 + playerWidth/2;
//
//		// Maintain floating offset from the wall
//		float distanceToWall = wallNormal.dot(currentPos - runningWall->getLocalPosition());
//		Vector3 correctedPosition = currentPos - wallNormal * (distanceToWall - wallOffset);
//		body->setLocalPosition(correctedPosition);
//
//		//Jump Off of the Wall
//		if (isJumping) {
//			Vector3 currentVelocity = physicsBody->getVelocity();
//			Vector3 wallJumpVelocity = wallNormal * wallJumpForce + Vector3(0.0f, wallJumpForce, 0.0f);
//			Vector3 combinedVelocity = (currentVelocity + wallJumpVelocity) / 2.0f;
//			physicsBody->setVelocity(combinedVelocity);
//
//			playerState = Free; // Exit wallrunning
//			isWallRunning = false;
//			runningWall = nullptr;
//		}
//
//		//Exit Wall Running if there is no more Wall
//		if ((!isLeftWall && !isRightWall) || isGrounded || !isMovingForward) {
//  		playerState = Free;
//			isWallRunning = false;
//			runningWall = nullptr;
//		}
//	} //End Wallrunning State
//	else if (playerState = Sliding) {
//
//		Vector3 driftVector = Vector3(0.0f, 0.0f, 0.0f);
//		Vector3 driftDirection = Vector3(-slideVector.z, 0.0f, slideVector.x).normalized();
//
//		if (isMovingLeft) {
//			driftVector = driftDirection * -0.2f;
//		}
//		if (isMovingRight) {
//			driftVector = driftDirection * 0.2f;
//		}
//
//		Vector3 newSlideVector = slideVector + driftVector;
//		newSlideVector = newSlideVector.normalized() * slideVector.magnitude();
//
//		//Continue to Maintain Velocity
//		physicsBody->setVelocity(newSlideVector);
//
//		//increment slide timer
//		slideCoolDownTimer += 0.01f;
//
//		if (slideCoolDownTimer >= (slideCoolDown/2.0f)) {
//			playerState = Free;
//		}
//
//		if (isJumping) {
//			//Apply Jump Force
//			Vector3 currentVelocity = physicsBody->getVelocity();
//			Vector3 newVelocity = Vector3(currentVelocity.x / 2, jumpSpeed * 1.5f, currentVelocity.z / 2);
//			physicsBody->setVelocity(newVelocity);
//			playerState = Free;
//		}
//
//	}//End Sliding State
//
//}


void FirstPersonControllerComponent::SwitchState(PlayerState originalState, PlayerState newState)
{
	switch (originalState)
	{
	case FirstPersonControllerComponent::Free:
		switch (newState)
		{
		case FirstPersonControllerComponent::WallRunning:
			FreeToWallRunning();
			return;
			break;
		case FirstPersonControllerComponent::Sliding:
			FreeToSliding();
			return;
			break;
		case FirstPersonControllerComponent::Grounded:
			FreeToGrounded();
			return;
			break;
		default:
			break;
		}
		break;
	case FirstPersonControllerComponent::WallRunning:
		switch (newState)
		{
		case FirstPersonControllerComponent::Free:
			WallRunningToFree();
			return;
			break;
		case FirstPersonControllerComponent::Grounded:
			WallRunningToGrounded();
			return;
			break;
		default:
			break;
		}
		break;
	case FirstPersonControllerComponent::Sliding:
		switch (newState)
		{
		case FirstPersonControllerComponent::Free:
			SlidingToFree();
			return;
			break;
		case FirstPersonControllerComponent::Grounded:
			SlidingToGrounded();
			return;
			break;
		default:
			break;
		}
		break;
	case FirstPersonControllerComponent::Grounded:
		switch (newState)
		{
		case FirstPersonControllerComponent::Free:
			GroundedToFree();
			return;
			break;
		case FirstPersonControllerComponent::Sliding:
			GroundedToSliding();
			return;
			break;
		case FirstPersonControllerComponent::Grounded:
			return;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	assert("Invalid state transition triggered for FPC" && false);
}

inline void FirstPersonControllerComponent::FreeToGrounded()
{
	unanchoredTime = 0.0f;
	hasSlidSinceAnchored = false;
	physicsBody->setDrag(anchoredDrag);
	physicsToAnchor();
	playerState = Grounded;
}

inline void FirstPersonControllerComponent::FreeToSliding()
{
	hasSlidSinceAnchored = true;
	sinceLastSlideTime = 0.0f;
	playerState = Sliding;
	
	physicsBody->setDrag(anchoredDrag);
}

inline void FirstPersonControllerComponent::FreeToWallRunning()
{
	unanchoredTime = 0.0f;
	hasSlidSinceAnchored = false;
	physicsBody->setDrag(anchoredDrag);

	physicsToAnchor();
	playerState = WallRunning;

	RigidBody* const rb = static_cast<RigidBody*>(physicsBody);
 	rb->usingGravity(false);
}

inline void FirstPersonControllerComponent::GroundedToFree()
{
	physicsBody->setDrag(airDrag);
	physicsToAir();
	playerState = Free;
}

inline void FirstPersonControllerComponent::GroundedToSliding()
{
	sinceLastSlideTime = 0.0f;
	physicsToAir();
	playerState = Sliding;
}

inline void FirstPersonControllerComponent::WallRunningToFree()
{
	physicsBody->setDrag(airDrag);

	physicsToAir();
	playerState = Free;
	RigidBody* const rb = static_cast<RigidBody*>(physicsBody);
	rb->usingGravity(true);
}

inline void FirstPersonControllerComponent::WallRunningToGrounded()
{

	physicsToAnchor();
	playerState = Grounded;
	RigidBody* const rb = static_cast<RigidBody*>(physicsBody);
	rb->usingGravity(true);
}

inline void FirstPersonControllerComponent::SlidingToGrounded()
{
	unanchoredTime = 0.0f;
	hasSlidSinceAnchored = false;
	physicsToAnchor();
	playerState = Grounded;
	physicsBody->setDrag(anchoredDrag);
}

inline void FirstPersonControllerComponent::SlidingToFree()
{
	physicsToAir();
	playerState = Free;
	physicsBody->setDrag(airDrag);
}

void FirstPersonControllerComponent::GroundedJump()
{

	//-----Handle Jumping-----//
#pragma region Jumping
	//Apply Jump
	//Reset Cooldown Timer
	sinceLastJumpTime = 0.0f;

	//Apply Jump Force
	const Vector3 currentVelocity = physicsBody->getVelocity();
	/* Todo: Consider adding forward momentum? */
	const Vector3 newVelocity = Vector3(currentVelocity.x, jumpSpeed, currentVelocity.z);
	physicsBody->setVelocity(newVelocity);

	AudioManager::instance().playSound("jump", Vector3(body->getLocalPosition()));

	// Prevent multiple jumps until grounded again
	sinceLastJumpPressedTime = jumpBufferTime + 1.0f;
#pragma endregion
}

void FirstPersonControllerComponent::SlidingJump()
{
	sinceLastJumpTime = 0.0f;
	sinceLastJumpPressedTime = jumpBufferTime + 1.0f;

	const float slideJumpMultiplier = 1.5f;

	Vector3 currentVelocity = physicsBody->getVelocity();
	Vector3 newVelocity = Vector3(currentVelocity.x / 2, jumpSpeed * slideJumpMultiplier, currentVelocity.z / 2);
	physicsBody->setVelocity(newVelocity);

	AudioManager::instance().playSound("jump", Vector3(body->getLocalPosition()));
}

void FirstPersonControllerComponent::WallrunningJump()
{
	sinceLastJumpTime = 0.0f;
	sinceLastJumpPressedTime = jumpBufferTime + 1.0f;

	const float wallJumpMultiplier = 2.0f;

	Vector3 currentVelocity = physicsBody->getVelocity();
	Vector3 wallJumpVelocity = anchorInfo.normal * wallJumpForce * wallJumpMultiplier + Vector3(0.0f, wallJumpForce * 2 * wallJumpMultiplier, 0.0f);
	Vector3 combinedVelocity = (currentVelocity + wallJumpVelocity) / 2.0f;
	physicsBody->setVelocity(combinedVelocity);

	AudioManager::instance().playSound("jump", Vector3(body->getLocalPosition()));
}

inline bool FirstPersonControllerComponent::passedCoyoteTime()
{
	return (unanchoredTime > coyoteTime);
}

inline bool FirstPersonControllerComponent::JumpBuffered()
{
	return (sinceLastJumpPressedTime < jumpBufferTime);
}

inline bool FirstPersonControllerComponent::CanJump()
{
	return (sinceLastJumpTime > jumpCooldown);
}

inline bool FirstPersonControllerComponent::SlideBuffered()
{
	return (sinceLastSlidePressedTime < slideBufferTime);
}

inline bool FirstPersonControllerComponent::CanSlide()
{
	return !hasSlidSinceAnchored && (sinceLastSlideTime > slideCoolDown);
}

bool FirstPersonControllerComponent::SlidingTimedOut()
{
	return (sinceLastSlideTime > slideEffectTime);
}

void FirstPersonControllerComponent::UpdateAnchorInfo()
{

#pragma region Grounded
	const Transform bodyWorldTransform = body->getWorldTransform();
	const Vector3 currentPos = bodyWorldTransform.getPosition();
	RaycastHit hitGround;
	/* Todo: This currently assumes z is down, fix for rotated objects. 
	* Consider using getFarthestExtent()?
	*/
	const bool isGrounded = RaycastManager::Instance().Raycast(
		Ray(currentPos, Vector3(0.0f, -1.0f, 0.0f)),
		hitGround, (bodyWorldTransform.getScaling().z) * 2 + 0.25
	);
	if (isGrounded) {
		anchorInfo.object = hitGround.object;
		anchorInfo.direction = 'd';
		anchorInfo.normal = hitGround.normal;
		return;
	}
#pragma endregion

	const Vector3 forwardVector = body->getForwardVector();
	const Vector3 rightVector = body->getRightVector();
	const float rayDist = parent->getWorldTransform().getScaling().x * 3;
	RaycastHit leftWallHit, rightWallHit;

#pragma region RightWallAndBoth
	if (anchorInfo.direction == 'r' || anchorInfo.direction == '0' || anchorInfo.direction == 'd') {
		const Ray rightRay = Ray(currentPos, rightVector);
		const Ray right45Ray = Ray(currentPos, (rightVector + forwardVector).normalized());
		const bool isRightWall = RaycastManager::Instance().Raycast(rightRay, rightWallHit, rayDist, {GameObject::RUNNABLE_WALL}) ||
			RaycastManager::Instance().Raycast(right45Ray, rightWallHit, rayDist, { GameObject::RUNNABLE_WALL });
		if (isRightWall) {
			anchorInfo.direction = 'r';
			anchorInfo.object = rightWallHit.object;
			anchorInfo.normal = rightWallHit.normal;
			return;
		}
		else {
			const Ray leftRay = Ray(currentPos, -rightVector);
			const Ray left45Ray = Ray(currentPos, (-rightVector + forwardVector).normalized());
			const bool isLeftWall = RaycastManager::Instance().Raycast(leftRay, leftWallHit, rayDist, { GameObject::RUNNABLE_WALL }) ||
				RaycastManager::Instance().Raycast(left45Ray, leftWallHit, rayDist, { GameObject::RUNNABLE_WALL });
			if (isLeftWall) {
				anchorInfo.direction = 'l';
				anchorInfo.object = leftWallHit.object;
				anchorInfo.normal = leftWallHit.normal;
				return;
			}
			else {
				anchorInfo.Reset();
				return;
			}
		}
	}
#pragma endregion
#pragma region LeftWall
	else if (anchorInfo.direction == 'l') {
		const Ray leftRay = Ray(currentPos, -rightVector);
		const Ray left45Ray = Ray(currentPos, (-rightVector + forwardVector).normalized());
		const bool isLeftWall = RaycastManager::Instance().Raycast(leftRay, leftWallHit, rayDist, { GameObject::RUNNABLE_WALL }) ||
			RaycastManager::Instance().Raycast(left45Ray, leftWallHit, rayDist, { GameObject::RUNNABLE_WALL });
		if (isLeftWall) {
			anchorInfo.object = leftWallHit.object;
			anchorInfo.normal = leftWallHit.normal;
			return;
		}
		else {
			const Ray rightRay = Ray(currentPos, rightVector);
			const Ray right45Ray = Ray(currentPos, (rightVector + forwardVector).normalized());
			const bool isRightWall = RaycastManager::Instance().Raycast(rightRay, rightWallHit, rayDist, { GameObject::RUNNABLE_WALL }) ||
				RaycastManager::Instance().Raycast(right45Ray, rightWallHit, rayDist, { GameObject::RUNNABLE_WALL });
			if (isRightWall) {
				anchorInfo.direction = 'r';
				anchorInfo.object = rightWallHit.object;
				anchorInfo.normal = rightWallHit.normal;
				return;
			}
			else {
				anchorInfo.Reset();
				return;
			}
		}
	}
#pragma endregion

}

void FirstPersonControllerComponent::physicsToAir()
{
	Transform currentWorld = parent->getWorldTransform();
	std::shared_ptr<GameObject> parentGameObject = std::dynamic_pointer_cast<GameObject>(parent->getParent());
	if (parentGameObject) {
		std::shared_ptr<PhysicsBody> anchorPhysics = parentGameObject->findComponent<PhysicsBody>();
		if (anchorPhysics) {
			physicsBody->setVelocity(anchorPhysics->getVelocity() + physicsBody->getVelocity());
			physicsBody->setAcceleration(anchorPhysics->getAcceleration() + physicsBody->getAcceleration());
			physicsBody->setForce(anchorPhysics->getAcceleration() + physicsBody->getAcceleration());
			physicsBody->setRotationalVelocity(anchorPhysics->getRotationalVelocity() + physicsBody->getRotationalVelocity());
			physicsBody->setRotationalAcceleration(anchorPhysics->getRotationalAcceleration() + physicsBody->getRotationalAcceleration());
			physicsBody->setRotationalForce(anchorPhysics->getRotationalAcceleration() + physicsBody->getRotationalAcceleration());
		}
	}
	parent->reparent(sceneRoot);
	parent->setWorldTransform(currentWorld);
}

void FirstPersonControllerComponent::physicsToAnchor()
{
	Transform currentWorld = parent->getWorldTransform();
	std::shared_ptr<GameObject> anchorGameObject = std::dynamic_pointer_cast<GameObject>(anchorInfo.object);
	if (anchorGameObject) {
		std::shared_ptr<PhysicsBody> anchorPhysics =
			anchorInfo.object->findComponent<PhysicsBody>();
		if (anchorPhysics) {
			physicsBody->setVelocity(physicsBody->getVelocity() - anchorPhysics->getVelocity());
			physicsBody->setAcceleration(physicsBody->getAcceleration() - anchorPhysics->getAcceleration());
			physicsBody->setForce(physicsBody->getAcceleration() - anchorPhysics->getAcceleration());
			physicsBody->setRotationalVelocity(physicsBody->getRotationalVelocity() - anchorPhysics->getRotationalVelocity());
			physicsBody->setRotationalAcceleration(physicsBody->getRotationalAcceleration() - anchorPhysics->getRotationalAcceleration());
			physicsBody->setRotationalForce(physicsBody->getRotationalAcceleration() - anchorPhysics->getRotationalAcceleration());
		}
		parent->reparent(anchorInfo.object);
	}
	else {
		parent->reparent(sceneRoot);
	}
	parent->setWorldTransform(currentWorld);
}

void FirstPersonControllerComponent::update(float deltaTime)
{

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
	//Mouse
	float mouseXDelta = 0.0f;
	float mouseYDelta = 0.0f;
#pragma endregion

	//GamePad Input
#pragma region GamePad
	if ( gp != nullptr ) {
		if ( gp->update() ) {
			if ( gp->leftStickY != 0 ) {
				forwardMotion = gp->leftStickY;
				if ( forwardMotion > 0 ) {
					isMovingForward = true;
					isMovingBackward = false;
				}
				else if ( forwardMotion < 0 ) {
					isMovingForward = false;
					isMovingBackward = true;
				}
			}
			if ( gp->leftStickX != 0 ) {
				lateralMotion = gp->leftStickX;
				if ( lateralMotion < 0 ) {
					isMovingLeft = true;
					isMovingBackward = false;
				}
				else if ( forwardMotion < 0 ) {
					isMovingLeft = false;
					isMovingBackward = true;
				}
			}
			if ( gp->rightStickX != 0 ) {
				mouseXDelta = static_cast<float>( gp->rightStickX ) * 2;
				Quaternion currentBodyRotation = body->getLocalRotation();
				Quaternion mouseRotation = Quaternion::axisAngleToQuaternion(Vector3(0.0f, 1.0f, 0.0f), ( -mouseXDelta * 3.14159265f / 180.0f ));
				body->setLocalRotation(currentBodyRotation * mouseRotation);
			}
			if ( gp->rightStickY != 0 ) {
				mouseYDelta = -static_cast<float>( gp->rightStickY ) * 2;
				//Rotate Camera
				Quaternion currentCameraRoation = camera->getLocalRotation();
				Vector3 currentEuler = currentCameraRoation.toEuler();
				float newPitch = currentEuler.x + ( -mouseYDelta * 3.14159265f / 180.0f );
				newPitch = std::clamp(newPitch, -pitchLimit * ( 3.14159265f / 180.0f ), pitchLimit * ( 3.14159265f / 180.0f )); // Convert degrees to radians
				Quaternion newCameraRotation = Quaternion::fromEuler(Vector3(newPitch, currentEuler.y, currentEuler.z));
				camera->setLocalRotation(newCameraRotation);
			}
			if ( gp->isPressed(XINPUT_GAMEPAD_LEFT_THUMB) )
				isSprinting = gp->isPressed(XINPUT_GAMEPAD_LEFT_THUMB);
			if ( gp->isPressed(XINPUT_GAMEPAD_B) )
				isJumping = gp->isPressed(XINPUT_GAMEPAD_B);
			if ( gp->isPressed(XINPUT_GAMEPAD_X) )
				isSliding = gp->isPressed(XINPUT_GAMEPAD_X);
		}
	}
#pragma endregion

	//-----Handling Camera Movement-----//
#pragma region Camera
	//Get Mouse State Data
	const MouseState mouseState = input->getMouseState();
	if ( mouseState.deltaX != 0 ) {
		mouseXDelta = static_cast<float>( mouseState.deltaX ) * mouseXSensitivity;
		//Rotate Body
		const Quaternion currentBodyRotation = body->getLocalRotation();
		const Quaternion mouseRotation = Quaternion::axisAngleToQuaternion(Vector3(0.0f, 1.0f, 0.0f), ( -mouseXDelta * 3.14159265f / 180.0f ));
		body->setLocalRotation(currentBodyRotation * mouseRotation);
	}
	if ( mouseState.deltaY != 0 ) {
		mouseYDelta = static_cast<float>( mouseState.deltaY ) * mouseYSensitivity;
		//Rotate Camera
		const Vector3 currentEuler = camera->getLocalRotation().toEuler();
		float newPitch = currentEuler.x + ( -mouseYDelta * 3.14159265f / 180.0f );
		newPitch = std::clamp(newPitch, -pitchLimit * ( 3.14159265f / 180.0f ), pitchLimit * ( 3.14159265f / 180.0f )); // Convert degrees to radians
		const Quaternion newCameraRotation = Quaternion::fromEuler(Vector3(newPitch, currentEuler.y, currentEuler.z));
		camera->setLocalRotation(newCameraRotation);
	}
	//Reset Mouse Delta
	input->resetMouseDelta();
#pragma endregion

	if (isJumping) sinceLastJumpPressedTime = 0.0f;
	if (isSliding) sinceLastSlidePressedTime = 0.0f;

	//----Some Cached Variables----//
	const Vector3 forwardVector = body->getForwardVector();
	const Vector3 upVector = body->getUpVector();
	const Vector3 rightVector = body->getRightVector();
	const Transform bodyWorldTransform = body->getWorldTransform();
	const Vector3 currentPos = bodyWorldTransform.getPosition();
	const float rayDist = parent->getWorldTransform().getScaling().x * 2.5f;
	RigidBody* const rb = static_cast<RigidBody*>(physicsBody);

	UpdateAnchorInfo();

	//------------------------------STATES------------------------------//
	//-----State Switching-----//
#pragma region StateSwitching
	if (playerState == Free) {
		if (sinceLastJumpTime > jumpCooldown && anchorInfo.direction == 'd')
			SwitchState(Free, Grounded);
		else if (SlideBuffered() && CanSlide())
		{
			if (!forwardMotion && !lateralMotion) {
				slideVector = forwardVector * slideForce;
			}
			const Vector3 forwardMotionVector = forwardVector * forwardMotion;
			//Lateral
			const Vector3 lateralMotionVector = rightVector * lateralMotion;
			//Combine Forward and Lateral Movement and Apply Force
			const Vector3 combinedMotionVector = forwardMotionVector + lateralMotionVector;
			slideVector = combinedMotionVector * slideForce;
			if (slideVector.magnitude() == 0) {
				slideVector = forwardVector * slideForce;
			}
			physicsBody->setVelocity(slideVector);
			AudioManager::instance().playSound("slide", Vector3(body->getLocalPosition()));
			SwitchState(Free, Sliding);
		}
		else if (anchorInfo.direction != '0' && isMovingForward) { //If anchor is not the ground and moving forward
			if ((isMovingLeft && anchorInfo.direction == 'l')
				|| (isMovingRight && anchorInfo.direction == 'r')) { // If anchor is a wall
				if (anchorInfo.isLargestFace()) { //if wall face is the big side
					const float maxAngle = 45.0f;
					const float maxDotThreshold = std::cos(maxAngle * (3.14159265f / 180.0f));
					float dotProduct = std::abs(forwardVector.dot(anchorInfo.normal));
					if (dotProduct > -maxDotThreshold && dotProduct < maxDotThreshold) { // If angle is within limits (not too steep)
						SwitchState(Free, WallRunning);
					}
				}

			}
		}
	}

	else if (playerState == Grounded) {
		/* If coyote time, preserve state */
		if (passedCoyoteTime()) {
			SwitchState(Grounded, Free);
		}
		else if (JumpBuffered())
		{
			SwitchState(Grounded, Free);
			GroundedJump();
		}
		else if (SlideBuffered() && CanSlide())
		{
			if (!forwardMotion && !lateralMotion) {
				slideVector = forwardVector * slideForce;
			}
			const Vector3 forwardMotionVector = forwardVector * forwardMotion;
			//Lateral
			const Vector3 lateralMotionVector = rightVector * lateralMotion;
			//Combine Forward and Lateral Movement and Apply Force
			const Vector3 combinedMotionVector = forwardMotionVector + lateralMotionVector;
			slideVector = combinedMotionVector * slideForce;
			if (slideVector.magnitude() == 0) {
				slideVector = forwardVector * slideForce;
			}
			physicsBody->setVelocity(slideVector);
			AudioManager::instance().playSound("slide", Vector3(body->getLocalPosition()));
			SwitchState(Grounded, Sliding);
		}
		else if (anchorInfo.direction != 'd' && anchorInfo.direction != '0')
		{
			SwitchState(Grounded, Free);
			if ((isMovingLeft && anchorInfo.direction == 'l')
				|| (isMovingRight && anchorInfo.direction == 'r'))
				SwitchState(Free, WallRunning);
		}
	}

	else if (playerState == WallRunning) {
		if (passedCoyoteTime()) {
			SwitchState(WallRunning, Free);
		}
		else if (anchorInfo.direction == 'd')
			SwitchState(WallRunning, Grounded);
		else if (!isMovingForward || anchorInfo.direction == '0')
			SwitchState(WallRunning, Free);
		else if (isJumping) {
			SwitchState(WallRunning, Free);
			WallrunningJump();
		}
	}

	else if (playerState == Sliding) {
		if (SlidingTimedOut())
			SwitchState(Sliding, (anchorInfo.direction == 'd') ? Grounded : Free);
		else if (isJumping)
		{
			SwitchState(Sliding, Free);
			SlidingJump();
		}
	}

#pragma endregion

	//-----State Processing-----//
#pragma region StateProcessing

	//-----First Person Ground Movement-----//
#pragma region GroundMovement
	if (playerState == Grounded) {

		const float movementForce = (isSprinting ? runForceMultiplier : 1.0f) * walkForce * 100.0f;
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
			if ( isSprinting ) {
				AudioManager::instance().playSound("run", Vector3(body->getLocalPosition()));
			}
			else {
				AudioManager::instance().playSound("walk", Vector3(body->getLocalPosition()));
			}
		}
	}
#pragma endregion


	//-----First Person Air Movement-----//
#pragma region FreeMovement
	else if (playerState == Free) {
		//---Applying Movement Force---//
		const float movementForce = (isSprinting ? runForceMultiplier : 1.0f) * walkForce * 50.0f;
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
	}
#pragma endregion

	//-----Handle Sliding-----//
#pragma region Sliding
	else if (playerState == Sliding) {
		//Apply a Slide Force
		//Forward
		/*
		// Force based
		slideVector = combinedMotionVector * slideForce * 10.0f;
		physicsBody->applyForce(slideVector);
		*/

		Vector3 driftVector = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 driftDirection = Vector3(-slideVector.z, 0.0f, slideVector.x).normalized();

		if ( isMovingLeft ) {
			driftVector = driftDirection * -0.2f;
		}
		if ( isMovingRight ) {
			driftVector = driftDirection * 0.2f;
		}

		Vector3 newSlideVector = slideVector + driftVector;
		newSlideVector = newSlideVector.normalized() * slideVector.magnitude();

		//Continue to Maintain Velocity
		physicsBody->setVelocity(newSlideVector);
	}
#pragma endregion

	//-----Handle Wallrunning-----//
#pragma region WallRunning
	else if (playerState == WallRunning) {
		/* Todo: verify that this code works regardless of wall angle. */
		/* Todo: consider wallrun max time */

		//Get the direction to move along the wall in
		Vector3 wallRunDirection = Vector3(0, 1, 0).cross(anchorInfo.normal);
		if (wallRunDirection.dot(physicsBody->getVelocity()) < 0.0f) {
			wallRunDirection = -wallRunDirection; // Ensure correct movement direction
		}

		// Apply movement along the wall
		physicsBody->setVelocity(wallRunDirection * wallRunSpeed);

		const float wallWidth = (anchorInfo.normal * anchorInfo.object->getWorldScaling()).magnitude();
		const float playerWidth = 1.415;
		const float wallOffset = wallWidth / 2 + playerWidth / 2;

		// Maintain floating offset from the wall
		float distanceToWall = anchorInfo.normal.dot(currentPos - anchorInfo.object->getWorldPosition());
		Vector3 correctedPosition = currentPos - anchorInfo.normal * (distanceToWall - wallOffset);
		body->setWorldPosition(correctedPosition);

	} //End Wallrunning State
#pragma endregion

#pragma endregion


	//-----Timers-----//
#pragma region Timers

	if ((anchorInfo.direction != 'd') && playerState != WallRunning)
		unanchoredTime += deltaTime;

	sinceLastJumpTime += deltaTime;
	sinceLastJumpPressedTime += deltaTime;
	sinceLastSlideTime += deltaTime;
	sinceLastSlidePressedTime += deltaTime;

#pragma endregion
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

std::shared_ptr<FirstPersonControllerComponent> FirstPersonControllerComponent::setState(PlayerState state)
{
	SwitchState(playerState, state);
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
	FirstPersonControllerComponent::setSceneRoot(std::shared_ptr<Node> root)
{
	sceneRoot = root;
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
	return (anchorInfo.direction == 'd');
}

std::shared_ptr<GameObject> FirstPersonControllerComponent::getAnchoredSurface()
{
	return anchorInfo.object;
}

void FirstPersonControllerComponent::debugCheck()
{
	if (input->isKeyPressed(ActionKey[Debug])) {
		std::cout << "Here" << std::endl;
	}
}
