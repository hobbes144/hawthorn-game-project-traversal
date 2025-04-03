#ifndef DOOR_H
#define DOOR_H

#pragma once

#include "CollisionListener.h"
#include "KeyList.h"
#include "LevelManager.h"
#include "RigidBody.h"

class Door : public RigidBody {
public:
	enum DoorType {
		SLIDEUP,
		NEXTLEVEL,
		DISAPPEAR
	};

	Door() : id(0), LevelSwitched(false), type(DISAPPEAR), RigidBody() {}
	~Door() = default;

	void initialize();

	int getID();
	void setID(int _id);
	DoorType getType();
	void setType(DoorType _type);
	bool getLevelSwitchStatus();
	void setLevelSwitchStatus(bool status);

private:
	int id;
	bool LevelSwitched;
	DoorType type;
	CollisionListener* doorListener;
};

#endif