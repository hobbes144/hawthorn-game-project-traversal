#include "PhysicsBody.h"
#include "RenderableNode.h"


PhysicsBody::PhysicsBody(RenderableNode* owner)
    : owner(owner), mass(1.0f), inverseMass(1.0f),
    velocity(0, 0, 0), acceleration(0, 0, 0), force(0, 0, 0),
    restitution(0.5f), friction(0.3f), isStatic(false) {}

void PhysicsBody::setMass(float newMass) {
    mass = newMass;
    inverseMass = newMass > 0.0f ? 1.0f / newMass : 0.0f;
    isStatic = (newMass == 0.0f);
}

void PhysicsBody::setVelocity(const Vector3& vel) {
    velocity = vel;
}

void PhysicsBody::setAcceleration(const Vector3& acc) {
    acceleration = acc;
}

void PhysicsBody::applyForce(const Vector3& f) {
    force = force + f;
}

void PhysicsBody::setRestitution(float r) {
    restitution = r;
}

void PhysicsBody::setFriction(float f) {
    friction = f;
}

void PhysicsBody::setStatic(bool staticValue) {
    isStatic = staticValue;
    if (staticValue) {
        mass = 0.0f;
        inverseMass = 0.0f;
    }
}

void PhysicsBody::setShape(std::shared_ptr<Shape> newShape) {
    collisionShape = newShape;
}

float PhysicsBody::getMass()            const { return mass; }
float PhysicsBody::getInverseMass()     const { return inverseMass; }
Vector3 PhysicsBody::getVelocity()      const { return velocity; }
Vector3 PhysicsBody::getAcceleration()  const { return acceleration; }
Vector3 PhysicsBody::getForce()         const { return force; }
float PhysicsBody::getRestitution()     const { return restitution; }
float PhysicsBody::getFriction()        const { return friction; }
bool PhysicsBody::getIsStatic()         const { return isStatic; }
Shape* PhysicsBody::getShape()          const { return collisionShape.get(); }
RenderableNode* PhysicsBody::getOwner() const { return owner; }

void PhysicsBody::integrate(float dt) {
    if (isStatic) return;

    // TODO: Semi-implicit Euler integration
    // implement here ->:

    // TODO: Update position through the owner's transform
    Vector3 newPosition = Vector3();// <- how do you get this new value :) ??? 
    owner->setLocalPosition(newPosition);

    // Update collision shape
    if (collisionShape) {
        // Since we don't have direct access to transform,
        // we'll create a Transform object with the current state
        Transform currentTransform;
        currentTransform.setPosition(owner->getLocalPosition());
        currentTransform.setRotation(owner->getLocalRotation());
        currentTransform.setScale(owner->getLocalScale());

        // TODO: What else do you have to update during the integration
        // besides the owner's position?
        // implement here ->:
    }

    // Reset force accumulator
    force = Vector3(0, 0, 0);
}
