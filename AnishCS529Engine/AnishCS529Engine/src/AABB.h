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

#include "Camera.h"
#include "DebugMaterial.h"
#include "DebugPass.h"
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
  void update(Transform& transform);
  void debugDaw();

  Vector3  getMin()        const;
  Vector3  getMax()        const;
  Vector3  getCenter()     const;
  Vector3 getHalfExtents() const;
  float   getWidth()       const;
  float   getHeight()      const;
  float   getDepth()       const;

  // debug functions
  void initializeDebugDraw(std::shared_ptr<RenderGraph> renderGraph); // Call this once when creating OBB


private:
  Vector3 localMin, localMax;   // Original bounds in local space
  Vector3 worldMin, worldMax;   // Transformed bounds in world space

  // debug properties
  std::shared_ptr<Mesh> debugMesh;
  std::shared_ptr<DebugMaterial> debugMaterial;
  std::shared_ptr<RenderGraph> renderGraph;
  std::shared_ptr<Camera> camera;
};

#endif // !AABB_H
