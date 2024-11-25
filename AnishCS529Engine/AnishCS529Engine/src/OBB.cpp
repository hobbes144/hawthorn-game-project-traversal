#include "OBB.h"


OBB::OBB(const Vector3& center = Vector3(0, 0, 0),
  const Vector3& halfExtents = Vector3(0.5f, 0.5f, 0.5f))
  : localCenter(center), localHalfExtents(halfExtents),
  unscaledWorldCenter(center),
  worldCenter(center), worldHalfExtents(halfExtents) {

  // Initialize right and up vectors for 2D
  localAxes[0] = worldAxes[0] = Vector3(1, 0, 0);
  localAxes[1] = worldAxes[1] = Vector3(0, 1, 0);
  localAxes[2] = worldAxes[2] = Vector3(0, 0, 1);
  localRight = worldRight = localAxes[0];
  localUp = worldUp = localAxes[1];
  localFront = worldFront = localAxes[2];
}

Shape::Type OBB::getType() const {
  return Type::OBB;
}

void OBB::update(Transform& transform) {
  // Get the transform matrix once
  unscaledWorldCenter = transform.getPosition();
  worldCenter = transform.getPosition() * transform.getScaling();

  // Update orientation vectors using rotation only
  // We can get this directly from the transform's rotation
  Matrix4 transformMatrix = transform.getLocalMatrix();

  // Todo: Figure out what this is for:
  //float angle = transform.getRotation().z; // For 2D we only need Z rotation
  
  worldAxes[0] = Vector3(transformMatrix.getElement(0, 0), transformMatrix.getElement(1, 0), transformMatrix.getElement(2, 0)).normalized();
  worldAxes[1] = Vector3(transformMatrix.getElement(0, 1), transformMatrix.getElement(1, 1), transformMatrix.getElement(2, 1)).normalized();
  worldAxes[2] = Vector3(transformMatrix.getElement(0, 2), transformMatrix.getElement(1, 2), transformMatrix.getElement(2, 2)).normalized();
  worldRight = worldAxes[0];
  worldUp = worldAxes[1];

  // Update half extents with scale
  Vector3 scale = transform.getScaling();
  worldHalfExtents = Vector3(
    localHalfExtents.x * std::abs(scale.x),
    localHalfExtents.y * std::abs(scale.y),
    localHalfExtents.z * std::abs(scale.z)
  );
}

void OBB::getCorners(Vector3 corners[4]) const {
  Vector3 offsets[3] = {
    worldAxes[0] * worldHalfExtents.x,
    worldAxes[1] * worldHalfExtents.y,
    worldAxes[2] * worldHalfExtents.z
  };

  corners[0] = worldCenter - offsets[0] - offsets[1] - offsets[2]; // Bottom-left-Front
  corners[1] = worldCenter + offsets[0] - offsets[1] - offsets[2]; // Bottom-right-Front
  corners[2] = worldCenter + offsets[0] + offsets[1] - offsets[2]; // Top-right-Front
  corners[3] = worldCenter - offsets[0] + offsets[1] - offsets[2]; // Top-left-Front
  corners[0] = worldCenter - offsets[0] - offsets[1] + offsets[2]; // Bottom-left-Back
  corners[1] = worldCenter + offsets[0] - offsets[1] + offsets[2]; // Bottom-right-Back
  corners[2] = worldCenter + offsets[0] + offsets[1] + offsets[2]; // Top-right-Back
  corners[3] = worldCenter - offsets[0] + offsets[1] + offsets[2]; // Top-left-Back
}

void OBB::project(const Vector3& axis, float& min, float& max) const {
  // Get absolute position of corners in world space
  Vector3 corners[8];
  getCorners(corners);

  // Project directly onto axis
  min = max = corners[0].dot(axis);

  for (int i = 1; i < 8; i++) {
    float proj = corners[i].dot(axis);
    min = std::min(min, proj);
    max = std::max(max, proj);
  }

}

Vector3 OBB::getCenter()	      const { return worldCenter; }
Vector3 OBB::getHalfExtents()   const { return worldHalfExtents; }
Vector3 OBB::getRight()		      const { return worldRight; }
Vector3 OBB::getUp()		        const { return worldUp; }
Vector3 OBB::getFront()		      const { return worldFront; }
const Vector3* OBB::getAxes()   const { return worldAxes; }

void OBB::initializeDebugDraw(Renderer* renderer) {
  this->renderer = renderer;

  // Define vertices in normalized coordinates
  std::vector<float> vertices = {
    // Box corners in normalized coordinates (-0.5 to 0.5)
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // Bottom-left-Front    //  0
     0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // Bottom-right-Front   //  1
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // Top-right-Front      //  2
    -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // Top-left-Front       //  3
    -0.5f, -0.5f, 0.5f,   0.0f, 0.0f,  // Bottom-left-Back      //  4
     0.5f, -0.5f, 0.5f,   0.0f, 0.0f,  // Bottom-right-Back     //  5
     0.5f,  0.5f, 0.5f,   0.0f, 0.0f,  // Top-right-Back        //  6
    -0.5f,  0.5f, 0.5f,   0.0f, 0.0f,  // Top-left-Back         //  7
    // Center point
     0.0f,  0.0f, 0.0f,   0.0f, 0.0f,                           //  8
    // Right axis endpoint (unit vector)
     1.0f,  0.0f, 0.0f,   0.0f, 0.0f,                           //  9
    // Up axis endpoint (unit vector)
     0.0f,  1.0f, 0.0f,   0.0f, 0.0f,                           // 10
    // Up axis endpoint (unit vector)
     0.0f,  0.0f, 1.0f,   0.0f, 0.0f                            // 11
  };

  std::vector<unsigned int> indices = {
    0, 1,  // Bottom Front edge         // 2
    1, 2,  // Right Front edge          // 4
    2, 3,  // Top Front edge            // 6
    3, 0,  // Left Front edge           // 8
    4, 5,  // Bottom Back edge          // 10
    5, 6,  // Right Back edge           // 12
    6, 7,  // Top Back edge             // 14
    7, 4,  // Left Back edge            // 16
    0, 4,  // Bottom Left Z Axis edge   // 18
    1, 5,  // Bottom Right Z Axis edge  // 20
    2, 6,  // Top Right Z Axis edge     // 22
    3, 7,  // Top Left Z Axis edge      // 24
    8, 9,  // Right vector              // 26
    8, 10,  // Up vector                // 28
    8, 11,  // Front vector             // 30
  };
  
  Mesh::Attributes debugMeshData;
  debugMeshData[GeometryBuffer::AttributeType::Position] = {
    vertices,
    3
  };
  debugMeshData[GeometryBuffer::AttributeType::TexCoord] = {
    vertices,
    2
  };

  debugMesh = std::make_shared<Mesh>("OBB_Debug_Mesh", debugMeshData, indices, static_cast<GLsizei>(5 * sizeof(float)));

  // Create and setup material
  auto shader = std::make_shared<Shader>("shaders/physics_test_vertex_shader.glsl\nshaders/physics_test_fragment_shader.glsl");
  debugMaterial = std::make_shared<Material>(shader);
  debugMaterial->setProperty("useTexture", 0);
  debugMaterial->setProperty("isTransparent", 0);
}


void OBB::drawDebugLines(Matrix4& view, Matrix4& projection) {
  if (!debugMesh || !debugMaterial) return;

  // Create model matrix that will transform our normalized box to the OBB's position and orientation
  Matrix4 scale = Matrix4::scale(worldHalfExtents.x * 2, worldHalfExtents.y * 2, worldHalfExtents.z * 2);
  Matrix4 rotation = Matrix4(
    worldAxes[0].x, worldAxes[0].y, worldAxes[0].z, 0.0f,
    worldAxes[1].x, worldAxes[1].y, worldAxes[1].z, 0.0f,
    worldAxes[2].x, worldAxes[2].y, worldAxes[2].z, 0.0f,
    0.0f,  0.0f,  0.0f,  1.0f
    );
  Matrix4 translation = Matrix4::translation(
    unscaledWorldCenter.x, unscaledWorldCenter.y, unscaledWorldCenter.z);
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
    renderer->draw(GL_LINES, 24, true);  // First 8 indices for box

    // Draw direction vectors
    // For these, we use a different scale matrix that keeps them unit length
    Matrix4 vectorScale = Matrix4::scale(worldHalfExtents.x, worldHalfExtents.y, worldHalfExtents.z);
    Matrix4 vectorModel = model;// translation* rotation* vectorScale;

    // Draw right vector in red
    debugMaterial->setProperty("Color", Vector3(1.0f, 0.0f, 0.0f));
    debugMaterial->setProperty("ModelMatrix", vectorModel);
    debugMaterial->apply();
    glLineWidth(3.0f);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));

    // Draw up vector in blue
    debugMaterial->setProperty("Color", Vector3(0.0f, 0.0f, 1.0f));
    debugMaterial->apply();
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(26 * sizeof(unsigned int)));

    // Draw front vector in yellow
    debugMaterial->setProperty("Color", Vector3(1.0f, 1.0f, 0.0f));
    debugMaterial->apply();
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(28 * sizeof(unsigned int)));

    glLineWidth(1.0f);
    geomBuffer->unbind();
  }
}
