#pragma once
#include "Transform.h"
#include "Shape.h"
#include <memory>

class RenderableNode;

class PhysicsBody {
    friend class PhysicsManager;
public:
    PhysicsBody(RenderableNode* owner);

    void setMass(float newMass);
    void setVelocity(const Vector3& vel);
    void setAcceleration(const Vector3& acc);
    void applyForce(const Vector3& f);
    void setRestitution(float r);
    void setFriction(float f);
    void setStatic(bool staticValue);
    void setShape(std::shared_ptr<Shape> newShape);

    // Getters
    float       getMass()         const;
    float       getInverseMass()  const;
    Vector3     getVelocity()     const;
    Vector3     getAcceleration() const;
    Vector3     getForce()        const;
    float       getRestitution()  const;
    float       getFriction()     const;
    bool        getIsStatic()     const;
    Shape*      getShape()        const;
    RenderableNode* getOwner()        const;

    // integration function
    void integrate(float dt);

private:
    RenderableNode* owner;
    float mass;
    float inverseMass;
    Vector3 velocity;
    Vector3 acceleration;
    Vector3 force;
    float restitution;
    float friction;
    bool isStatic;
    std::shared_ptr<Shape> collisionShape;
};

