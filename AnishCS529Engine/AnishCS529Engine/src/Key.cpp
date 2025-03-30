#include "precompiled.h"
#include "Key.h"

void onKeyCollide(std::shared_ptr<GameObject> obj1,
	std::shared_ptr<GameObject> obj2, const Vector3& point) {
	const std::shared_ptr<Key>& K1 = obj1->findComponent<Key>();
	const std::shared_ptr<Key>& K2 = obj2->findComponent<Key>();
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

void Key::initialize() {
	keyListener = new CollisionListener(this->parent);
	keyListener->setCallback(onKeyCollide);
}

int Key::getID() {
	return id;
}
