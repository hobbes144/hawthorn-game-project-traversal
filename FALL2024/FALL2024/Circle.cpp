#include "Circle.h"

Circle::Circle(const Vector3& center, float radius)
    : center(center), radius(radius) {}

Shape::Type Circle::getType() const {
    return Type::Circle;
}

void Circle::update(Transform& transform) {
    // Update center position
    Matrix4 transformMatrix = transform.getLocalMatrix();
    center = transformMatrix * center;

    // For 2D circle, use the largest scale component for the radius
    Vector3 scale = transform.getScale();
    float maxScale = std::max(std::abs(scale.x), std::abs(scale.y));
    radius *= maxScale;
}

Vector3 Circle::getCenter() const {
    return center;
}

float Circle::getRadius() const {
    return radius;
}