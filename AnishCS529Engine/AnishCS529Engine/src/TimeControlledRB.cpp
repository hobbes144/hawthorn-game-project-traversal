#include "precompiled.h"
#include "TimeControlledRB.h"

void TimeControlledRB::integrate(float deltaTime) {
	assert((timeScale > 0.0f) && "Timescale cannot be negative, not supported yet.");
	RigidBody::integrate(deltaTime * timeScale);
}
