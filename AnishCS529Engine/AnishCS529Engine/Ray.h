/*!****************************************************************************
 * \file   Ray.h
 * \author Nicholas Shaw (nick_shaw@me.com)
 * \par    **DigiPen Email**
 *    nick.shaw@digipen.edu
 * \par    **Course**
 *    GAM541
 * \date   03-01-2025
 * \brief  This is a Ray class representing a ray being casted. It is created 
 * before the call of RaycastManager::Raycast.
 * It contains an Origin(Vector3) and a direciton (Vector3)
 * 
 *****************************************************************************/

#ifndef RAY
#define RAY

#pragma once

#include "src/Vector3.h"
#include "src/Matrix4.h"

class Ray
{

	Vector3 origin;
	Vector3 direction;

public:
	Ray(const Vector3& o = Vector3(), const Vector3& d = Vector3()) : origin(o), direction(d.normalized()) {}

	Ray transformRay(const Matrix4& transform) const {
		Ray transformedRay = Ray(transform * origin, transform.transformDirection(direction));
		return transformedRay;
	}

	Vector3 getOrigin() const { return origin; }
	Vector3 getDirection() const { return direction; }

};


#endif // !RAY