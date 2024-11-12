#pragma once

#include  "Transform.h"

class Shape {
public:
    enum class Type {
        AABB,
        OBB,
        Circle
    };

    virtual ~Shape() = default;
    virtual Type getType() const = 0;
    virtual void update(Transform& transform) = 0;
};