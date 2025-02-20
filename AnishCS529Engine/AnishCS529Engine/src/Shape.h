#pragma once

#include  "Transform.h"

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
};