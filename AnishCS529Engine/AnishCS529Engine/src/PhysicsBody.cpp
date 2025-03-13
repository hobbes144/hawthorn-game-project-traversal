/*!****************************************************************************
 * \file   PhysicsBody.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 * 
 *****************************************************************************/
#include "precompiled.h"

#include "PhysicsBody.h"
#include "PhysicsManager.h"


/*!****************************************************************************
 * \brief Register self to the PhysicsManager
 * 
 * ## Usage:
 * 
 * If a collision Shape exists and collisions need to be properly calculated,
 * the PhysicsBody must be registered to the PhysicsManager.
 * 
 * \param manager PhysicsManager
 * \return \b std::shared_ptr<PhysicsBody> Self
 *****************************************************************************/
std::shared_ptr<PhysicsBody> PhysicsBody::registerToPhysicsManager(
  PhysicsManager& manager)
{
  manager.addBody(shared_from_this());
  return shared_from_this();
}

/*!****************************************************************************
 * \brief Set the mass
 * 
 * ## Usage:
 * 
 * If the object is allowed to move, it must have a mass that the forces can
 * be applied on.
 * 
 * This can be skipped for static objects.
 * 
 * \param newMass Mass of the PhysicsBody
 * \return \b std::shared_ptr<PhysicsBody> Self
 *****************************************************************************/
std::shared_ptr<PhysicsBody> PhysicsBody::setMass(double newMass) {
  mass = newMass;
  inverseMass = newMass > 0.0f ? 1.0f / newMass : 0.0f;
  isStatic = (newMass == 0.0f);

  return shared_from_this();
}

/*!****************************************************************************
 * \brief Set the velocity
 *
 * ## Usage:
 *
 * This is to be used if the object's velocity needs to be reset to a specific
 * value. A common use case would be during collisions, where instead of force,
 * velocity might be set instead. Or in portals where, velocity must be shifted
 * to a different reference frame.
 *
 * \param vel Velocity of the PhysicsBody
 * \return \b std::shared_ptr<PhysicsBody> Self
 *****************************************************************************/
std::shared_ptr<PhysicsBody> PhysicsBody::setVelocity(const Vector3& vel) {
  velocity = vel;

  return shared_from_this();
}

/*!****************************************************************************
 * \brief Set the acceleration
 *
 * ## Usage:
 *
 * This is used only if a burst of velocity is needed. This can be finnicky, so
 * avoid using.
 *
 * ## Explanation:
 *
 * Acceleration is reset at the end of each update() call, so this would only
 * take effect for the single update.
 *
 * \param acc Acceleration of the PhysicsBody
 * \return \b std::shared_ptr<PhysicsBody> Self
 *****************************************************************************/
std::shared_ptr<PhysicsBody> PhysicsBody::setAcceleration(const Vector3& acc) {
  acceleration = acc;

  return shared_from_this();
}

/*!****************************************************************************
 * \brief Apply a force
 *
 * ## Usage:
 *
 * This should be the primary way of interacting with the object. It sets the
 * force to affect the object for the update() call.
 *
 * ## Note:
 *
 * Force is reset at the end of each update() call, so this would only take
 * effect for the single update.
 *
 * \param f Force on the PhysicsBody
 * \return \b std::shared_ptr<PhysicsBody> Self
 *****************************************************************************/
std::shared_ptr<PhysicsBody> PhysicsBody::applyForce(const Vector3& f) {
  force = force + f;

  return shared_from_this();
}

std::shared_ptr<PhysicsBody> PhysicsBody::setRotationalVelocity(const Vector3& vel)
{
  rotationalVelocity = vel;

  return shared_from_this();
}

std::shared_ptr<PhysicsBody> PhysicsBody::setRotationalAcceleration(const Vector3& acc)
{
  rotationalAcceleration = acc;

  return shared_from_this();
}

std::shared_ptr<PhysicsBody> PhysicsBody::applyRotationalForce(const Vector3& f)
{
  rotationalForce = rotationalForce + f;

  return shared_from_this();
}

/*!****************************************************************************
 * \brief Reset the force on the object
 * 
 * ## Usage:
 * 
 * This can be used when the object should be forced to stop all motion.
 * 
 * \return \b 
 *****************************************************************************/
std::shared_ptr<PhysicsBody> PhysicsBody::reset()
{
  force = Vector3(0.0f, 0.0f, 0.0f);
  velocity = Vector3(0.0f, 0.0f, 0.0f);
  return shared_from_this();
}

/*!****************************************************************************
 * \brief Dummy restitution
 *
 * This has not yet been implemented.
 *
 * \param r Resitution of the PhysicsBody
 * \return \b std::shared_ptr<PhysicsBody> Self
 *****************************************************************************/
std::shared_ptr<PhysicsBody> PhysicsBody::setRestitution(double r) {
  restitution = r;

  return shared_from_this();
}

/*!****************************************************************************
 * \brief Set the friction affecting the body
 *
 * ## Usage:
 *
 * This is set to 0.3f by default. Set this to the required value to change the
 * friction affecting the body.
 *
 * \param f Friction of the PhysicsBody
 * \return \b std::shared_ptr<PhysicsBody> Self
 *****************************************************************************/
std::shared_ptr<PhysicsBody> PhysicsBody::setDrag(double f) {
  drag = f;

  return shared_from_this();
}

/*!****************************************************************************
 * \brief Set the angular drag (angular friction) affecting the body
 *
 * ## Usage:
 *
 * This has not yet been implemented.
 *
 * \param f Angular drag (angular friction) of the PhysicsBody
 * \return \b std::shared_ptr<PhysicsBody> Self
 *****************************************************************************/
std::shared_ptr<PhysicsBody> PhysicsBody::setAngularDrag(float f) {
    angularDrag = f;

    return shared_from_this();
}

/*!****************************************************************************
 * \brief Sets the body to be static
 *
 * ## Usage:
 *
 * This is to be used if the object should no longer be movable.
 *
 * ## Explanation:
 *
 * This resets the body's mass to 0.0f, so be aware of this if you want to use
 * this to just freeze an object. When unfrozen, the object needs to have its
 * mass reset to the old value.
 *
 * \param staticValue True if static
 * \return \b std::shared_ptr<PhysicsBody> Self
 *****************************************************************************/
std::shared_ptr<PhysicsBody> PhysicsBody::setStatic(bool staticValue) {
  isStatic = staticValue;
  if (staticValue) {
    mass = 0.0f;
    inverseMass = 0.0f;
  }

  return shared_from_this();
}

/*!****************************************************************************
 * \brief Set up the collision Shape
 *
 * ## Usage:
 *
 * This is to be used when the object needs to have interactions with other
 * objects in the world. This can be skipped if world interactions aren't
 * needed.
 *
 * \param newShape Shape to be added to the object
 * \return \b std::shared_ptr<PhysicsBody> Self
 *****************************************************************************/
std::shared_ptr<PhysicsBody> PhysicsBody::setShape(std::shared_ptr<Shape> newShape) {
  collisionShape = newShape;
  collisionShape->update(parent->getWorldTransform());

  return shared_from_this();
}

std::shared_ptr<PhysicsBody> PhysicsBody::updateShapePosition()
{
  if (collisionShape) {
    collisionShape->update(parent->getWorldTransform());
  }
  return shared_from_this();
}

/* Getters */

/*!****************************************************************************
 * \brief Get the mass
 * 
 * \return \b double Mass
 *****************************************************************************/
double PhysicsBody::getMass()            const { return mass; }

/*!****************************************************************************
 * \brief Get the inverse mass
 * 
 * \return \b double Inverse mass
 *****************************************************************************/
double PhysicsBody::getInverseMass()     const { return inverseMass; }

/*!****************************************************************************
 * \brief Get the velocity
 * 
 * \return \b Vector3 Velocity
 *****************************************************************************/
Vector3 PhysicsBody::getVelocity()      const { return velocity; }

/*!****************************************************************************
 * \brief Get the acceleration
 * 
 * \return \b Vector3 Acceleration
 *****************************************************************************/
Vector3 PhysicsBody::getAcceleration()  const { return acceleration; }

/*!****************************************************************************
 * \brief Get the force
 * 
 * \return \b Vector3 Force
 *****************************************************************************/
Vector3 PhysicsBody::getForce()         const { return force; }

/*!****************************************************************************
 * \brief Get the restitution
 * 
 * \return \b double Restitution
 *****************************************************************************/
double PhysicsBody::getRestitution()     const { return restitution; }

/*!****************************************************************************
 * \brief Get the friction
 * 
 * \return \b double Friction
 *****************************************************************************/
double PhysicsBody::getDrag()        const { return drag; }

/*!****************************************************************************
 * \brief Get the friction
 *
 * \return \b double Friction
 *****************************************************************************/
double PhysicsBody::getAngularDrag()        const { return angularDrag; }

/*!****************************************************************************
 * \brief Get if the object is static
 * 
 * \return \b bool True if static
 *****************************************************************************/
bool PhysicsBody::getIsStatic()         const { return isStatic; }

/*!****************************************************************************
 * \brief Get the Collision Shape
 * 
 * \return \b Shape* Collision Shape
 *****************************************************************************/
std::shared_ptr<Shape> PhysicsBody::getShape() const { return collisionShape; }

std::shared_ptr<PhysicsBody> PhysicsBody::setDebug(bool _debug)
{
  debug = _debug;
  return shared_from_this();
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
void PhysicsBody::integrate(float deltaTime) {
  if (!parent->isEnabled()) return;
  if (!isStatic) {
    Transform parentTransform = parent->getTransform();
    Vector3 netFriction;
    if (velocity.magnitude() > 1e-16f) {
        netFriction = velocity.normalized() * velocity.magnitude() * float(-drag);
    }
    else {
      netFriction = Vector3(0.0f, 0.0f, 0.0f);
    }

    acceleration = acceleration + (force + netFriction) * float(inverseMass);
    velocity = velocity + (acceleration * deltaTime);

    if (velocity > 1e-16f) {
      parent->setWorldPosition(parentTransform.getPosition() + (velocity * deltaTime));
    }
    else {
      velocity = Vector3();
    }

    Vector3 netRotationalFriction;
    if (rotationalVelocity.magnitude() > 1e-16f) {
      netRotationalFriction = rotationalVelocity.normalized() * rotationalVelocity.magnitude() * float(-angularDrag);
    }
    else {
      netRotationalFriction = Vector3();
    }

    rotationalAcceleration = rotationalAcceleration + (rotationalForce + netRotationalFriction) * float(inverseMass);
    rotationalVelocity = rotationalVelocity + (rotationalAcceleration * deltaTime);
    if (rotationalVelocity > 1e-16f) {
      parent->setWorldRotation(parentTransform.getRotation() * Quaternion::fromEuler(rotationalVelocity * deltaTime));
    }
    else {
      rotationalVelocity = Vector3();
    }
  }

  if (collisionShape) {
    collisionShape->update(parent->getWorldTransform());
  }

  // Reset force accumulator
  force = Vector3(0, 0, 0);
  acceleration = Vector3(0, 0, 0);
  rotationalForce = Vector3(0, 0, 0);
  rotationalAcceleration = Vector3(0, 0, 0);
}

/*!****************************************************************************
 * \brief Dummy initialize function
 * 
 *****************************************************************************/
void PhysicsBody::initialize() {}

/*!****************************************************************************
 * \brief Dummy update function
 * 
 *****************************************************************************/
void PhysicsBody::update(float deltaTime) {
  if (debug) {
    collisionShape->debugDaw();
  }
}

/*!****************************************************************************
 * \brief Dummy shutdown function
 *****************************************************************************/
void PhysicsBody::shutdown() {}
