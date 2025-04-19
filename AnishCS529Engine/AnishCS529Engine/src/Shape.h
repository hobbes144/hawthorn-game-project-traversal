/*!****************************************************************************
 * \file   Shape.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \author Mariojulio Osmin Zaldivar Alvarez (ex-Adjunct Professor)
 *   (zaldivaralvarez@gmail.com) (Advising and Base Code)
 * \par    **Course**
 *    GAM541
 * \brief  Shape base class used by all Collision Shapes
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 *
 *****************************************************************************/
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
  virtual Vector3 getNormalClosestToPoint(const Vector3& point) = 0;
  // virtual void debugDaw() = 0;

  virtual bool raycastIntersect(const Ray& ray, RaycastHit& hit, float maxDistance) const = 0;

};