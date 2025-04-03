#ifndef DEATHPLANE_H
#define DEATHPLANE_H

#pragma once

#include "CollisionListener.h"
#include "RigidBody.h"
#include "FirstPersonControllerComponent.h"

class DeathPlane : public RigidBody {
public:
	DeathPlane() : RigidBody() {}
	~DeathPlane() = default;

	void initialize();

	std::shared_ptr<DeathPlane> setPlayerName(std::string name);
	std::string getPlayerName();

private:
	std::string playerName;
	CollisionListener* deathListener;
};

#endif
