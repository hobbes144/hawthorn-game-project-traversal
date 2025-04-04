#include "precompiled.h"
#include "AABB.h"
#include <iostream>

AABB::AABB(const Vector3& min,
            const Vector3& max)
  : localMin(min), localMax(max),
  worldMin(min), worldMax(max) {}

Shape::Type AABB::getType() const {
  return Type::AABB;
}

void AABB::update(const Transform& transform) {
  // For 2D AABB, we only need 4 corners
  Vector3 corners[8] = {
      Vector3(localMin[0], localMin[1], localMin[2]), // Bottom-left-Front
      Vector3(localMax[0], localMin[1], localMin[2]), // Bottom-right-Front
      Vector3(localMin[0], localMax[1], localMin[2]), // Top-left-Front
      Vector3(localMax[0], localMax[1], localMin[2]), // Top-right-Front
      Vector3(localMin[0], localMin[1], localMax[2]), // Bottom-left-Back
      Vector3(localMax[0], localMin[1], localMax[2]), // Bottom-right-Back
      Vector3(localMin[0], localMax[1], localMax[2]), // Top-left-Back
      Vector3(localMax[0], localMax[1], localMax[2]), // Top-right-Back
  };

  // Get the transform matrix once
  Matrix4 transformMatrix = transform.getLocalMatrix();

  // Transform corners and find new world AABB bounds
  worldMin = worldMax = transformMatrix * corners[0];
  for (int i = 1; i < 8; i++) {
    // Todo: find out why this is not correct
    Vector3 transformed = transformMatrix * corners[i];
    worldMin[0] = std::min(worldMin[0], transformed[0]);
    worldMin[1] = std::min(worldMin[1], transformed[1]);
    worldMin[2] = std::min(worldMin[2], transformed[2]);
    worldMax[0] = std::max(worldMax[0], transformed[0]);
    worldMax[1] = std::max(worldMax[1], transformed[1]);
    worldMax[2] = std::max(worldMax[2], transformed[2]);
  }
}

Vector3 AABB::getFarthestExtent(const Vector3& direction)
{
  Vector3 farthestPoint;
  Vector3 worldHalfExtents = getHalfExtents();

  Vector3 farthestDiagonal = Vector3(
    worldHalfExtents[0] * ((direction[0] > 0.0f) * 2.0f - 1.0f),
    worldHalfExtents[1] * ((direction[1] > 0.0f) * 2.0f - 1.0f),
    worldHalfExtents[2] * ((direction[2] > 0.0f) * 2.0f - 1.0f)
  );

  farthestPoint = direction * farthestDiagonal.dot(direction);

  return farthestPoint;
}

Vector3 AABB::getSurfacePoint(const Vector3& direction)
{
  Vector3 surfacePoint;
  Vector3 worldHalfExtents = getHalfExtents();
  Vector3 localHalfExtents = getLocalHalfExtents();

  Vector3 projectedLengths = direction / worldHalfExtents;
  int maxIndex = projectedLengths.abs().getMaxIndex();
  float scaling = fabs(localHalfExtents[maxIndex] / (projectedLengths[maxIndex]));

  surfacePoint = projectedLengths * scaling * (worldHalfExtents / localHalfExtents);

  return surfacePoint;
}

Vector3 AABB::getNormalAtVector(const Vector3& direction)
{
  if (fabs(direction.x) > fabs(direction.y)) {
    if (fabs(direction.x) > fabs(direction.z)) {
      return Vector3(1, 0, 0) * ((direction.x >= 0.0f) * 2.0f - 1.0f);
    }
    else {
      return Vector3(0, 0, 1) * ((direction.z >= 0.0f) * 2.0f - 1.0f);
    }
  }
  else {
    if (fabs(direction.y) > fabs(direction.z)) {
      return Vector3(0, 1, 0) * ((direction.y >= 0.0f) * 2.0f - 1.0f);
    }
    else {
      return Vector3(0, 0, 1) * ((direction.z >= 0.0f) * 2.0f - 1.0f);
    }
  }
}



// Utility functions
Vector3 AABB::getMin()          const { return worldMin; }
Vector3 AABB::getMax()          const { return worldMax; }
Vector3 AABB::getCenter()       const { return (worldMin + worldMax) * 0.5f; }
Vector3 AABB::getHalfExtents()  const { return (worldMax - worldMin) * 0.5f; }
Vector3 AABB::getLocalHalfExtents() const { return (localMax - localMax) * 0.5f; }
float   AABB::getWidth()        const { return worldMax[0] - worldMin[0]; }
float   AABB::getHeight()       const { return worldMax[1] - worldMin[1]; }
float   AABB::getDepth()        const { return worldMax[2] - worldMin[2]; }

void AABB::initializeDebugDraw(
  std::shared_ptr<RenderGraph> renderGraph, std::shared_ptr<Camera> camera) {
  this->renderGraph = renderGraph;
  this->camera = camera;
  // Get debug shape
  debugMesh = Mesh::getShapeMesh(Mesh::Cube);

  // Get debug material
  debugMaterial = Material::getMaterial<DebugMaterial>("Debug", renderGraph);

  renderGraph->addPass<DebugPass>("DebugPass");
}

void AABB::debugDaw() {
  assert(("AABB::DEBUGDRAW::NOT_IMPLEMENTED") && false);

  // Todo: Need to rework the entire debug draw system to work with the new
  // render system.

  //assert(("AABB::DEBUGDRAW::NOT_INITIALIZED") && renderGraph);

  //const Vector3 worldHalfExtents = this->getHalfExtents();
  //const Vector3 worldCenter = this->getCenter();

  //// Create model matrix that will transform our normalized box to the OBB's position and orientation
  //Matrix4 scale = Matrix4::scale(worldHalfExtents.x * 2, worldHalfExtents.y * 2, worldHalfExtents.z * 2);
  //Matrix4 rotation = Matrix4();
  //Matrix4 translation = Matrix4::translation(
  //  worldCenter.x, worldCenter.y, worldCenter.z);
  //Matrix4 model = translation * rotation * scale;

  //debugMaterial->setProperty("ViewMatrix", camera->getViewMatrix());
  //debugMaterial->setProperty("ProjectionMatrix", camera->getProjectionMatrix());
  //debugMaterial->setProperty("ModelMatrix", model);

  ////debugMaterial->draw(debugMesh);
}

bool AABB::raycastIntersect(const Ray& ray, RaycastHit& hit, float maxDistance) const {

    float tMin = 0.0f;
    float tMax = maxDistance;

    Vector3 bounds[2] = { localMin, localMax };

    for (int i = 0; i < 3; i++) {
        if (ray.getDirection()[i] == 0) {
            if (ray.getOrigin()[i] > bounds[0][i] || ray.getOrigin()[i] > bounds[1][i]) {
                return false;
            }
        }
        else {
            float t1 = (bounds[0][i] - ray.getOrigin()[i]) / ray.getDirection()[i];
            float t2 = (bounds[1][i] - ray.getOrigin()[i]) / ray.getDirection()[i];

            if (t1 > t2) {
                std::swap(t1, t2);
            }

            tMin = std::max(tMin, t1);
            tMax = std::min(tMax, t2);

            if (tMin > tMax) {
                return false;
            }
        }
    }

    hit.distance = tMin;
    hit.point = ray.getOrigin() + (ray.getDirection() * tMin);

    Vector3 center = (localMin + localMax) * 0.5f;
    Vector3 localPoint = hit.point - center;
    Vector3 extents = (localMax - localMin) * 0.5f;

    hit.normal = Vector3(
         (fabs(localPoint.x) > extents.x - 1e-4f) ? copysign(1.0f, localPoint.x) : 0.0f,
        (fabs(localPoint.y) > extents.y - 1e-4f) ? copysign(1.0f, localPoint.y) : 0.0f,
        (fabs(localPoint.z) > extents.z - 1e-4f) ? copysign(1.0f, localPoint.z) : 0.0f
    );

    return true;

}
