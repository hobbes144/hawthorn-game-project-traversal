#include "Sphere.h"

Sphere::Sphere(const Vector3& center, float radius)
  : center(center), radius(radius) {}

Shape::Type Sphere::getType() const {
  return Type::Sphere;
}

void Sphere::update(Transform& transform) {
  // Update center position
  Matrix4 transformMatrix = transform.getLocalMatrix();
  center = transformMatrix * center;

  // For 2D Sphere, use the largest scale component for the radius
  Vector3 scale = transform.getScaling();
  float maxScale = std::max(std::max(std::abs(scale.x), std::abs(scale.y)), std::abs(scale.z));
  radius *= maxScale;
}

Vector3 Sphere::getCenter() const {
  return center;
}

float Sphere::getRadius() const {
  return radius;
}