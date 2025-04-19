/*!****************************************************************************
 * \file   TimeControlledRB.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    GAM541
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 *
 *****************************************************************************/
#include "precompiled.h"
#include "TimeControlledRB.h"

void TimeControlledRB::integrate(float deltaTime) {
	assert((timeScale > 0.0f) && "Timescale cannot be negative, not supported yet.");
	RigidBody::integrate(deltaTime * timeScale);
}
