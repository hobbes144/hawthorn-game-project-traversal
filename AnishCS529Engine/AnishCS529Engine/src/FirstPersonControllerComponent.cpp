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
	int forwardMotion = input->isKeyHeld(ActionKey[MoveForward]) - input->isKeyHeld(ActionKey[MoveBackward]);
	int lateralMotion = input->isKeyHeld(ActionKey[MoveRight]) - input->isKeyHeld(ActionKey[MoveLeft]);
	isGrounded = RaycastManager::Raycast();

	//---Applying Movement Force---
	float movementForce = isSprinting ? runForce : walkForce;
	float maxMovementSpeed = isSprinting ? maxRunSpeed : maxWalkSpeed;
	//Forward
	Vector3 forwardVector = body->getForwardVector();
	Vector3 forwardMotionVector = forwardMotion * forwardVector;
	//Lateral
	Vector3 rightVector = body->getRightVector();
	Vector3 lateralMotionVector = lateralMotion * rightVector;
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

	//---Camera Movement---


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
