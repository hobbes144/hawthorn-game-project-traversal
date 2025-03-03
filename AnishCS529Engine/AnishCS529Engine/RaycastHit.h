/*!****************************************************************************
 * \file   RaycastHit.h
 * \author Nicholas Shaw (nick_shaw@me.com)
 * \par    **DigiPen Email**
 *    nick.shaw@digipen.edu
 * \par    **Course**
 *    GAM541
 * \date   03-01-2025
 * \brief  This is the class representing the hit of a raycast
 * 
 *****************************************************************************/
#ifndef RAYCAST_HIT
#define RAYCAST_HIT

#pragma once

#include "src/Vector3.h"
#include "src/GameObject.h"

class RaycastHit
{

public:
	Vector3 point;
	Vector3 normal;
	float distance;
	GameObject* object;

};

#endif // !RAYCAST_HIT
