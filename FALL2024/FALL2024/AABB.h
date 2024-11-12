#pragma once

#include "Shape.h"
#include "Vector3.h"

class AABB : public Shape
{
public:
	AABB(const Vector3& min = Vector3(-0.5f, -0.5f, 0.0f), 
		 const Vector3& max = Vector3(0.5f, 0.5f, 0.0f));
	~AABB() = default;

	Type getType() const override;
	void update(Transform& transform);

	Vector3	getMin()		 const;
	Vector3	getMax()		 const;
	Vector3	getCenter()		 const;
	Vector3 getHalfExtents() const;
	float   getWidth()		 const;
	float   getHeight()		 const;

private:
	Vector3 localMin, localMax;   // Original bounds in local space
	Vector3 worldMin, worldMax;   // Transformed bounds in world space

};

