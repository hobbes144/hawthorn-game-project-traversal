#include "precompiled.h"
#include "Door.h"

void onDoorCollide(std::shared_ptr<GameObject> obj1,
	std::shared_ptr<GameObject> obj2, const Vector3& point) {
	const std::shared_ptr<Door>& D1 = obj1->findComponent<Door>();
	const std::shared_ptr<Door>& D2 = obj2->findComponent<Door>();
	const std::shared_ptr<KeyList>& S1 = obj1->findComponent<KeyList>();
	const std::shared_ptr<KeyList>& S2 = obj2->findComponent<KeyList>();

	if (D1) {
		bool canOpen = !D1->getRequiresKey() || (S2 && S2->hasKey(D1->getID()));
		if (canOpen) {
			if (D1->getType() == Door::DoorType::DISAPPEAR) obj1->disable();
			if (D1->getType() == Door::DoorType::NEXTLEVEL && !D1->getLevelSwitchStatus()) {
				LevelManager::Instance().NextLevel();
				D1->setLevelSwitchStatus(true);
			}
		}
	}
	else if (D2) {
		bool canOpen = !D2->getRequiresKey() || (S1 && S1->hasKey(D2->getID()));
		if (canOpen) {
			if (D2->getType() == Door::DoorType::DISAPPEAR) obj2->disable();
			if (D2->getType() == Door::DoorType::NEXTLEVEL && !D2->getLevelSwitchStatus()) {
				LevelManager::Instance().NextLevel();
				D2->setLevelSwitchStatus(true);
			}
		}
	}
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

bool Door::getLevelSwitchStatus() {
	return LevelSwitched;
}

void Door::setLevelSwitchStatus(bool status) {
	LevelSwitched = status;
}

bool Door::getRequiresKey() {
	return requiresKey;
}

void Door::setRequiresKey(bool reqKey) {
	requiresKey = reqKey;
}