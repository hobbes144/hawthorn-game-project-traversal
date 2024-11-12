#include "OBB.h"


OBB::OBB(const Vector3& center = Vector3(0, 0, 0),
	const Vector3& halfExtents = Vector3(0.5f, 0.5f, 0.0f))
	: localCenter(center), localHalfExtents(halfExtents),
	worldCenter(center), worldHalfExtents(halfExtents) {

	// Initialize right and up vectors for 2D
	localRight = worldRight = Vector3(1, 0, 0);
	localUp = worldUp = Vector3(0, 1, 0);
}

Shape::Type OBB::getType() const{ 
	return Type::OBB; 
}

void OBB::update(Transform& transform) {
	// Get the transform matrix once
	worldCenter = transform.getPosition();

	// Update orientation vectors using rotation only
	// We can get this directly from the transform's rotation
	Matrix4 transformMatrix = transform.getLocalMatrix();
	float angle = transform.getRotation().z; // For 2D we only need Z rotation
	worldRight = Vector3(transformMatrix.getElement(0, 0), transformMatrix.getElement(1, 0), 0.0f).normalized();
	worldUp = Vector3(transformMatrix.getElement(0, 1), transformMatrix.getElement(1, 1), 0.0f).normalized();

	// Update half extents with scale
	Vector3 scale = transform.getScale();
	worldHalfExtents = Vector3(
		localHalfExtents.x * std::abs(scale.x),
		localHalfExtents.y * std::abs(scale.y),
		0.0f
	);
}

void OBB::getCorners(Vector3 corners[4]) const{
	Vector3 rightOffset = worldRight * worldHalfExtents.x;
	Vector3 upOffset = worldUp * worldHalfExtents.y;

	corners[0] = worldCenter - rightOffset - upOffset; // Bottom-left
	corners[1] = worldCenter + rightOffset - upOffset; // Bottom-right
	corners[2] = worldCenter + rightOffset + upOffset; // Top-right
	corners[3] = worldCenter - rightOffset + upOffset; // Top-left
}

void OBB::project(const Vector3& axis, float& min, float& max) const{
	// Get absolute position of corners in world space
	Vector3 corners[4];
	getCorners(corners);

	// Project directly onto axis
	min = max = corners[0].dot(axis);

	for (int i = 1; i < 4; i++) {
		float proj = corners[i].dot(axis);
		min = std::min(min, proj);
		max = std::max(max, proj);
	}
	
}

Vector3 OBB::getCenter()	  const { return worldCenter; }
Vector3 OBB::getHalfExtents() const { return worldHalfExtents; }
Vector3 OBB::getRight()		  const { return worldRight; }
Vector3 OBB::getUp()		  const { return worldUp; }

void OBB::initializeDebugDraw(Renderer* renderer){
	this->renderer = renderer;
	debugMesh = std::make_shared<Mesh>("OBB_Debug_Mesh");

	// Define vertices in normalized coordinates
	std::vector<float> vertices = {
		// Box corners in normalized coordinates (-0.5 to 0.5)
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,  // Bottom-left
		 0.5f, -0.5f, 0.0f,   0.0f, 0.0f,  // Bottom-right
		 0.5f,  0.5f, 0.0f,   0.0f, 0.0f,  // Top-right
		-0.5f,  0.5f, 0.0f,   0.0f, 0.0f,  // Top-left
		// Center point
		 0.0f,  0.0f, 0.0f,   0.0f, 0.0f,
		 // Right axis endpoint (unit vector)
		  1.0f,  0.0f, 0.0f,   0.0f, 0.0f,
		  // Up axis endpoint (unit vector)
		   0.0f,  1.0f, 0.0f,   0.0f, 0.0f
	};

	std::vector<unsigned int> indices = {
		0, 1,  // Bottom edge
		1, 2,  // Right edge
		2, 3,  // Top edge
		3, 0,  // Left edge
		4, 5,  // Right vector
		4, 6   // Up vector
	};

	debugMesh->setVertexData({
		{GeometryBuffer::Attribute::Position, vertices, 3},
		{GeometryBuffer::Attribute::TexCoord, vertices, 2}
		}, 5 * sizeof(float), indices);

	// Create and setup material
	auto shader = std::make_shared<Shader>("vertex_shader.glsl\nfragment_shader.glsl");
	debugMaterial = std::make_shared<Material>(shader);
	debugMaterial->setProperty("useTexture", 0);
	debugMaterial->setProperty("isTransparent", 0);
}


void OBB::drawDebugLines(Matrix4& view, Matrix4& projection) {
	if (!debugMesh || !debugMaterial) return;

	// Create model matrix that will transform our normalized box to the OBB's position and orientation
	Matrix4 scale = Matrix4::scale(worldHalfExtents.x * 2, worldHalfExtents.y * 2, 1.0f);
	Matrix4 rotation = Matrix4::rotationZ(std::atan2(worldRight.y, worldRight.x));
	Matrix4 translation = Matrix4::translation(worldCenter.x, worldCenter.y, worldCenter.z);
	Matrix4 model = translation * rotation * scale;

	// Draw box outline in green
	debugMaterial->setProperty("Color", Vector3(0.0f, 1.0f, 0.0f));
	debugMaterial->setProperty("ModelMatrix", model);
	debugMaterial->setProperty("ViewMatrix", view);
	debugMaterial->setProperty("ProjectionMatrix", projection);

	debugMaterial->apply();
	auto geomBuffer = debugMesh->getGeometryBuffer();
	if (geomBuffer) {
		geomBuffer->bind();

		// Draw box outline
		glLineWidth(2.0f);
		renderer->draw(8, GL_LINES, true);  // First 8 indices for box

		// Draw direction vectors
		// For these, we use a different scale matrix that keeps them unit length
		Matrix4 vectorScale = Matrix4::scale(worldHalfExtents.x, worldHalfExtents.y, 1.0f);
		Matrix4 vectorModel = model;// translation* rotation* vectorScale;

		// Draw right vector in red
		debugMaterial->setProperty("Color", Vector3(1.0f, 0.0f, 0.0f));
		debugMaterial->setProperty("ModelMatrix", vectorModel);
		debugMaterial->apply();
		glLineWidth(3.0f);
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(8 * sizeof(unsigned int)));

		// Draw up vector in blue
		debugMaterial->setProperty("Color", Vector3(0.0f, 0.0f, 1.0f));
		debugMaterial->apply();
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));

		glLineWidth(1.0f);
		geomBuffer->unbind();
	}
}