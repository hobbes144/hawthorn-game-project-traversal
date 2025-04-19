/*!****************************************************************************
 * \file   TimeControlledRB.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    GAM541
 * \brief  RigidBody component with modified logic to allow handling of time
 * based physics modifications.
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 *
 *****************************************************************************/
#ifndef TIME_CONTROLLED_RB_H
#define TIME_CONTROLLED_RB_H

#pragma once

#include "RigidBody.h"

class TimeControlledRB : public RigidBody {
public:
	TimeControlledRB() : RigidBody(), timeScale(1.0f) {}

	void initialize() {
		RigidBody::initialize();
	}

	void setTimeScale(float _timeScale) {
		timeScale = _timeScale;
	}

	float getTimeScale() {
		return timeScale;
	}
	
	void integrate(float deltaTime);

private:
	float timeScale;
};

#endif // !TIME_CONTROLLED_RB_H