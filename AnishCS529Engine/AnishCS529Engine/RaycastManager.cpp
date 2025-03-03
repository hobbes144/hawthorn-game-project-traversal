#include "RaycastManager.h"
#include <src/PhysicsBody.h>

bool RaycastManager::Raycast(const Ray& ray, const SceneGraph* sceneGraph, RaycastHit& hit, float maxDistance = FLT_MAX) {

	return processNode(sceneGraph->getRootNode(), ray, hit, maxDistance);

}

bool RaycastManager::processNode(const std::shared_ptr<Node>& node,
					 const Ray& ray,
					 RaycastHit& hit,
					 float& closeHitDistance) {

	//Confirm that node exists
	if (!node) {
		return false;
	}

	bool hasHit = false;
	RaycastHit tempHit;

	//Convert the Ray to the Node's local space
	Matrix4 worldToLocal = node->getWorldTransform().getInverseLocalMatrix();
	Ray localRay = ray.transformRay(worldToLocal);

	//If the node has a physics body, check for intersection
	auto gameObject = std::dynamic_pointer_cast<GameObject>(node);
	if (gameObject) {
		auto pbComp = gameObject->findComponent<PhysicsBody>();
		if (pbComp && pbComp->getShape()->raycastIntersect(localRay, tempHit, closeHitDistance)) { //TODO: MIGHT NOT BE CLOSEHIT DISTANCE
			
			tempHit.point = node->getTransformMatrix() * tempHit.point;
			tempHit.normal = node->getTransformMatrix().transformDirection(tempHit.normal);
			closeHitDistance = tempHit.distance;
			hit = tempHit;
			hasHit = true;

		}
	}

	//Recursivly check children
	for (const auto child : node->getChildren()) {
		if (processNode(child, ray, hit, closeHitDistance)) {
			hasHit = true;
		}
	}

}
