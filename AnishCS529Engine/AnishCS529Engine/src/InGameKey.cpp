#include "precompiled.h"
#include "InGameKey.h"
#include "Audio.h"

void onKeyCollide(std::shared_ptr<GameObject> obj1,
	std::shared_ptr<GameObject> obj2, const Vector3& point) {
	const std::shared_ptr<InGameKey>& K1 = obj1->findComponent<InGameKey>();
	const std::shared_ptr<InGameKey>& K2 = obj2->findComponent<InGameKey>();
	const std::shared_ptr<KeyList>& S1 = obj1->findComponent<KeyList>();
	const std::shared_ptr<KeyList>& S2 = obj2->findComponent<KeyList>();

	if (K1 && S2) {
		S2->addKey(K1->getID());	
		AudioManager::instance().playSound("key", obj1->getWorldPosition(), PauseMenu::Instance().getSFXVolume());
		std::cout << "1";
		obj1->disable();
	}
	else if (K2 && S1) {
		S1->addKey(K2->getID());
		AudioManager::instance().playSound("key", obj2->getWorldPosition(), PauseMenu::Instance().getSFXVolume());
		std::cout << "2";
		obj2->disable();
	}
	return;
}

void InGameKey::initialize() {
	listener = new CollisionListener(this->parent);
	listener->setCallback(onKeyCollide);
}

void InGameKey::shutdown()
{
	delete listener;
}

int InGameKey::getID() {
	return id;
}

void InGameKey::setID(int _id) {
	id = _id;
}