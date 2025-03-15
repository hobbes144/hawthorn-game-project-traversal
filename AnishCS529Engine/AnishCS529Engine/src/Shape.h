#pragma once

#include  "Transform.h"
#include "Ray.h"
#include "RaycastHit.h"

class Shape {
public:
  enum class Type { 
    AABB,
    OBB,
    Sphere
  };

  virtual ~Shape() = default;
  virtual Type getType() const = 0;
  virtual void update(const Transform& transform) = 0;
  virtual Vector3 getFarthestExtent(const Vector3& direction) = 0;
  virtual Vector3 getSurfacePoint(const Vector3& direction) = 0;
  virtual Vector3 getNormalAtVector(const Vector3& direction) = 0;
  virtual void debugDaw() = 0;

  virtual bool raycastIntersect(const Ray& ray, RaycastHit& hit, float maxDistance) const = 0;

};