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

#include "PhysicsManager.h"
#include "RigidBody.h"
#include <cmath>

const float gravity = 9.8f;

/*!****************************************************************************
 * \brief The constructor or RigidBody class
 *****************************************************************************/
RigidBody::RigidBody() :
	PhysicsBody(), useGravity(false),
	listener(new CollisionListener(this->parent)),
	freezePositionX(false), freezePositionY(false), freezePositionZ(false),
	freezeRotationX(false), freezeRotationY(false), freezeRotationZ(false) {

	listener->setCallback(onRBCollide);
}

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
		applyForce(Vector3(0.0, -gravity, 0.0));
	}

	PhysicsBody::integrate(deltaTime);

}

bool belongsToXY(Vector3 vert1, Vector3 vert2, Vector3 target) {
	if (vert1.x > target.x && vert1.y > target.y) {
		if (vert2.x < target.x && vert2.y < target.y) {
			return true;
		}
	}
	return false;
}

bool belongsToYZ(Vector3 vert1, Vector3 vert2, Vector3 target) {
	if (vert1.z > target.z && vert1.y > target.y) {
		if (vert2.z < target.z && vert2.y < target.y) {
			return true;
		}
	}
	return false;
}

bool belongsToXZ(Vector3 vert1, Vector3 vert2, Vector3 target) {
	if (vert1.x > target.x && vert1.z > target.z) {
		if (vert2.x < target.x && vert2.z < target.z) {
			return true;
		}
	}
	return false;
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

	std::shared_ptr<RigidBody> RB, RB2;

	if (obj1->findComponent<RigidBody>()->getIsStatic()) {
		RB2 = obj1->findComponent<RigidBody>();
		RB = obj2->findComponent<RigidBody>();
	}
	else {
		RB = obj1->findComponent<RigidBody>();
		RB2 = obj2->findComponent<RigidBody>();
	}

	if (RB && RB2) {
		std::cout << "RBcollided between " << RB->getParent()->getName()
			<< " and " << RB2->getParent()->getName() << std::endl;
		Vector3 velocity = RB->getVelocity();
		Vector3 negVelocity = Vector3(-RB->getVelocity().x,
							  -RB->getVelocity().y, -RB->getVelocity().z);
		Vector3 Acc = RB->getAcceleration();
		Vector3 Force = RB->getForce();

		Vector3 scaleRB = RB->getParent()->getLocalScaling();
		Vector3 PosRB = RB->getParent()->getLocalPosition() * scaleRB;
		Vector3 scaleRB2 = RB2->getParent()->getLocalScaling();
		Vector3 PosRB2 = RB2->getParent()->getLocalPosition() * scaleRB2;

		double dx = (scaleRB.x + scaleRB2.x) / 2;
		double dy = (scaleRB.y + scaleRB2.y) / 2;
		double dz = (scaleRB.z + scaleRB2.z) / 2;

		double actualdisX = abs(PosRB.x - PosRB2.x);
		double actualdisY = abs(PosRB.y - PosRB2.y);
		double actualdisZ = abs(PosRB.z - PosRB2.z);

		bool signX = Force.x != 0;
		bool signY = Force.y != 0;
		bool signZ = Force.z != 0;

		Vector3 restore = Vector3(dx - actualdisX, dy - actualdisY, dz - actualdisZ);

		float cntX = abs(restore.x / negVelocity.x);
		float cntY = abs(restore.y / negVelocity.y);
		float cntZ = abs(restore.z / negVelocity.z);

		double cnt = fmin(cntX, fmin(cntY, cntZ));

		restore = Vector3(negVelocity.x * cnt, negVelocity.y * cnt, negVelocity.z * cnt);

		std::cout << restore.x << " " << restore.y << " " << restore.z;

		if (restore.x == NAN || restore.y == NAN || restore.z == NAN) restore = Vector3(0, 0, 0);

		if (RB2->getIsStatic()) {
			RB->setVelocity(Vector3(velocity.x*signX, velocity.y*signY, velocity.z*signZ));
			RB->getParent()->setLocalPosition(PosRB / scaleRB + restore*1.1 / scaleRB);
		}
		else {
			RB->applyForce(negVelocity * 100 * RB2->getMass());
			RB->getParent()->setLocalPosition(PosRB / scaleRB + restore / scaleRB / 2);
			RB2->applyForce(velocity * 100 * RB->getMass());
			RB2->getParent()->setLocalPosition(PosRB2 / scaleRB2 - restore / scaleRB2 / 2);
		}
	}
	return;
}

/* Getters */