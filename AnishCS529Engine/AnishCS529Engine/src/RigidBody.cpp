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

const float gravity = -9.8f;

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
	if (!parent->isEnabled()) return;
	if (!isStatic) {

		Vector3 netFriction;
		if (velocity.magnitude() > 0) {
			netFriction =
				velocity.normalized() * velocity.magnitude() * -drag;
		}
		else {
			netFriction = Vector3(0.0f, 0.0f, 0.0f);
		}


		acceleration = acceleration + (force + netFriction) * inverseMass;
		velocity = velocity + (acceleration * deltaTime);

		Vector3 newPosition =
			parent->getLocalPosition() + (velocity * deltaTime);
		parent->setLocalPosition(newPosition);
	}

	// Update collision shape
	if (collisionShape) {
		// Since we don't have direct access to transform,
		// we'll create a Transform object with the current state
		Transform currentTransform;
		currentTransform.setPosition(parent->getLocalPosition());
		currentTransform.setRotation(parent->getLocalRotation());
		currentTransform.setScaling(parent->getLocalScaling());

		// TODO: What else do you have to update during the integration
		// besides the parent's position?
		// implement here ->:
		collisionShape->update(currentTransform);
	}

	// Reset force accumulator
	if (useGravity) force = Vector3(0.0f, gravity, 0.0f);
	else force = Vector3(0, 0, 0);
	acceleration = Vector3(0, 0, 0);
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
		Vector3 velocity2 = RB2->getVelocity();
		Vector3 negVelocity2 = Vector3(-RB2->getVelocity().x,
							   -RB2->getVelocity().y, -RB2->getVelocity().z);
		Vector3 halfForce = Vector3(RB->getForce().x / 2,
							RB->getForce().y / 2, RB->getForce().z / 2);
		Vector3 negHalfForce = Vector3(-RB->getForce().x / 2,
							   -RB->getForce().y / 2, -RB->getForce().z / 2);
		Vector3 negForce = Vector3(-RB->getForce().x,
						   -RB->getForce().y, -RB->getForce().z);
		Vector3 halfForce2 = Vector3(RB2->getForce().x / 2,
							 RB2->getForce().y / 2, RB2->getForce().z / 2);
		Vector3 negHalfForce2 = Vector3(-RB2->getForce().x / 2,
								-RB2->getForce().y / 2, -RB2->getForce().z / 2);
		Vector3 negForce2 = Vector3(-RB2->getForce().x,
							-RB2->getForce().y, -RB2->getForce().z);

		Vector3 scaleRB = RB->getParent()->getLocalScaling();

		Vector3 PosRB = RB->getParent()->getLocalPosition() * scaleRB;

		std::cout << "posRB=" << PosRB.x << ", " << PosRB.y << ", " << PosRB.z << std::endl;
		std::cout << "scaleRB=" << scaleRB.x << ", " << scaleRB.y << ", " << scaleRB.z << std::endl;
		Vector3 scaleRB2 = RB2->getParent()->getLocalScaling();

		Vector3 PosRB2 = RB2->getParent()->getLocalPosition() * scaleRB2;

		double dx = (scaleRB.x + scaleRB2.x) / 2;
		double dy = (scaleRB.y + scaleRB2.y) / 2;
		double dz = (scaleRB.z + scaleRB2.z) / 2;

		double actualdisX = abs(PosRB.x - PosRB2.x);
		double actualdisY = abs(PosRB.y - PosRB2.y);
		double actualdisZ = abs(PosRB.z - PosRB2.z);

		Vector3 vertices[8];
		vertices[0] = Vector3(PosRB2.x + scaleRB2.x, PosRB2.y + scaleRB2.y, PosRB2.z + scaleRB2.z);
		vertices[1] = Vector3(PosRB2.x - scaleRB2.x, PosRB2.y + scaleRB2.y, PosRB2.z + scaleRB2.z);
		vertices[2] = Vector3(PosRB2.x - scaleRB2.x, PosRB2.y - scaleRB2.y, PosRB2.z + scaleRB2.z);
		vertices[3] = Vector3(PosRB2.x + scaleRB2.x, PosRB2.y - scaleRB2.y, PosRB2.z + scaleRB2.z);
		vertices[4] = Vector3(PosRB2.x + scaleRB2.x, PosRB2.y + scaleRB2.y, PosRB2.z - scaleRB2.z);
		vertices[5] = Vector3(PosRB2.x - scaleRB2.x, PosRB2.y + scaleRB2.y, PosRB2.z - scaleRB2.z);
		vertices[6] = Vector3(PosRB2.x - scaleRB2.x, PosRB2.y - scaleRB2.y, PosRB2.z - scaleRB2.z);
		vertices[7] = Vector3(PosRB2.x + scaleRB2.x, PosRB2.y - scaleRB2.y, PosRB2.z - scaleRB2.z);


		std::cout << "posRB2=" << PosRB2.x << ", " << PosRB2.y << ", " << PosRB2.z << std::endl;
		std::cout << "scaleRB2=" << scaleRB2.x << ", " << scaleRB2.y << ", " << scaleRB2.z << std::endl;
		std::cout << dx << "¡¡" << dy << " " << dz << std::endl;

		bool signX = PosRB.x - PosRB2.x > 0;
		bool signY = PosRB.y - PosRB2.y > 0;
		bool signZ = PosRB.z - PosRB2.z > 0;

		Vector3 restore = Vector3(dx - actualdisX, dy - actualdisY, dz - actualdisZ);

		double dotValue = RB->getVelocity().dot(RB2->getVelocity());
		Vector3 crossVec = RB->getVelocity().cross(RB2->getVelocity());

		Vector3 judgeVec[3];
		if (signX) judgeVec[0] = Vector3(scaleRB2.x + scaleRB.x, 0, 0);
		else judgeVec[0] = Vector3(-scaleRB2.x - scaleRB.x, 0, 0);
		if (signY) judgeVec[1] = Vector3(0, scaleRB2.y + scaleRB.y, 0);
		else judgeVec[1] = Vector3(0, -scaleRB2.y - scaleRB.y, 0);
		if (signZ) judgeVec[2] = Vector3(0, 0, scaleRB2.z + scaleRB.z);
		else judgeVec[2] = Vector3(0, 0, -scaleRB2.z - scaleRB.z);

		float cntX = abs(restore.x / negVelocity.x);
		float cntY = abs(restore.y / negVelocity.y);
		float cntZ = abs(restore.z / negVelocity.z);

		double cnt = fmin(cntX, fmin(cntY, cntZ));

		std::cout << cntX << cntY << cntZ << std::endl;

		restore = Vector3(negVelocity.x * cnt, negVelocity.y * cnt, negVelocity.z * cnt);

		if (RB2->getIsStatic()) {
			RB->getParent()->setLocalPosition(PosRB / scaleRB + restore / scaleRB);
		}
		else {
			RB->applyForce(negVelocity * 1250);
			RB->getParent()->setLocalPosition(PosRB / scaleRB + restore / scaleRB / 2);
			RB2->applyForce(velocity * 1250);
			RB2->getParent()->setLocalPosition(PosRB2 / scaleRB2 - restore / scaleRB / 2);
		}
	}
	return;
}

/* Getters */