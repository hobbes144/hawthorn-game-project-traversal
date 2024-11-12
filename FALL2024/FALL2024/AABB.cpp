#include "AABB.h"
#include <iostream>

AABB::AABB( const Vector3& min,
            const Vector3& max)
    : localMin(min), localMax(max),
    worldMin(min), worldMax(max) {}

Shape::Type AABB::getType() const { 
    return Type::AABB; 
}

void AABB::update(Transform& transform){
    // For 2D AABB, we only need 4 corners
    Vector3 corners[4] = {
        Vector3(localMin.x, localMin.y, 0.0f), // Bottom-left
        Vector3(localMax.x, localMin.y, 0.0f), // Bottom-right
        Vector3(localMin.x, localMax.y, 0.0f), // Top-left
        Vector3(localMax.x, localMax.y, 0.0f)  // Top-right
    };

    // Get the transform matrix once
    Matrix4 transformMatrix = transform.getLocalMatrix();

    // Transform corners and find new world AABB bounds
    worldMin = worldMax = transformMatrix * corners[0];
    for (int i = 1; i < 4; i++) {
        Vector3 transformed = transformMatrix * corners[i];
        worldMin.x = std::min(worldMin.x, transformed.x);
        worldMin.y = std::min(worldMin.y, transformed.y);
        worldMax.x = std::max(worldMax.x, transformed.x);
        worldMax.y = std::max(worldMax.y, transformed.y);
    }
}

// Utility functions
Vector3 AABB::getMin()          const { return worldMin; }
Vector3 AABB::getMax()          const { return worldMax; }
Vector3 AABB::getCenter()       const { return (worldMin + worldMax) * 0.5f; }
Vector3 AABB::getHalfExtents()  const { return (worldMax - worldMin) * 0.5f; }
float   AABB::getWidth()        const { return worldMax.x - worldMin.x; }
float   AABB::getHeight()       const { return worldMax.y - worldMin.y; }
