#include "precompiled.h"
#include "RaycastManager.h"
#include <src/PhysicsBody.h>


/*!
 * @brief This is the primary Raycasting function. It detects the nearest object along the ray.
 * Instruction:
 * 1) Create a Ray with the desired origin and direction
 * 2) Create a RayCastHit Object to store the data
 * 3) Call the funtion
 * @param ray This is the Ray being cast. It contains an origin and a direction
 * @param sceneGraph The scenegraph that the ray is beign cast in, checks each game object in the node
 * @param hit Stores the data of the intersection if one occurs
 * @param maxDistance The max distance the ray is cast
 * @param tagToIgnore A Vector containing Tags of Gameobject that should be ignored for collisions
 * @return Boolean signifying if there was a successful intersection. The data of the intersection is stored in the RaycastHit object
 */
bool RaycastManager::Raycast(const Ray& ray, const SceneGraph* sceneGraph, RaycastHit& hit, float maxDistance, const std::vector<GameObject::Tag> tagToIgnore) {

	return processNode(sceneGraph->getRootNode(), ray, hit, maxDistance, tagToIgnore);

}

/*!
 * @brief Recursivly checks each object for an intersection
 * @param node The node to check for intersection
 * @param ray The Ray being cast
 * @param hit The hit object to store the data
 * @param closeHitDistance distance which to cast the ray
 * @param tagToIgnore The Tags the mark ignorable objects
 * @return Bool if there was an intersection. Hit stores the data of the intersection
 */
bool RaycastManager::processNode(const std::shared_ptr<Node>& node,
                                 const Ray& ray,
                                 RaycastHit& hit,
                                 float& closeHitDistance,
                                 const std::vector<GameObject::Tag> tagToIgnore
) {
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
        if (std::find(tagToIgnore.begin(), tagToIgnore.end(), gameObject->getTag()) == tagToIgnore.end() && pbComp) {
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
        if (processNode(child, ray, hit, closeHitDistance, tagToIgnore)) {
            hasHit = true;
        }
    }

    return hasHit;
}
