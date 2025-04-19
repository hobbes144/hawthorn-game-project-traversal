/*!****************************************************************************
 * \file   Door.h
 * \author Daoming Wang (daoming.wang@digipen.edu)
 * \brief  Doors
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#ifndef DOOR_H
#define DOOR_H

#pragma once

#include "CollisionListener.h"
#include "KeyList.h"
#include "LevelManager.h"
#include "RigidBody.h"
#include "FirstPersonControllerComponent.h"  

class Door : public PhysicsBody {
public:
	enum DoorType {
		SLIDEUP,
		NEXTLEVEL,
		DISAPPEAR,
		SET_DIFFICULTY
	};

	Door() : 
		PhysicsBody(), id(0), LevelSwitched(false), type(DISAPPEAR),
		requiresKey(true), difficultyMode(FirstPersonControllerComponent::NORMAL) {}
	~Door() = default;

	void initialize() override;
	void shutdown() override;

	int getID();
	void setID(int _id);
	DoorType getType();
	void setType(DoorType _type);
	bool getLevelSwitchStatus();
	void setLevelSwitchStatus(bool status);
	bool getRequiresKey();
	void setRequiresKey(bool reqKey);

	FirstPersonControllerComponent::Difficulty getDifficultyMode() const;
	void setDifficultyMode(FirstPersonControllerComponent::Difficulty diffMode);

private:
	int id;
	bool LevelSwitched;
	DoorType type;
	CollisionListener* doorListener;
	bool requiresKey;
	FirstPersonControllerComponent::Difficulty difficultyMode;
};

#endif