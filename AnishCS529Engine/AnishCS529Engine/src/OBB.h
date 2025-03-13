/*!****************************************************************************
 * \file   OBB.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-10-2025
 * \brief  
 * 
 *****************************************************************************/
#ifndef OBB_H
#define OBB_H

#pragma once

#include "Camera.h"
#include "DebugMaterial.h"
#include "DebugPass.h"
#include "EngineMath.h"
#include "Mesh.h"
#include "RenderGraph.h"
#include "Shape.h"

class OBB : public Shape
{
public:
  OBB(const Vector3& center = Vector3(0, 0, 0), const Vector3& halfExtents = Vector3(0.5f, 0.5f, 0.5f));
  ~OBB() = default;

  Type getType() const override;
  void update(const Transform& transform) override;
  Vector3 getFarthestExtent(const Vector3& direction) override;
  Vector3 getSurfacePoint(const Vector3& direction) override;
  Vector3 getNormalAtVector(const Vector3& direction) override;
  void debugDaw();

  void getCorners(Vector3 corners[4]) const;

  void project(const Vector3& axis, float& min, float& max) const;

  Vector3 getCenter() const;
  Vector3 getHalfExtents() const;
  Vector3 getRight() const;
  Vector3 getUp() const;
  Vector3 getFront() const;
  const Vector3* getAxes() const;

  // debug functions
  void initializeDebugDraw(
    std::shared_ptr<RenderGraph> renderGraph, std::shared_ptr<Camera> camera); // Call this once when creating OBB

  bool raycastIntersect(const Ray& ray, RaycastHit& hit, float maxDistance) const override;

private:
  // Local space values (original, unchanged)
  Vector3 localCenter;
  Vector3 localHalfExtents;
  Vector3 localScale;
  Vector3 localAxes[3]; // unused
  Vector3 localRight;
  Vector3 localUp;
  Vector3 localFront;

  // World space values (transformed)
  Vector3 worldCenter;
  Vector3 unscaledWorldCenter;
  Vector3 worldHalfExtents;
  Vector3 worldAxes[3];
  Vector3 worldRight;
  Vector3 worldUp;
  Vector3 worldFront;

  Quaternion rotation;

  // debug properties
  std::shared_ptr<Mesh> debugMesh;
  std::shared_ptr<DebugMaterial> debugMaterial;
  std::shared_ptr<RenderGraph> renderGraph;
  std::shared_ptr<Camera> camera;

};

#endif // !OBB_H
