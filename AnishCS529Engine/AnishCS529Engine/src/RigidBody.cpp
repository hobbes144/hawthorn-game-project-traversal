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

const float gravity = -9.8f;

/*!****************************************************************************
 * \brief 
 *****************************************************************************/
RigidBody::RigidBody():
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
                velocity.normalized() * velocity.magnitude() * - drag;
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
        std::cout << "test" << std::endl;
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
        
        Vector3 PosRB = RB->getParent()->getLocalPosition();
        Vector3 PosRB2 = RB2->getParent()->getLocalPosition();

        if (RB2->getIsStatic()) {
            RB->getParent()->setLocalPosition();
            return;
        }

        RB->applyForce(negVelocity * 2500);
        RB2->applyForce(velocity * 2500);
    }
    return;
}

/* Getters */