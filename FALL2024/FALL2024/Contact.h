#pragma once

#include "PhysicsBody.h"

class Contact {
public:
    Contact() : bodies{ nullptr, nullptr } {}

    PhysicsBody* bodies[2];    // The two bodies in contact
    Vector3 point;             // Point of contact (if needed for visualization)
};