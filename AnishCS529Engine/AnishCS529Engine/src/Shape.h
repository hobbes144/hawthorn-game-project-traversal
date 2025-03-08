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
  virtual void update(Transform& transform) = 0;
  virtual void debugDaw() = 0;

  virtual bool raycastIntersect(const Ray& ray, RaycastHit& hit, float maxDistance) const = 0;

};