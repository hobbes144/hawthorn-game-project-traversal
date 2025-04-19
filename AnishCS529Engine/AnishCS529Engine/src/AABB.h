/*!****************************************************************************
 * \file   AABB.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-10-2025
 * \brief  
 * 
 *****************************************************************************/
#ifndef AABB_H
#define AABB_H

#pragma once

#include "EngineMath.h"
#include "Camera.h"
#include "Mesh.h"
#include "RenderGraph.h"
#include "Shape.h"

class AABB : public Shape
{
public:
  AABB(const Vector3& min = Vector3(-0.5f, -0.5f, 0.0f),
     const Vector3& max = Vector3(0.5f, 0.5f, 0.0f));
  ~AABB() = default;

  Type getType() const override;
  void update(const Transform& transform) override;
  Vector3 getFarthestExtent(const Vector3& direction) override;
  Vector3 getSurfacePoint(const Vector3& direction) override;
  Vector3 getNormalAtVector(const Vector3& direction) override;
  Vector3 getNormalClosestToPoint(const Vector3& point) override;
  //void debugDaw();

  Vector3  getMin()        const;
  Vector3  getMax()        const;
  Vector3  getCenter()     const;
  Vector3 getHalfExtents() const;
  Vector3 getLocalHalfExtents() const;
  float   getWidth()       const;
  float   getHeight()      const;
  float   getDepth()       const;

  //// debug functions
  //void initializeDebugDraw(std::shared_ptr<RenderGraph> renderGraph, std::shared_ptr<Camera> camera); // Call this once when creating OBB

  bool raycastIntersect(const Ray& ray, RaycastHit& hit, float maxDistance) const override;

private:
  Vector3 localMin, localMax;   // Original bounds in local space
  Vector3 worldMin, worldMax;   // Transformed bounds in world space

  //// debug properties
  //std::shared_ptr<Mesh> debugMesh;
  //std::shared_ptr<DebugMaterial> debugMaterial;
  //std::shared_ptr<RenderGraph> renderGraph;
  //std::shared_ptr<Camera> camera;
};

#endif // !AABB_H
