/*!****************************************************************************
 * \file   RigidBody.cpp
 * \author Daoming Wang (KeitherJinn@outlook.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 *
 *****************************************************************************/
#include "precompiled.h"

#include "RigidBody.h"

float RigidBody::gravity = 9.8f;

/*!****************************************************************************
 * \brief The constructor or RigidBody class
 *****************************************************************************/
RigidBody::RigidBody() :
	PhysicsBody(), useGravity(false),
	elasticity(0.5f),
	listener(nullptr),
	freezePositionX(false), freezePositionY(false), freezePositionZ(false),
	freezeRotationX(false), freezeRotationY(false), freezeRotationZ(false) {}

/*!****************************************************************************
 * \brief If is using Gravity
 *
 * ## Usage:
 *
 * This is to be used when the object needs to use gravity.
 *
 * \param value If the object is using gravity or not
 * \return \b std::shared_ptr<RigidBody> Self
 *****************************************************************************/
std::shared_ptr<RigidBody> RigidBody::usingGravity(bool value) {
	useGravity = value;

	return std::static_pointer_cast<RigidBody>(shared_from_this());
}

/*!****************************************************************************
 * \brief All the Freezing Position functions are not yet implemented
 *
 * \param value
 * \return \b
 *****************************************************************************/
std::shared_ptr<RigidBody> RigidBody::freezingPositionX(bool value) {
	freezePositionX = value;

	return std::static_pointer_cast<RigidBody>(shared_from_this());
}

std::shared_ptr<RigidBody> RigidBody::freezingPositionY(bool value) {
	freezePositionY = value;

	return std::static_pointer_cast<RigidBody>(shared_from_this());
}

std::shared_ptr<RigidBody> RigidBody::freezingPositionZ(bool value) {
	freezePositionZ = value;

	return std::static_pointer_cast<RigidBody>(shared_from_this());
}

std::shared_ptr<RigidBody> RigidBody::freezingRotationX(bool value) {
	freezeRotationX = value;

	return std::static_pointer_cast<RigidBody>(shared_from_this());
}

std::shared_ptr<RigidBody> RigidBody::freezingRotationY(bool value) {
	freezeRotationY = value;

	return std::static_pointer_cast<RigidBody>(shared_from_this());
}

std::shared_ptr<RigidBody> RigidBody::freezingRotationZ(bool value) {
	freezeRotationZ = value;

	return std::static_pointer_cast<RigidBody>(shared_from_this());
}

void RigidBody::initialize()
{
	listener = new CollisionListener(this->parent);

	listener->setCallback(onRBCollide);
}

/*!****************************************************************************
 * \brief Update the GameObject and its related collision
 *
 * ## Usage:
 *
 * This should be called in the main loop to update the object's position
 * according to all external forces acting upon it.
 *
 * ## Note:
 *
 * This is not used in the update call since physics is usually handled
 * separately to ensure consistent physics.
 *
 * Look into how collision Shape and the PhysicsManager system work to ensure
 * collisions are handled correctly.
 *
 * \param deltaTime
 *****************************************************************************/
void RigidBody::integrate(float deltaTime) {

	if (useGravity) {
		applyForce(Vector3(0.0f, -gravity*100.0f, 0.0f));
	}

	PhysicsBody::integrate(deltaTime);

}

/*!****************************************************************************
 * \brief A callback function needed to be set up to collisionListener for the
 *		  collision Event of RigidBody
 *
 * \param obj1 object collided
 * \param obj2 another object collided
 * \param point contact point
 *****************************************************************************/
void onRBCollide(std::shared_ptr<GameObject> obj1,
	std::shared_ptr<GameObject> obj2, const Vector3& point) {
	const std::shared_ptr<RigidBody>& RB1 = obj1->findComponent<RigidBody>();
	const std::shared_ptr<RigidBody>& RB2 = obj2->findComponent<RigidBody>();

	if (!RB1 || !RB2) return;
	if (PhysicsManager::Instance().isHandledCollision(RB1, RB2))
		return;

	Vector3 final = point;
	const Vector3& RB1Position = obj1->getWorldTransform().getPosition();
	const Vector3& RB2Position = obj2->getWorldTransform().getPosition();

	Vector3 velocity = RB1->getVelocity();
	Vector3 velocity2 = RB2->getVelocity();

	float e = std::min(RB1->getElasticity(), RB2->getElasticity());

	if (RB1->getIsStatic() && RB1->getIsStatic()) {
		PhysicsManager::Instance().addHandledCollision(RB1, RB2);
		return;
	}

	Vector3 contactVector = (final - RB1Position);
	Vector3 normal = RB1->getShape()->getNormalAtVector(contactVector.normalized());
	contactVector *= normal;
	Vector3 RB1Extent = RB1->getShape()->getSurfacePoint(contactVector.normalized());
	//Vector3 RB1Point = RB1->getShape()->getSurfacePoint(contactVector.normalized());

	Vector3 correction = (RB1Extent - contactVector) * normal;

	if (correction < Vector3(1e-16f)) {
		PhysicsManager::Instance().addHandledCollision(RB1, RB2);
		return;
	}

	Vector3 impulse =
		(RB1->getVelocity() - RB2->getVelocity()) *
		(1 + e) *
		(
			(RB1->getMass() * RB2->getMass())
			/
			(RB1->getMass() + RB2->getMass())
		);

	if (RB1->getIsStatic()) {
		obj2->setWorldPosition(RB2Position + (correction * 2));
		RB2->setVelocity(Vector3());
		RB2->applyForce(impulse);
	}
	else if (RB2->getIsStatic()) {
		obj1->setWorldPosition(RB1Position - (correction * 2));
		RB1->setVelocity(Vector3());
		RB1->applyForce(impulse);
	}
	else {
		RB1->applyForce(-impulse);
		RB2->applyForce(impulse);

		if (correction > Vector3(1e-16f)) {
			obj1->setWorldPosition(RB1Position - correction);
			RB1->updateShapePosition();
			obj2->setWorldPosition(RB2Position + correction);
			RB2->updateShapePosition();
		}
	}

	PhysicsManager::Instance().addHandledCollision(RB1, RB2);

	return;
}

/* Getters */
