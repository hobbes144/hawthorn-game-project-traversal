/*!****************************************************************************
 * \file   RigidBody.h
 * \author Daoming Wang (daoming.wang@digipen.edu) (Callback, Base Class)
 * \author Anish Murthy (anish.murthy@digipen.edu) (Collision handling)
 * \date   01-14-2025
 * \brief  Rigidbody Component that gives a gameobject rigidbody attribute
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
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
#include "PhysicsManager.h"
#include <cmath>
#include <algorithm>
#include "AABB.h"
#include "OBB.h"
#include "Sphere.h"

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

	static float gravity;
	RigidBody();
	~RigidBody() = default;

	/* Component functions */
	void initialize() override;
	void shutdown() override;

	/* Physics update function */
	virtual void integrate(float deltaTime);

	/* Utility functions */
	std::shared_ptr<RigidBody> usingGravity(bool value);
	std::shared_ptr<RigidBody> freezingPositionX(bool value);
	std::shared_ptr<RigidBody> freezingPositionY(bool value);
	std::shared_ptr<RigidBody> freezingPositionZ(bool value);
	std::shared_ptr<RigidBody> freezingRotationX(bool value);
	std::shared_ptr<RigidBody> freezingRotationY(bool value);
	std::shared_ptr<RigidBody> freezingRotationZ(bool value);
	
	float getElasticity() const { return elasticity; }

	Vector3 getLastPosition() const { return lastPosition; }

protected:
	/** If it uses gravity */
	bool useGravity;
	float elasticity;
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

	Vector3 lastPosition;
};

void onRBCollide(std::shared_ptr<GameObject> obj1,
	std::shared_ptr<GameObject> obj2, const Vector3& point);

#endif // RIGIDBODY_H
