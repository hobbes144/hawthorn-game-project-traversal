#include "precompiled.h"
#include "OBB.h"


OBB::OBB(const Vector3& center,
  const Vector3& halfExtents)
  : localCenter(center), localHalfExtents(halfExtents),
  unscaledWorldCenter(center),
  worldCenter(center), worldHalfExtents(halfExtents) {

  // Initialize right and up vectors for 2D
  localAxes[0] = worldAxes[0] = Vector3(1, 0, 0);
  localAxes[1] = worldAxes[1] = Vector3(0, 1, 0);
  localAxes[2] = worldAxes[2] = Vector3(0, 0, 1);
  localRight = worldRight = localAxes[0];
  localUp = worldUp = localAxes[1];
  localFront = worldFront = localAxes[2];
}

Shape::Type OBB::getType() const {
  return Type::OBB;
}

void OBB::update(const Transform& transform) {
  // Update orientation vectors using rotation only
  // We can get this directly from the transform's rotation
  Matrix4 transformMatrix = transform.getLocalMatrix();
  
  unscaledWorldCenter = transform.getPosition() + localCenter;
  worldCenter = localCenter + Vector3(transformMatrix.getElement(0, 3), transformMatrix.getElement(1, 3), transformMatrix.getElement(2, 3));
  //worldCenter = transform.getPosition() + (rotation * localCenter * transform.getScaling());

  rotation = transform.getRotation();
  worldAxes[0] = worldRight = rotation.getAxis(0);
  worldAxes[1] = worldUp = rotation.getAxis(1);
  worldAxes[2] = worldFront = rotation.getAxis(2);

  // Update half extents with scale
  Vector3 scale = transform.getScaling();
  worldHalfExtents = Vector3(
    localHalfExtents.x * std::abs(scale.x),
    localHalfExtents.y * std::abs(scale.y),
    localHalfExtents.z * std::abs(scale.z)
  );
}

Vector3 OBB::getFarthestExtent(const Vector3& direction) {
  Vector3 farthestPoint;

  Vector3 projectedPoint = rotation * direction;
  Vector3 farthestDiagonal = Vector3(
    worldHalfExtents[0] * ((projectedPoint[0] > 0) * 2 - 1),
    worldHalfExtents[1] * ((projectedPoint[1] > 0) * 2 - 1),
    worldHalfExtents[2] * ((projectedPoint[2] > 0) * 2 - 1)
  );

  Vector3 reprojectedDiagonal = rotation.inverse() * farthestDiagonal;

  farthestPoint = direction * reprojectedDiagonal.dot(direction);

  return farthestPoint;
}

Vector3 OBB::getSurfacePoint(const Vector3& direction) {
  Vector3 surfacePoint;

  Vector3 projectedLengths = rotation * direction / worldHalfExtents;
  int maxIndex = projectedLengths.abs().getMaxIndex();
  float scaling = fabs(localHalfExtents[maxIndex] / (projectedLengths[maxIndex]));

  surfacePoint = projectedLengths * scaling * (worldHalfExtents/localHalfExtents);

  return surfacePoint;
}
  
//  Vector3 support = Vector3();
//  float point;
//  float maxPoint = 0;
//  int maxDirection;
//  int sign = 0;
//
//  // Move along each principal axis in the direction that maximizes projection
//  for (int i = 0; i < 3; i++) {
//    point = direction.dot(worldAxes[i]) * worldHalfExtents[i];
//    support[i] = point;
//    if (fabs(point) > maxPoint) {
//      maxPoint = fabs(point);
//      maxDirection = i;
//      sign = (point >= 0);
//    }
//  }
//
//  support[maxDirection] = worldHalfExtents[maxDirection] * (sign*2 - 1);
//
//  return support;
//}

Vector3 OBB::getNormalAtVector(const Vector3& direction)
{
  Vector3 rotatedDirection = (rotation * direction);
  double projX = static_cast<double>(rotatedDirection.x) / static_cast<double>(worldHalfExtents.x);
  double projY = static_cast<double>(rotatedDirection.y) / static_cast<double>(worldHalfExtents.y);
  double projZ = static_cast<double>(rotatedDirection.z) / static_cast<double>(worldHalfExtents.z);
  Vector3 projectedDirection = ( rotation * direction ) / worldHalfExtents;
  Vector3 result;
  if (fabs(projectedDirection.x) > fabs(projectedDirection.y)) {
    if (fabs(projectedDirection.x) > fabs(projectedDirection.z)) {
      result = worldAxes[0] * ((projectedDirection.x >= 0) * 2 - 1);
    }
    else {
      result = worldAxes[2] * ((projectedDirection.z >= 0) * 2 - 1);
    }
  }
  else {
    if (fabs(projectedDirection.y) > fabs(projectedDirection.z)) {
      result = worldAxes[1] * ((projectedDirection.y >= 0) * 2 - 1);
    }
    else {
      result = worldAxes[2] * ((projectedDirection.z >= 0) * 2 - 1);
    }
  }
  return result;
}

Vector3 OBB::getNormalClosestToPoint(const Vector3& point)
{
  Vector3 halfExtents = getHalfExtents();
  if ((halfExtents.x - fabs(point.x)) < (halfExtents.y - fabs(point.y))) {
    if ((halfExtents.x - fabs(point.x)) < (halfExtents.z - fabs(point.z))) {
      return Vector3(1, 0, 0) * ((point.x >= 0.0f) * 2.0f - 1.0f);
    }
    else {
      return Vector3(0, 0, 1) * ((point.z >= 0.0f) * 2.0f - 1.0f);
    }
  }
  else {
    if ((halfExtents.y - fabs(point.y)) < (halfExtents.z - fabs(point.z))) {
      return Vector3(0, 1, 0) * ((point.y >= 0.0f) * 2.0f - 1.0f);
    }
    else {
      return Vector3(0, 0, 1) * ((point.z >= 0.0f) * 2.0f - 1.0f);
    }
  }
  return Vector3();
}

void OBB::getCorners(Vector3 corners[4]) const {
  Vector3 offsets[3] = {
    worldAxes[0] * worldHalfExtents.x,
    worldAxes[1] * worldHalfExtents.y,
    worldAxes[2] * worldHalfExtents.z
  };

  corners[0] = worldCenter - offsets[0] - offsets[1] - offsets[2]; // Bottom-left-Front
  corners[1] = worldCenter + offsets[0] - offsets[1] - offsets[2]; // Bottom-right-Front
  corners[2] = worldCenter + offsets[0] + offsets[1] - offsets[2]; // Top-right-Front
  corners[3] = worldCenter - offsets[0] + offsets[1] - offsets[2]; // Top-left-Front
  corners[0] = worldCenter - offsets[0] - offsets[1] + offsets[2]; // Bottom-left-Back
  corners[1] = worldCenter + offsets[0] - offsets[1] + offsets[2]; // Bottom-right-Back
  corners[2] = worldCenter + offsets[0] + offsets[1] + offsets[2]; // Top-right-Back
  corners[3] = worldCenter - offsets[0] + offsets[1] + offsets[2]; // Top-left-Back
}

void OBB::project(const Vector3& axis, float& min, float& max) const {
  // Get absolute position of corners in world space
  Vector3 corners[8];
  getCorners(corners);

  // Project directly onto axis
  min = max = corners[0].dot(axis);

  for (int i = 1; i < 8; i++) {
    float proj = corners[i].dot(axis);
    min = std::min(min, proj);
    max = std::max(max, proj);
  }

}

Vector3 OBB::getCenter()	      const { return worldCenter; }
Vector3 OBB::getHalfExtents()   const { return worldHalfExtents; }
Vector3 OBB::getRight()		      const { return worldRight; }
Vector3 OBB::getUp()		        const { return worldUp; }
Vector3 OBB::getFront()		      const { return worldFront; }
const Vector3* OBB::getAxes()   const { return worldAxes; }

void OBB::initializeDebugDraw(
  std::shared_ptr<RenderGraph> renderGraph, std::shared_ptr<Camera> camera) {
  this->renderGraph = renderGraph;
  this->camera = camera;
  // Get debug shape
  debugMesh = Mesh::getShapeMesh(Mesh::Cube);

  // Get debug material
  debugMaterial = Material::getMaterial<DebugMaterial>("Debug");

  //renderGraph->addPass<DebugPass>("DebugPass");
}

void OBB::debugDaw() {
  assert(("OBB::DEBUGDRAW::NOT_IMPLEMENTED") && false);

  // Todo: Need to rework the entire debug draw system to work with the new
  // render system.

  //assert(("OBB::DEBUGDRAW::NOT_INITIALIZED") && renderGraph);

  //const Vector3 worldHalfExtents = this->getHalfExtents();
  //const Vector3 worldCenter = this->getCenter();

  //// Create model matrix that will transform our normalized box to the OBB's position and orientation
  //Matrix4 scale = Matrix4::scale(worldHalfExtents.x * 2, worldHalfExtents.y * 2, worldHalfExtents.z * 2);
  //Matrix4 rotation = Matrix4(
  //  worldAxes[0].x, worldAxes[0].y, worldAxes[0].z, 0.0f,
  //  worldAxes[1].x, worldAxes[1].y, worldAxes[1].z, 0.0f,
  //  worldAxes[2].x, worldAxes[2].y, worldAxes[2].z, 0.0f,
  //  0.0f, 0.0f, 0.0f, 1.0f
  //);
  //Matrix4 translation = Matrix4::translation(
  //  unscaledWorldCenter.x, unscaledWorldCenter.y, unscaledWorldCenter.z);
  //Matrix4 model = translation * rotation * scale;

  //debugMaterial->setProperty("ViewMatrix", camera->getViewMatrix());
  //debugMaterial->setProperty("ProjectionMatrix", camera->getProjectionMatrix());
  //debugMaterial->setProperty("ModelMatrix", model);

  //debugMaterial->draw(debugMesh);
}

bool OBB::raycastIntersect(const Ray& ray, RaycastHit& hit, float maxDistance) const {
    const Vector3* axes = localAxes;
    const Vector3 halfExtents = localHalfExtents;

    Vector3 rayOrigin = ray.getOrigin();
    Vector3 rayDir = ray.getDirection();

    /*
    //-------------
    // Hueristically Check if the Object is too far away
    if (!(std::abs(rayOrigin.x) - halfExtents.x <= maxDistance &&
          std::abs(rayOrigin.y) - halfExtents.y <= maxDistance &&
          std::abs(rayOrigin.z) - halfExtents.z <= maxDistance
        )) {
        return false;
    }
    //-------------
    */

    //------------- 
    // Hueristically Check if the ray is pointing away
    
    if (((rayOrigin.x > halfExtents.x && rayDir.x > 0) || (rayOrigin.x < -halfExtents.x && rayDir.x < 0) ||
        (rayOrigin.y > halfExtents.y && rayDir.y > 0) || (rayOrigin.y < -halfExtents.y && rayDir.y < 0) ||
        (rayOrigin.z > halfExtents.z && rayDir.z > 0) || (rayOrigin.z < -halfExtents.z && rayDir.z < 0)
        )) {
        return false;
    }
    
    //-------------

    //-------------
    //Check if the origin is in the bounding box
    if (((rayOrigin.x >= -halfExtents.x && rayOrigin.x <= halfExtents.x) &&
        (rayOrigin.y >= -halfExtents.y && rayOrigin.y <= halfExtents.y) &&
        (rayOrigin.z >= -halfExtents.z && rayOrigin.z <= halfExtents.z))) {
        return false;
    }
    //-------------

    Vector3 p = ray.getOrigin(); 

    float tMin = -std::numeric_limits<float>::infinity();
    float tMax = std::numeric_limits<float>::infinity();
    int hitAxis = -1;

    for (int i = 0; i < 3; ++i) {
        Vector3 currAxis = axes[i];
        float currHalfExtents = halfExtents[i];

        float minBound = -currHalfExtents;
        float maxBound = currHalfExtents;
        float originComponent = ray.getOrigin()[i];
        float dirComponent = ray.getDirection()[i];

        // Ray is parallel to slab
        if (std::abs(dirComponent) < 1e-6) { 
            if (originComponent < minBound || originComponent > maxBound) {
                return false; // Outside the slab
            }
            continue;
        }

        float t1 = (minBound - originComponent) / dirComponent;
        float t2 = (maxBound - originComponent) / dirComponent;

        if (t1 > t2) std::swap(t1, t2);

        if (t1 > tMin) {
            tMin = t1;
            hitAxis = i;
        }

        tMax = std::min(tMax, t2);

        if (tMin > tMax || tMax < 0) {
            return false;
        }
    }

    hit.point = ray.getOrigin() + ray.getDirection() * tMin;
    hit.distance = tMin;

    switch (hitAxis) {
    case 0:
        hit.normal.x = (hit.point.x > 0.f) ? 1.f : -1.f;
        break;
    case 1:
        hit.normal.y = (hit.point.y > 0.f) ? 1.f : -1.f;
        break;
    case 2:
        hit.normal.z = (hit.point.z > 0.f) ? 1.f : -1.f;
        break;
    default:
        break;
    }

    return true;

}

