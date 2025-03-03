/*!****************************************************************************
 * \file   Ray.h
 * \author Nicholas Shaw (nick_shaw@me.com)
 * \par    **DigiPen Email**
 *    nick.shaw@digipen.edu
 * \par    **Course**
 *    GAM541
 * \date   03-01-2025
 * \brief  This is a Ray class representing a ray being casted
 * 
 *****************************************************************************/

#ifndef RAY
#define RAY

#pragma once

#include "src/Vector3.h"

class Ray
{

	Vector3 origin;
	Vector3 direction;

public:
	Ray(const Vector3& o, const Vector3& d) : origin(o), direction(d.normalized()) {}

	Ray transformRay(const Matrix4& transform) const {
		Ray transformedRay = Ray(Vector3(), Vector3());
		transformedRay.origin = transform * origin;
		transformedRay.direction = transform.transformDirection(direction);
		return transformedRay;
	}

	Vector3 getOrigin() const { return origin; }
	Vector3 getDirection() const { return direction; }

};


#endif // !RAY