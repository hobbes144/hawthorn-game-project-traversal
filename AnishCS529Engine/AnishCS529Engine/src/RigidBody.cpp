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

#include "RigidBody.h"

float RigidBody::gravity = 9.8f;

/*!****************************************************************************
 * \brief The constructor or RigidBody class
 *****************************************************************************/
RigidBody::RigidBody() :
	PhysicsBody(), useGravity(false),
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

Vector3 OBBandOBB(std::shared_ptr<RigidBody> RB, const std::shared_ptr<RigidBody> RB2) {
	Vector3 scaleRB = RB->getParent()->getLocalScaling();
	Vector3 PosRB = RB->getParent()->getLocalPosition() * scaleRB;
	Vector3 scaleRB2 = RB2->getParent()->getLocalScaling();
	Vector3 PosRB2 = RB2->getParent()->getLocalPosition() * scaleRB2;

	const std::shared_ptr<OBB> boxA = std::static_pointer_cast<OBB>(RB->getShape());
	const std::shared_ptr<OBB> boxB = std::static_pointer_cast<OBB>(RB2->getShape());

	float minPenDepth = INFINITY;
	float penDepth = 0.0f;
	// Axis of minimum penetration depth
	int minPenAxis = 0;

	// Vector between two centers (scaled up appropriately)
	Vector3 T = (boxA->getCenter() - boxB->getCenter());

	const Vector3* aAxes = boxA->getAxes();
	const Vector3* bAxes = boxB->getAxes();

	Vector3 aExtents = boxA->getHalfExtents();
	Vector3 bExtents = boxB->getHalfExtents();

	Vector3 res = Vector3(0, 0, 0);

	// T projected to A's axes:
	T = Vector3(T.dot(aAxes[0]), T.dot(aAxes[1]), T.dot(aAxes[2]));

	// Projections of B's axes on A:
	Vector3 R[3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			R[i][j] = abs(aAxes[i].dot(bAxes[j]));
		}
	}

	// A0 axis
	// We calculate this separately so we can get the initial pen depth
	minPenDepth = penDepth = (aExtents[0] +
		(
			bExtents[0] * R[0][0] +
			bExtents[1] * R[0][1] +
			bExtents[2] * R[0][2]
			)) - T[0];
	minPenAxis = 0;

	// A1 and A2 axes
	for (int i = 1; i < 3; i++) {
		penDepth = (aExtents[i] +
		  (
			  bExtents[0] * R[i][0] +
			  bExtents[1] * R[i][1] +
			  bExtents[2] * R[i][2]
			  )) - T[i];
		if (penDepth < minPenDepth && penDepth > 0) {
			minPenDepth = penDepth;
			minPenAxis = i;
		}
	}

	// B axes
	for (int i = 0; i < 3; i++) {
		penDepth = (bExtents[i] +
			(
				aExtents[0] * R[0][i] +
				aExtents[1] * R[1][i] +
				aExtents[2] * R[2][i]
				)) - abs(T[0] * R[0][i] + T[1] * R[1][i] + T[2] * R[2][i]);
		if (penDepth < minPenDepth && penDepth > 0) {
			minPenDepth = penDepth;
			// B0 = 3, B1 = 4, B2 = 5
			minPenAxis = i + 3;
		}
	}

	// A0xB0 axis
	penDepth = (
		aExtents[1] * R[2][0] + aExtents[2] * R[1][0] +
		bExtents[1] * R[0][2] + bExtents[2] * R[0][1]
	  ) - abs(T[2] * R[1][0] - T[1] * R[2][0]);
	if (penDepth < minPenDepth && penDepth > 0) {
		minPenDepth = penDepth;
		// A0xB0 = 6
		minPenAxis = 6;
	}

	// A0xB1 axis
	penDepth = (
		aExtents[1] * R[2][1] + aExtents[2] * R[1][1] +
		bExtents[0] * R[0][2] + bExtents[2] * R[0][0]
	  ) - abs(T[2] * R[1][1] - T[1] * R[2][1]);
	if (penDepth < minPenDepth && penDepth > 0) {
		minPenDepth = penDepth;
		// A0xB1 = 7
		minPenAxis = 7;
	}

	// A0xB2 axis
	penDepth = (
		aExtents[1] * R[2][2] + aExtents[2] * R[1][2] +
		bExtents[0] * R[0][1] + bExtents[1] * R[0][0]
	  ) - abs(T[2] * R[1][2] - T[1] * R[2][2]);
	if (penDepth < minPenDepth && penDepth > 0) {
		minPenDepth = penDepth;
		// A0xB2 = 8
		minPenAxis = 8;
	}
	// A1xB0 axis
	penDepth = (
		aExtents[0] * R[2][0] + aExtents[2] * R[0][0] +
		bExtents[1] * R[1][2] + bExtents[2] * R[1][1]
	  ) - abs(T[0] * R[2][0] - T[2] * R[0][0]);
	if (penDepth < minPenDepth && penDepth > 0) {
		minPenDepth = penDepth;
		// A1xB0 = 9
		minPenAxis = 9;
	}

	// A1xB1 axis
	penDepth = (
		aExtents[0] * R[2][1] + aExtents[2] * R[0][1] +
		bExtents[0] * R[1][2] + bExtents[2] * R[1][0]
	  ) - abs(T[0] * R[2][1] - T[2] * R[0][1]);
	if (penDepth < minPenDepth && penDepth > 0) {
		minPenDepth = penDepth;
		// A1xB1 = 10
		minPenAxis = 10;
	}
	// A1xB2 axis
	penDepth = (
		aExtents[0] * R[2][2] + aExtents[2] * R[0][2] +
		bExtents[0] * R[1][1] + bExtents[1] * R[1][0]
	  ) - abs(T[0] * R[2][2] - T[2] * R[0][2]);
	if (penDepth < minPenDepth && penDepth > 0) {
		minPenDepth = penDepth;
		// A1xB2 = 11
		minPenAxis = 11;
	}
	// A2xB0 axis
	penDepth = (
		aExtents[0] * R[1][0] + aExtents[1] * R[0][0] +
		bExtents[1] * R[2][2] + bExtents[2] * R[2][1]
	  ) - abs(T[1] * R[0][0] - T[0] * R[1][0]);
	if (penDepth < minPenDepth && penDepth > 0) {
		minPenDepth = penDepth;
		// A2xB0 = 12
		minPenAxis = 12;
	}
	// A2xB1 axis
	penDepth = (
		aExtents[0] * R[1][1] + aExtents[1] * R[0][1] +
		bExtents[0] * R[2][2] + bExtents[2] * R[2][0]
	  ) - abs(T[1] * R[0][1] - T[0] * R[1][1]);
	if (penDepth < minPenDepth && penDepth > 0) {
		minPenDepth = penDepth;
		// A2xB1 = 13
		minPenAxis = 13;
	}
	// A2xB2 axis
	penDepth = (
		aExtents[0] * R[1][2] + aExtents[1] * R[0][2] +
		bExtents[0] * R[2][1] + bExtents[1] * R[2][0]
	  ) - abs(T[1] * R[0][2] - T[0] * R[1][2]);
	if (penDepth < minPenDepth && penDepth > 0) {
		minPenDepth = penDepth;
		// A2xB2 = 14
		minPenAxis = 14;
	}

	std::cout << minPenDepth << "\n";
	std::cout << minPenAxis << "\n";

	if (minPenAxis == 0) {
		return boxA->getAxes()[0].normalized() * minPenDepth;
	}
	else if (minPenAxis == 1) {
		return boxA->getAxes()[1].normalized() * minPenDepth;
	}
	else if (minPenAxis == 2) {
		return boxA->getAxes()[2].normalized() * minPenDepth;
	}
	else if (minPenAxis == 3) {
		return boxB->getAxes()[0].normalized() * minPenDepth;
	}
	else if (minPenAxis == 4) {
		return boxB->getAxes()[1].normalized() * minPenDepth;
	}
	else if (minPenAxis == 5) {
		return boxB->getAxes()[2].normalized() * minPenDepth;
	}
	else if (minPenAxis == 6) {
		return boxA->getAxes()[0].cross(boxB->getAxes()[0]).normalized() * minPenDepth;
	}
	else if (minPenAxis == 7) {
		return boxA->getAxes()[0].cross(boxB->getAxes()[1]).normalized() * minPenDepth;
	}
	else if (minPenAxis == 8) {
		return boxA->getAxes()[0].cross(boxB->getAxes()[2]).normalized() * minPenDepth;
	}
	if (minPenAxis == 9) {
		return boxA->getAxes()[1].cross(boxB->getAxes()[0]).normalized() * minPenDepth;
	}
	else if (minPenAxis == 10) {
		return boxA->getAxes()[1].cross(boxB->getAxes()[1]).normalized() * minPenDepth;
	}
	else if (minPenAxis == 11) {
		return boxA->getAxes()[1].cross(boxB->getAxes()[2]).normalized() * minPenDepth;
	}
	if (minPenAxis == 12) {
		return boxA->getAxes()[2].cross(boxB->getAxes()[0]).normalized() * minPenDepth;
	}
	else if (minPenAxis == 13) {
		return boxA->getAxes()[2].cross(boxB->getAxes()[1]).normalized() * minPenDepth;
	}
	else if (minPenAxis == 14) {
		return boxA->getAxes()[2].cross(boxB->getAxes()[2]).normalized() * minPenDepth;
	}
	else {
		return Vector3(0, 0, 0);
	}
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
	Vector3 mtv = Vector3(0, 0, 0);
	std::shared_ptr<RigidBody> RB, RB2;

	if (obj1->findComponent<RigidBody>()->getIsStatic()) {
		if (obj2->findComponent<RigidBody>()->getIsStatic()) return;
		RB2 = obj1->findComponent<RigidBody>();
		RB = obj2->findComponent<RigidBody>();
	}
	else {
		RB = obj1->findComponent<RigidBody>();
		RB2 = obj2->findComponent<RigidBody>();
	}

	Vector3 scaleRB = RB->getParent()->getLocalScaling();
	Vector3 PosRB = RB->getParent()->getLocalPosition() * scaleRB;
	Vector3 scaleRB2 = RB2->getParent()->getLocalScaling();
	Vector3 PosRB2 = RB2->getParent()->getLocalPosition() * scaleRB2;
	Vector3 velocity = RB->getVelocity();
	Vector3 velocity2 = RB2->getVelocity();

	if (RB && RB2) {
		Vector3 final = Vector3(0, 0, 0);

		const std::shared_ptr<OBB> boxA = std::static_pointer_cast<OBB>(RB->getShape());
		const std::shared_ptr<OBB> boxB = std::static_pointer_cast<OBB>(RB2->getShape());

		if (RB->getShape()->getType() == Shape::Type::OBB && 
			RB2->getShape()->getType() == Shape::Type::OBB) {
			
			final = OBBandOBB(RB, RB2);
			std::cout << final << "\n";
		}
		else {
			return;
		}

		if (PosRB.x - PosRB2.x < 0) {
			final.x = -final.x;
		}
		if (PosRB.y - PosRB2.y < 0) {
			final.y = -final.y;
		}
		if (PosRB.z - PosRB2.z < 0) {
			final.z = -final.z;
		}

		if (RB2->getIsStatic()) {
			RB->getParent()->setLocalPosition((PosRB + final) / scaleRB);
		}
		else {
			RB->getParent()->setLocalPosition((PosRB + final / 2) / scaleRB);
			RB2->getParent()->setLocalPosition((PosRB2 - final / 2) / scaleRB2);
		}
	}
	return;
}

/* Getters */
