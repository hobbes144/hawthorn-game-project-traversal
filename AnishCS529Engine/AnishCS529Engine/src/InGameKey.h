/*!****************************************************************************
 * \file   InGameKey.h
 * \author Daoming Wang (daoming.wang@digipen.edu) (Controller and Pause menu)
 * \brief  Keys to open doors
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#ifndef INGAMEKEY_H
#define INGAMEKEY_H

#pragma once

#include "CollisionListener.h"
#include "KeyList.h"
#include "PauseMenu.h"
#include "PhysicsBody.h"

class InGameKey : public PhysicsBody {
public:
	InGameKey() : id(0), listener(nullptr), PhysicsBody() {}
	~InGameKey() = default;

	void initialize() override;
	void shutdown() override;

	int getID();
	void setID(int _id);

private:
	int id;
	CollisionListener* listener;
};

#endif
