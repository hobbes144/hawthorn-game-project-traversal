#ifndef INGAMEKEY_H
#define INGAMEKEY_H

#pragma once

#include "CollisionListener.h"
#include "KeyList.h"
#include "RigidBody.h"
#include "PauseMenu.h"

class InGameKey : public PhysicsBody {
public:
	InGameKey() : id(0), listener(nullptr), PhysicsBody() {}
	~InGameKey() = default;

	void initialize();

	int getID();
	void setID(int _id);

private:
	int id;
	CollisionListener* listener;
};

#endif
