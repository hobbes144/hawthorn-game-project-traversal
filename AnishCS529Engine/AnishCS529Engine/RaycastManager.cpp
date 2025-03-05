#include "RaycastManager.h"
#include <src/PhysicsBody.h>

bool RaycastManager::Raycast(const Ray& ray, const SceneGraph* sceneGraph, RaycastHit& hit, float maxDistance) {

	return processNode(sceneGraph->getRootNode(), ray, hit, maxDistance);

}

bool RaycastManager::processNode(const std::shared_ptr<Node>& node,
                                 const Ray& ray,
                                 RaycastHit& hit,
                                 float& closeHitDistance) {
    if (!node) {
        return false;
    }

    bool hasHit = false;
    RaycastHit tempHit;

    // Convert the Ray to the Node's local space
    Matrix4 worldToLocal = node->getWorldTransform().getInverseLocalMatrix();
    Ray localRay = ray.transformRay(worldToLocal);

    // If the node has a physics body, check for intersection
    auto gameObject = std::dynamic_pointer_cast<GameObject>(node);
    if (gameObject) {
        auto pbComp = gameObject->findComponent<PhysicsBody>();
        if (pbComp) {
            if (pbComp->getShape()->raycastIntersect(localRay, tempHit, closeHitDistance)) {

                // Only update if this is the closest hit
                if (tempHit.distance < closeHitDistance) {
                    closeHitDistance = tempHit.distance;

                    // Convert back to world space
                    tempHit.point = node->getWorldTransform().getLocalMatrix() * tempHit.point;
                    tempHit.normal = node->getWorldTransform().getLocalMatrix().transformDirection(tempHit.normal);

                    hit = tempHit;
                    hit.object = gameObject.get();
                    hasHit = true;
                }

            }
        }
    }

    // Recursively check children
    for (const auto& child : node->getChildren()) {
        if (processNode(child, ray, hit, closeHitDistance)) {
            hasHit = true;
        }
    }

    return hasHit;
}
