#include "precompiled.h"
#include "OBB.h"


OBB::OBB(const Vector3& center = Vector3(0, 0, 0),
  const Vector3& halfExtents = Vector3(0.5f, 0.5f, 0.5f))
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

void OBB::update(Transform& transform) {
  // Get the transform matrix once
  unscaledWorldCenter = transform.getPosition();
  worldCenter = transform.getPosition() * transform.getScaling();

  // Update orientation vectors using rotation only
  // We can get this directly from the transform's rotation
  Matrix4 transformMatrix = transform.getLocalMatrix();

  // Todo: Figure out what this is for:
  float angle = transform.getRotation().z; // For 2D we only need Z rotation
  
  worldAxes[0] = Vector3(transformMatrix.getElement(0, 0), transformMatrix.getElement(1, 0), transformMatrix.getElement(2, 0)).normalized();
  worldAxes[1] = Vector3(transformMatrix.getElement(0, 1), transformMatrix.getElement(1, 1), transformMatrix.getElement(2, 1)).normalized();
  worldAxes[2] = Vector3(transformMatrix.getElement(0, 2), transformMatrix.getElement(1, 2), transformMatrix.getElement(2, 2)).normalized();
  worldRight = worldAxes[0];
  worldUp = worldAxes[1];

  // Update half extents with scale
  Vector3 scale = transform.getScaling();
  worldHalfExtents = Vector3(
    localHalfExtents.x * std::abs(scale.x),
    localHalfExtents.y * std::abs(scale.y),
    localHalfExtents.z * std::abs(scale.z)
  );
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
  debugMaterial = Material::getMaterial<DebugMaterial>("Debug", renderGraph);

  renderGraph->addPass<DebugPass>("DebugPass");
}

void OBB::debugDaw() {
  assert(("OBB::DEBUGDRAW::NOT_INITIALIZED") && renderGraph);

  const Vector3 worldHalfExtents = this->getHalfExtents();
  const Vector3 worldCenter = this->getCenter();

  // Create model matrix that will transform our normalized box to the OBB's position and orientation
  Matrix4 scale = Matrix4::scale(worldHalfExtents.x * 2, worldHalfExtents.y * 2, worldHalfExtents.z * 2);
  Matrix4 rotation = Matrix4(
    worldAxes[0].x, worldAxes[0].y, worldAxes[0].z, 0.0f,
    worldAxes[1].x, worldAxes[1].y, worldAxes[1].z, 0.0f,
    worldAxes[2].x, worldAxes[2].y, worldAxes[2].z, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
  Matrix4 translation = Matrix4::translation(
    unscaledWorldCenter.x, unscaledWorldCenter.y, unscaledWorldCenter.z);
  Matrix4 model = translation * rotation * scale;

  debugMaterial->setProperty("ViewMatrix", camera->getViewMatrix());
  debugMaterial->setProperty("ProjectionMatrix", camera->getProjectionMatrix());
  debugMaterial->setProperty("ModelMatrix", model);

  debugMaterial->draw(debugMesh);
}

bool OBB::raycastIntersect(const Ray& ray, RaycastHit& hit, float maxDistance) const {
    const Vector3* axes = localAxes;
    const Vector3 halfExtents = localHalfExtents;

    Vector3 rayOrigin = ray.getOrigin();

    //-------------
    // Hueristically Check if the Object is too far away
    
    if (!(std::abs(rayOrigin.x) - halfExtents.x <= maxDistance &&
          std::abs(rayOrigin.y) - halfExtents.y <= maxDistance &&
          std::abs(rayOrigin.z) - halfExtents.z <= maxDistance
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

