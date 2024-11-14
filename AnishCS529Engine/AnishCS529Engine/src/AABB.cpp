#include "AABB.h"
#include <iostream>

AABB::AABB(const Vector3& min,
            const Vector3& max)
  : localMin(min), localMax(max),
  worldMin(min), worldMax(max) {}

Shape::Type AABB::getType() const {
  return Type::AABB;
}

void AABB::update(Transform& transform) {
  // For 2D AABB, we only need 4 corners
  Vector3 corners[8] = {
      Vector3(localMin[0], localMin[1], localMin[2]), // Bottom-left-Front
      Vector3(localMax[0], localMin[1], localMin[2]), // Bottom-right-Front
      Vector3(localMin[0], localMax[1], localMin[2]), // Top-left-Front
      Vector3(localMax[0], localMax[1], localMin[2]), // Top-right-Front
      Vector3(localMin[0], localMin[1], localMax[2]), // Bottom-left-Front
      Vector3(localMax[0], localMin[1], localMax[2]), // Bottom-right-Front
      Vector3(localMin[0], localMax[1], localMax[2]), // Top-left-Front
      Vector3(localMax[0], localMax[1], localMax[2]), // Top-right-Front
  };

  // Get the transform matrix once
  Matrix4 transformMatrix = transform.getLocalMatrix();

  // Transform corners and find new world AABB bounds
  worldMin = worldMax = transformMatrix * corners[0];
  for (int i = 1; i < 8; i++) {
    Vector3 transformed = transformMatrix * corners[i];
    worldMin[0] = std::min(worldMin[0], transformed[0]);
    worldMin[1] = std::min(worldMin[1], transformed[1]);
    worldMax[0] = std::min(worldMax[0], transformed[0]);
    worldMax[1] = std::min(worldMax[1], transformed[1]);
  }
}

// Utility functions
Vector3 AABB::getMin()          const { return worldMin; }
Vector3 AABB::getMax()          const { return worldMax; }
Vector3 AABB::getCenter()       const { return (worldMin + worldMax) * 0.5f; }
Vector3 AABB::getHalfExtents()  const { return (worldMax - worldMin) * 0.5f; }
float   AABB::getWidth()        const { return worldMax[0] - worldMin[0]; }
float   AABB::getHeight()       const { return worldMax[1] - worldMin[1]; }
float   AABB::getDepth()        const { return worldMax[2] - worldMin[2]; }
