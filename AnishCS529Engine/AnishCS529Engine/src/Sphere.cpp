#include "precompiled.h"
#include "Sphere.h"

Sphere::Sphere(const Vector3& center, float radius)
  : center(center), radius(radius) {}

Shape::Type Sphere::getType() const {
  return Type::Sphere;
}

void Sphere::update(const Transform& transform) {
  // Update center position
  Matrix4 transformMatrix = transform.getLocalMatrix();
  center = transformMatrix * center;

  // For 2D Sphere, use the largest scale component for the radius
  Vector3 scale = transform.getScaling();
  float maxScale = std::max(std::max(std::abs(scale.x), std::abs(scale.y)), std::abs(scale.z));
  radius *= maxScale;
}

Vector3 Sphere::getFarthestExtent(const Vector3& direction) const
{
	return direction * radius;
}

Vector3 Sphere::getSurfacePoint(const Vector3& direction) const
{
	return direction * radius;
}

Vector3 Sphere::getCenter() const {
  return center;
}

float Sphere::getRadius() const {
  return radius;
}

bool Sphere::raycastIntersect(const Ray& ray, RaycastHit& hit, float maxDistance) const{

	Vector3 oc = ray.getOrigin() - center;

	float a = ray.getDirection().dot(ray.getDirection());
	float b = 2.0f * oc.dot(ray.getDirection());
	float c = oc.dot(oc) - (radius * radius);

	float discriminant = (b * b) - (4 * a * c);

	//Does not intersect if discriminant is 0
	if (discriminant < 0) {
		return false;
	}

	//Computer nearest valid intersection point
	float sqrtDiscriminant = sqrt(discriminant);
	float t1 = (-b - sqrtDiscriminant) / (2.0f * a);
	float t2 = (-b + sqrtDiscriminant) / (2.0f * a);

	//Find closest valid t within macDistance
	float t = (t1 > 0 && t1 < maxDistance) ? t1 :
	    	  (t2 > 0 && t2 < maxDistance) ? t2 : -1;
	
	//If no valid intersection return false
	if (t < 0) {
		return false;
	}

	//store the data
	hit.distance = t;
	hit.point = ray.getOrigin() + (ray.getDirection() * t);
	hit.normal = (hit.point - center).normalized();

}
