/*!****************************************************************************
 * \file   PhysicsBody.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 * \brief  Physics body class
 *
 *****************************************************************************/
#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#pragma once

 /* Base class */
#include "Component.h"

/* Used classes */
#include "GameObject.h"
#include "Shape.h"
#include "Transform.h"
#include "Ray.h"
#include "RaycastHit.h"

class PhysicsManager;

/*!****************************************************************************
 * \brief PhysicsBody class
 * 
 * ## Usage:
 * 
 * PhysicsBody is needed to simulate the physics of the GameObject. This also
 * includes setting up the Collision Shape, which allows for interactions.
 * 
 * ## Pre-initialization calls:
 * 
 * By default, no pre-initialization calls are needed for static objects.
 * If a collision Shape is needed to enable collisions, call the following
 * function:
 * - setShape(std::shared_ptr<Shape> newShape)
 * 
 * ## General lifecycle of a PhysicsBody:
 * 
 * Note: This is assuming a movable object with collisions.
 * 
 * - Call setMass(double newMass) to set up the body's mass
 * - Create a Shape object
 * - Call setShape(std::shared_ptr<Shape> newShape)
 * - In main loop, call applyForce() to move the object.
 * 
 * ## Note:
 * 
 * PhysicsBody should have a collision Shape for any GameObject that needs to
 * interact with the environment.
 * 
 * PhysicsBody may be used without a Shape for objects that need to move in
 * the world but don't care about interacting with other objects, such as with
 * ghosts, simple hanging objects, or visual effects.
 * 
 *****************************************************************************/
class PhysicsBody : 
  public Component, public std::enable_shared_from_this<PhysicsBody> {

  friend class PhysicsManager;
public:
  PhysicsBody() : 
    mass(1.0f), inverseMass(1.0f),
    velocity(0, 0, 0), acceleration(0, 0, 0), force(0, 0, 0),
    rotationalVelocity(0, 0, 0), rotationalAcceleration(0, 0, 0),
    rotationalForce(0, 0, 0),
    restitution(0.5f), drag(0.3f), angularDrag(0.6f), isStatic(false) {}
  ~PhysicsBody() = default;

  /* Component functions */
  void initialize();
  void update(float deltaTime);
  void shutdown();

  /* Physics update function */
  virtual void integrate(float deltaTime);

  /* Utility functions */
  std::shared_ptr<PhysicsBody> registerToPhysicsManager(
    PhysicsManager& manager);
  std::shared_ptr<PhysicsBody> setMass(double newMass);
  std::shared_ptr<PhysicsBody> setVelocity(const Vector3& vel);
  std::shared_ptr<PhysicsBody> setAcceleration(const Vector3& acc);
  std::shared_ptr<PhysicsBody> applyForce(const Vector3& f);
  std::shared_ptr<PhysicsBody> setRotationalVelocity(const Vector3& vel);
  std::shared_ptr<PhysicsBody> setRotationalAcceleration(const Vector3& acc);
  std::shared_ptr<PhysicsBody> applyRotationalForce(const Vector3& f);
  std::shared_ptr<PhysicsBody> setRestitution(double r);
  std::shared_ptr<PhysicsBody> setDrag(double f);
  std::shared_ptr<PhysicsBody> setAngularDrag(float f);
  std::shared_ptr<PhysicsBody> setStatic(bool staticValue);
  std::shared_ptr<PhysicsBody> setShape(std::shared_ptr<Shape> newShape);
  std::shared_ptr<PhysicsBody> updateShapePosition();
  std::shared_ptr<PhysicsBody> setDebug(bool _debug);
  std::shared_ptr<PhysicsBody> reset();

  double      getMass()         const;
  double      getInverseMass()  const;
  Vector3     getVelocity()     const;
  Vector3     getAcceleration() const;
  Vector3     getForce()        const;
  double      getRestitution()  const;
  double      getDrag()			const;
  double      getAngularDrag()  const;
  bool        getIsStatic()     const;
  std::shared_ptr<Shape> getShape()        const;

protected:
	/** The mass of the Object */
	double mass;
	/** Inversed mass value */
	double inverseMass;
	/** The linear drag of the Object */
	double drag;
	/** The angular drag of the Object */
	double angularDrag;
	/** The restitution drag of the Object */
	double restitution;
	/** Velocity of the RigidBody */
	Vector3 velocity;
	/** Acceleration of the RigidBody */
	Vector3 acceleration;
	/** The force currently applied on the RigidBody */
	Vector3 force;
	/** If it is Static */
	bool isStatic;
  std::shared_ptr<Shape> collisionShape;
  bool debug = false;

  Vector3 rotationalVelocity;
  Vector3 rotationalAcceleration;
  Vector3 rotationalForce;

};

#endif // PHYSICS_BODY_H
