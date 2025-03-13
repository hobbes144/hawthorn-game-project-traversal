#pragma once

#include "Shape.h"
#include "Transform.h"

class Sphere : public Shape {
public:
  Sphere(const Vector3& center = Vector3(0, 0, 0), float radius = 0.5f);

  Type getType() const override;
  void update(const Transform& transform) override;
  Vector3 getFarthestExtent(const Vector3& direction) override;
  Vector3 getSurfacePoint(const Vector3& direction) override;
  Vector3 getCenter() const;
  float getRadius() const;

  bool raycastIntersect(const Ray& ray, RaycastHit& hit, float maxDistance) const override;

private:
  Vector3 center;
  float radius;
};
