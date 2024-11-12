#pragma once
#include "Shape.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Material.h"

class OBB : public Shape
{
public:
	OBB(const Vector3& center, const Vector3& halfExtents);
	~OBB() = default;

	Type getType() const override;

	void update(Transform& transform) override;

	void getCorners(Vector3 corners[4]) const;

	void project(const Vector3& axis, float& min, float& max) const;

	Vector3 getCenter()		 const;
	Vector3 getHalfExtents() const;
	Vector3 getRight()		 const;
	Vector3 getUp()			 const;

	// debug functions
	void initializeDebugDraw(Renderer* renderer); // Call this once when creating OBB
	void drawDebugLines(Matrix4& view, Matrix4& projection); // Call this in your render loop


private:
	// Local space values (original, unchanged)
	Vector3 localCenter;
	Vector3 localHalfExtents;
	Vector3 localRight;
	Vector3 localUp;

	// World space values (transformed)
	Vector3 worldCenter;
	Vector3 worldHalfExtents;
	Vector3 worldRight;
	Vector3 worldUp;

	// debug properties
	std::shared_ptr<Mesh> debugMesh;
	std::shared_ptr<Material> debugMaterial;
	Renderer* renderer;

};

