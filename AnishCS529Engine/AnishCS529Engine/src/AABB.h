#pragma once

#include "Shape.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Material.h"

class AABB : public Shape
{
public:
  AABB(const Vector3& min = Vector3(-0.5f, -0.5f, 0.0f),
     const Vector3& max = Vector3(0.5f, 0.5f, 0.0f));
  ~AABB() = default;

  Type getType() const override;
  void update(Transform& transform);

  Vector3  getMin()        const;
  Vector3  getMax()        const;
  Vector3  getCenter()     const;
  Vector3 getHalfExtents() const;
  float   getWidth()       const;
  float   getHeight()      const;
  float   getDepth()       const;

  // debug functions
  void initializeDebugDraw(Renderer* renderer); // Call this once when creating OBB
  void drawDebugLines(Matrix4& view, Matrix4& projection); // Call this in your render loop


private:
  Vector3 localMin, localMax;   // Original bounds in local space
  Vector3 worldMin, worldMax;   // Transformed bounds in world space

  // debug properties
  std::shared_ptr<Mesh> debugMesh;
  std::shared_ptr<Material> debugMaterial;
  Renderer* renderer;
};

