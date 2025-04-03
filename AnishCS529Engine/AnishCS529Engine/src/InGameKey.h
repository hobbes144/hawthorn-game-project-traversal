#ifndef INGAMEKEY_H
#define INGAMEKEY_H

#pragma once

#include "CollisionListener.h"
#include "KeyList.h"
#include "RigidBody.h"

class InGameKey : public RigidBody {
public:
	InGameKey() : id(0), RigidBody() {}
	~InGameKey() = default;

	void initialize();

	int getID();
	void setID(int _id);

private:
	int id;
	CollisionListener* keyListener;
};

#endif
