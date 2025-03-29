#ifndef KEY_H
#define KEY_H

#pragma once

#include "CollisionListener.h"
#include "KeyList.h"
#include "RigidBody.h"

class Key : public RigidBody {
public:
	Key(int _id) : id(_id), RigidBody() {}
	~Key() = default;

	void initialize();

	int getID() {
		return id;
	}

private:
	int id;
	CollisionListener* keyListener;
};

#endif
