/*!****************************************************************************
 * \file   RigidBody.h
 * \author Daoming Wang (KeitherJinn@outlook.com)
 * \par    **DigiPen Email**
 *    daoming.wang@digipen.edu
 * \par    **Course**
 *    GAM541
 * \date   01-14-2025
 * \brief  Rigidbody Component that gives a gameobject rigidbody attribute
 * 
 *****************************************************************************/
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#pragma once

/* Base class */
#include "PhysicsBody.h"

/* Used classes */
#include "CollisionListener.h"
#include "GameObject.h"
#include "Shape.h"
#include "Transform.h"

/*!****************************************************************************
 * \brief RigidBody class that implements a rigidbody component that can be 
 * attached to the GameObject
 * 
 * ## Usage:
 *****************************************************************************/

class RigidBody : 
	public PhysicsBody {

	friend class PhysicsManager;
public:
	RigidBody();
	~RigidBody() = default;

	/* Physics update function */
	void integrate(float deltaTime);

	/* Utility functions */
	std::shared_ptr<RigidBody> usingGravity(bool value);
	std::shared_ptr<RigidBody> freezingPositionX(bool value);
	std::shared_ptr<RigidBody> freezingPositionY(bool value);
	std::shared_ptr<RigidBody> freezingPositionZ(bool value);
	std::shared_ptr<RigidBody> freezingRotationX(bool value);
	std::shared_ptr<RigidBody> freezingRotationY(bool value);
	std::shared_ptr<RigidBody> freezingRotationZ(bool value);

private:
	/** If it uses gravity */
	bool useGravity;
	/** Used for collision detection of rigidbody */
	CollisionListener* listener;
	/** If it freezes position movement of x,y,z */
	bool freezePositionX;
	bool freezePositionY;
	bool freezePositionZ;
	/** If it freezes rotation of x,y,z */
	bool freezeRotationX;
	bool freezeRotationY;
	bool freezeRotationZ;
};

void onRBCollide(std::shared_ptr<GameObject> obj1,
	std::shared_ptr<GameObject> obj2, const Vector3& point);

#endif // RIGIDBODY_H



