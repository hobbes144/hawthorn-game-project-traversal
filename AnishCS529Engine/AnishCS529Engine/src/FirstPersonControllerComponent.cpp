#include "precompiled.h"
#include "FirstPersonControllerComponent.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "RaycastManager.h"

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
	//Temp States
	bool isSprinting = input->isKeyHeld(ActionKey[Sprint]);
	float forwardMotion = input->isKeyHeld(ActionKey[MoveForward]) - input->isKeyHeld(ActionKey[MoveBackward]);
	float lateralMotion = input->isKeyHeld(ActionKey[MoveRight]) - input->isKeyHeld(ActionKey[MoveLeft]);
	
	RaycastHit hitGround;
	isGrounded = RaycastManager::Instance().Raycast(
		Ray(body->getWorldTransform().getPosition(), -body->getUpVector()),
		hitGround, (body->getLocalScaling().z / 2) + 0.25
	);

	//---Applying Movement Force---
	float movementForce = isSprinting ? runForce : walkForce;
	float maxMovementSpeed = isSprinting ? maxRunSpeed : maxWalkSpeed;
	//Forward
	Vector3 forwardVector = body->getForwardVector();
	Vector3 forwardMotionVector = forwardVector * forwardMotion;
	//Lateral
	Vector3 rightVector = body->getRightVector();
	Vector3 lateralMotionVector = rightVector * lateralMotion;
	//Combine Forward and Lateral Movement and Apply Force
	Vector3 movementVector = (forwardMotionVector + lateralMotionVector).normalized() * movementForce;
	physicsBody->applyForce(movementVector);
	//Clamp Speed
	Vector3 pbVelocity = physicsBody->getVelocity();
	float pbVelocityMag = pbVelocity.magnitude();
	if (pbVelocityMag > maxMovementSpeed) {
		pbVelocity = (pbVelocity / pbVelocityMag) * maxMovementSpeed;
		physicsBody->setVelocity(pbVelocity);
	}

	//---Handling Camera Movement---
	//Update Camera Position
	float cameraHeight = 0.5f;
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
	//Yaw Camera
	camera->Rotate(mouseXDelta, Vector3(0,1,0));
	//Pitch Camera
	camera->Rotate(mouseYDelta, camera->getRightVector());
	//Reset Mouse Delta
	input->resetMouseDelta();

}

void FirstPersonControllerComponent::shutdown()
{
}

std::shared_ptr<FirstPersonControllerComponent> 
	FirstPersonControllerComponent::setActionKey(Action _action, Key _key)
{
	ActionKey[_action] = _key;
	return shared_from_this();
}
