#ifndef DEATHPLANE_H
#define DEATHPLANE_H

#pragma once

#include <cassert>
#include <functional>

#include "CollisionListener.h"
#include "RigidBody.h"
#include "FirstPersonControllerComponent.h"

class DeathPlane : public RigidBody {
public:
	DeathPlane() : RigidBody() {}
	~DeathPlane() = default;

	void initialize();

	void setPlayerName(std::string name);
	std::string getPlayerName();

private:
	std::string playerName;
	CollisionListener* deathListener;
};

#endif
