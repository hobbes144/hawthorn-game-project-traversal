#include "precompiled.h"
#include "InGameKey.h"

void onKeyCollide(std::shared_ptr<GameObject> obj1,
	std::shared_ptr<GameObject> obj2, const Vector3& point) {
	const std::shared_ptr<InGameKey>& K1 = obj1->findComponent<InGameKey>();
	const std::shared_ptr<InGameKey>& K2 = obj2->findComponent<InGameKey>();
	const std::shared_ptr<KeyList>& S1 = obj1->findComponent<KeyList>();
	const std::shared_ptr<KeyList>& S2 = obj2->findComponent<KeyList>();

	if (K1 && S2) {
		S2->addKey(K1->getID());
		obj1->disable();
	}
	else if (K2 && S1) {
		S1->addKey(K2->getID());
		obj2->disable();
	}
	return;
}

void InGameKey::initialize() {
	keyListener = new CollisionListener(this->parent);
	keyListener->setCallback(onKeyCollide);
}

int InGameKey::getID() {
	return id;
}

void InGameKey::setID(int _id) {
	id = _id;
}