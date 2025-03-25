/*!****************************************************************************
 * \file   RaycastHit.h
 * \author Nicholas Shaw (nick_shaw@me.com)
 * \par    **DigiPen Email**
 *    nick.shaw@digipen.edu
 * \par    **Course**
 *    GAM541
 * \date   03-01-2025
 * \brief  This is the class representing the hit of a raycast. It stores the
 * data of point of intersection (Vector3), the normal vector of the objected at
 * the point of intersection (Vector3), the distance at which the intersection
 * occured (float), and a pointer to the object that was intersected with 
 * (GameObject*)
 * 
 *****************************************************************************/
#ifndef RAYCAST_HIT
#define RAYCAST_HIT

#pragma once

#include "Vector3.h"
#include "GameObject.h"

class RaycastHit
{

public:
	Vector3 point;
	Vector3 normal;
	float distance;
	std::shared_ptr<GameObject> object;

};

#endif // !RAYCAST_HIT
