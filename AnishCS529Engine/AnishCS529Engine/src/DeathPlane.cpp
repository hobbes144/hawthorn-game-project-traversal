#include "precompiled.h"
#include "DeathPlane.h"

void onDeathCollide(std::shared_ptr<GameObject> obj1,
	std::shared_ptr<GameObject> obj2, const Vector3& point) {
	const std::shared_ptr<FirstPersonControllerComponent>& FPC1 = obj1->findComponent<FirstPersonControllerComponent>();
	const std::shared_ptr<FirstPersonControllerComponent>& FPC2 = obj2->findComponent<FirstPersonControllerComponent>();
	const std::shared_ptr<DeathPlane>& S1 = obj1->findComponent<DeathPlane>();
	const std::shared_ptr<DeathPlane>& S2 = obj2->findComponent<DeathPlane>();

	if (FPC1 && S2) {
		if (obj1->getName() == S2->getPlayerName()) {
			FPC1->takeDamage();
		}
	}
	else if (FPC2 && S1) {
		if (obj2->getName() == S1->getPlayerName()) {
			FPC2->takeDamage();
		}
	}
	return;
}

void DeathPlane::initialize() {
	deathListener = new CollisionListener(this->parent);
	deathListener->setCallback(onDeathCollide);
}

void DeathPlane::shutdown()
{
	delete deathListener;
}

void DeathPlane::setPlayerName(std::string name){
	playerName = name;
}

std::string DeathPlane::getPlayerName() {
	return playerName;
}