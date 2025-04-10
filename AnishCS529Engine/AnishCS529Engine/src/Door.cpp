#include "precompiled.h"
#include "Door.h"
#include "LevelManager.h"

FirstPersonControllerComponent::Difficulty Door::getDifficultyMode() const {
	return difficultyMode;
}

void Door::setDifficultyMode(FirstPersonControllerComponent::Difficulty diffMode) {
	difficultyMode = diffMode;
}

void onDoorCollide(std::shared_ptr<GameObject> obj1,
				   std::shared_ptr<GameObject> obj2, const Vector3& point) {
	const std::shared_ptr<Door>& D1 = obj1->findComponent<Door>();
	const std::shared_ptr<Door>& D2 = obj2->findComponent<Door>();

	// Get the FPC from both objects.
	const std::shared_ptr<FirstPersonControllerComponent> fpc1 = obj1->findComponent<FirstPersonControllerComponent>();
	const std::shared_ptr<FirstPersonControllerComponent> fpc2 = obj2->findComponent<FirstPersonControllerComponent>();

	// Get KeyList component
	const std::shared_ptr<KeyList>& keyList1 = obj1->findComponent<KeyList>();
	const std::shared_ptr<KeyList>& keyList2 = obj2->findComponent<KeyList>();


	auto difficultyToString = [](FirstPersonControllerComponent::Difficulty d) -> std::string {
		switch (d) {
		case FirstPersonControllerComponent::EASY:      return "EASY";
		case FirstPersonControllerComponent::NORMAL:    return "NORMAL";
		case FirstPersonControllerComponent::HARD:      return "HARD";
		case FirstPersonControllerComponent::CHEATING:  return "CHEATING";
		default:                                        return "UNKNOWN";
		}
		};
	// Key check logic.
	auto keyCheckPassed = [](const std::shared_ptr<Door>& door, const std::shared_ptr<KeyList>& keys) -> bool {
		return !door->getRequiresKey() || (keys && keys->hasKey(door->getID()));
		};

	if (D1 && fpc2) {
		bool canOpen = keyCheckPassed(D1, keyList2);
		if (D1->getType() == Door::SET_DIFFICULTY) {
			if (canOpen) {
				// Set the player's difficulty.
				FirstPersonControllerComponent::Difficulty diffMode = D1->getDifficultyMode();
				fpc2->setDifficulty(diffMode);
				LevelManager::Instance().SetPlayerDifficulty(D1->getDifficultyMode());

				std::cout << "Difficulty set to: " << difficultyToString(diffMode) << std::endl;
				// Trigger next level
				if (!D1->getLevelSwitchStatus()) {
					LevelManager::Instance().NextLevel();
					D1->setLevelSwitchStatus(true);
				}
				obj1->disable();
			}
		}
		else {
			if (canOpen) {
				if (D1->getType() == Door::SLIDEUP) {
					Vector3 velocity = Vector3(0.0f, 2.5f, -5.0f);
					Vector3 startPos = obj1->getLocalPosition();
					obj1->addComponent<Animate>()->setAnimateFunction(
						[velocity, startPos, time = 0.0f](std::shared_ptr<GameObject> self, float dt) mutable {
							time += dt;
							if (time >= 2.0f) {
								self->setLocalPosition(startPos + velocity * time);
								time = 0.0f;
							}
							else {
								self->setLocalPosition(self->getLocalPosition() + velocity * dt);
							}
						}
					)->runAnimateFunction(true);
				}
				if (D1->getType() == Door::DISAPPEAR)
					obj1->disable();
				if (D1->getType() == Door::NEXTLEVEL && !D1->getLevelSwitchStatus()) {
					LevelManager::Instance().NextLevel();
					D1->setLevelSwitchStatus(true);
				}
			}
		}
	}
	else if (D2 && fpc1) {
		bool canOpen = keyCheckPassed(D2, keyList1);
		if (D2->getType() == Door::SET_DIFFICULTY) {
			if (canOpen) {
				FirstPersonControllerComponent::Difficulty diffMode = D2->getDifficultyMode();
				fpc1->setDifficulty(diffMode);
				LevelManager::Instance().SetPlayerDifficulty(diffMode);
				std::cout << "Difficulty set to: " << difficultyToString(diffMode) << std::endl;
				if (!D2->getLevelSwitchStatus()) {
					LevelManager::Instance().NextLevel();
					D2->setLevelSwitchStatus(true);
				}
				obj2->disable();
			}
		}
		else {
			if (canOpen) {
				if (D2->getType() == Door::SLIDEUP) {
					Vector3 velocity = Vector3(0.0f, 2.5f, -5.0f);
					Vector3 startPos = obj2->getLocalPosition();
					obj2->addComponent<Animate>()->setAnimateFunction(
						[velocity, startPos, time = 0.0f](std::shared_ptr<GameObject> self, float dt) mutable {
							time += dt;
							if (time >= 2.0f) {
								self->setLocalPosition(startPos + velocity * time);
								time = 0.0f;
							}
							else {
								self->setLocalPosition(self->getLocalPosition() + velocity * dt);
							}
						}
					)->runAnimateFunction(true);
				}
				if (D2->getType() == Door::DISAPPEAR)
					obj2->disable();
				if (D2->getType() == Door::NEXTLEVEL && !D2->getLevelSwitchStatus()) {
					LevelManager::Instance().NextLevel();
					D2->setLevelSwitchStatus(true);
				}
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