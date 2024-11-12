#pragma once

#include "Shape.h"
#include "Transform.h"

class Circle : public Shape {
public:
    Circle(const Vector3& center = Vector3(0, 0, 0), float radius = 0.5f);
    
    Type getType() const override;
    void update(Transform& transform) override;
    Vector3 getCenter() const;
    float getRadius() const;

private:
    Vector3 center;
    float radius;
};
