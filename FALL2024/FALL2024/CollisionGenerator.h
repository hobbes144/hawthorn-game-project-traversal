#pragma once

#include "Shape.h"
#include "Contact.h"
#include <array>
#include <vector>

class CollisionGenerator {
public:
    using CollisionTest = bool(*)(const Shape*, const Shape*, Contact&);

    CollisionGenerator();

    // Main collision check function
    bool generateContact(PhysicsBody* body1, PhysicsBody* body2, Contact& contact);

private:
    void initializeCollisionMatrix();

    // Collision test functions
    static bool AABBvsAABB(const Shape* a, const Shape* b, Contact& contact);
    static bool AABBvsOBB(const Shape* a, const Shape* b, Contact& contact);
    static bool AABBvsCircle(const Shape* a, const Shape* b, Contact& contact);
    
    static bool OBBvsOBB(const Shape* a, const Shape* b, Contact& contact);
    static bool OBBvsAABB(const Shape* a, const Shape* b, Contact& contact);
    static bool OBBvsCircle(const Shape* a, const Shape* b, Contact& contact);

    static bool CirclevsCircle(const Shape* a, const Shape* b, Contact& contact);
    static bool CirclevsAABB(const Shape* a, const Shape* b, Contact& contact);
    static bool CirclevsOBB(const Shape* a, const Shape* b, Contact& contact);
    

    // The collision test table
    std::array<std::array<CollisionTest, 3>, 3> collisionTests;
};