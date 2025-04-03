#include "precompiled.h"
#include "Door.h"

void onDoorCollide(std::shared_ptr<GameObject> obj1,
	std::shared_ptr<GameObject> obj2, const Vector3& point) {
	const std::shared_ptr<Door>& D1 = obj1->findComponent<Door>();
	const std::shared_ptr<Door>& D2 = obj2->findComponent<Door>();
	const std::shared_ptr<KeyList>& S1 = obj1->findComponent<KeyList>();
	const std::shared_ptr<KeyList>& S2 = obj2->findComponent<KeyList>();

	if (D1 && S2) {
		if (S2->hasKey(D1->getID())) {
			if (D1->getType() == Door::DoorType::DISAPPEAR) obj1->disable();
			if (D1->getType() == Door::DoorType::NEXTLEVEL) {
				LevelManager::Instance().NextLevel();
			}
		}

	}
	else if (D2 && S1) {
		if (S1->hasKey(D2->getID())) {
			if (D2->getType() == Door::DoorType::DISAPPEAR) obj2->disable();
			if (D2->getType() == Door::DoorType::NEXTLEVEL) {
				LevelManager::Instance().NextLevel();
			}
		}
	}
	return;
}

void Door::initialize() {
	doorListener = new CollisionListener(this->parent);
	doorListener->setCallback(onDoorCollide);
}

int Door::getID() {
	return id;
}


void Door::setID(int _id) {
	id = _id;
}

Door::DoorType Door::getType() {
	return type;
}

void Door::setType(Door::DoorType _type) {
	type = _type;
}

