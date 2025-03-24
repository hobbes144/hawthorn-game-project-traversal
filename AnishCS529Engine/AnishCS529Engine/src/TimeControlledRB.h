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
	
	void integrate(float deltaTime);

private:
	float timeScale;
};

#endif // !TIME_CONTROLLED_RB_H