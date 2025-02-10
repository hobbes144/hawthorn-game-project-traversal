#include "AABB.h"
#include <iostream>

AABB::AABB(const Vector3& min,
            const Vector3& max)
  : localMin(min), localMax(max),
  worldMin(min), worldMax(max) {}

Shape::Type AABB::getType() const {
  return Type::AABB;
}

void AABB::update(Transform& transform) {
  // For 2D AABB, we only need 4 corners
  Vector3 corners[8] = {
      Vector3(localMin[0], localMin[1], localMin[2]), // Bottom-left-Front
      Vector3(localMax[0], localMin[1], localMin[2]), // Bottom-right-Front
      Vector3(localMin[0], localMax[1], localMin[2]), // Top-left-Front
      Vector3(localMax[0], localMax[1], localMin[2]), // Top-right-Front
      Vector3(localMin[0], localMin[1], localMax[2]), // Bottom-left-Back
      Vector3(localMax[0], localMin[1], localMax[2]), // Bottom-right-Back
      Vector3(localMin[0], localMax[1], localMax[2]), // Top-left-Back
      Vector3(localMax[0], localMax[1], localMax[2]), // Top-right-Back
  };

  // Get the transform matrix once
  Matrix4 transformMatrix = transform.getLocalMatrix();

  // Transform corners and find new world AABB bounds
  worldMin = worldMax = transformMatrix * corners[0];
  for (int i = 1; i < 8; i++) {
    // Todo: find out why this is not correct
    Vector3 transformed = transformMatrix * corners[i];
    worldMin[0] = std::min(worldMin[0], transformed[0]);
    worldMin[1] = std::min(worldMin[1], transformed[1]);
    worldMin[2] = std::min(worldMin[2], transformed[2]);
    worldMax[0] = std::max(worldMax[0], transformed[0]);
    worldMax[1] = std::max(worldMax[1], transformed[1]);
    worldMax[2] = std::max(worldMax[2], transformed[2]);
  }
}



// Utility functions
Vector3 AABB::getMin()          const { return worldMin; }
Vector3 AABB::getMax()          const { return worldMax; }
Vector3 AABB::getCenter()       const { return (worldMin + worldMax) * 0.5f; }
Vector3 AABB::getHalfExtents()  const { return (worldMax - worldMin) * 0.5f; }
float   AABB::getWidth()        const { return worldMax[0] - worldMin[0]; }
float   AABB::getHeight()       const { return worldMax[1] - worldMin[1]; }
float   AABB::getDepth()        const { return worldMax[2] - worldMin[2]; }

//void AABB::initializeDebugDraw(Renderer* renderer) {
//  this->renderer = renderer;
//
//  // Define vertices in normalized coordinates
//  std::vector<float> vertices = {
//    // Box corners in normalized coordinates (-0.5 to 0.5)
//    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // Bottom-left-Front    //  0
//     0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // Bottom-right-Front   //  1
//     0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // Top-right-Front      //  2
//    -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // Top-left-Front       //  3
//    -0.5f, -0.5f, 0.5f,   0.0f, 0.0f,  // Bottom-left-Back      //  4
//     0.5f, -0.5f, 0.5f,   0.0f, 0.0f,  // Bottom-right-Back     //  5
//     0.5f,  0.5f, 0.5f,   0.0f, 0.0f,  // Top-right-Back        //  6
//    -0.5f,  0.5f, 0.5f,   0.0f, 0.0f,  // Top-left-Back         //  7
//    // Center point
//     0.0f,  0.0f, 0.0f,   0.0f, 0.0f,                           //  8
//     // Right axis endpoint (unit vector)
//      1.0f,  0.0f, 0.0f,   0.0f, 0.0f,                           //  9
//      // Up axis endpoint (unit vector)
//       0.0f,  1.0f, 0.0f,   0.0f, 0.0f,                           // 10
//       // Up axis endpoint (unit vector)
//        0.0f,  0.0f, 1.0f,   0.0f, 0.0f                            // 11
//  };
//
//  std::vector<unsigned int> indices = {
//    0, 1,  // Bottom Front edge         // 0
//    1, 2,  // Right Front edge          // 2
//    2, 3,  // Top Front edge            // 4
//    3, 0,  // Left Front edge           // 6
//    4, 5,  // Bottom Back edge          // 8
//    5, 6,  // Right Back edge           // 10
//    6, 7,  // Top Back edge             // 12
//    7, 4,  // Left Back edge            // 14
//    0, 4,  // Bottom Left Z Axis edge   // 16
//    1, 5,  // Bottom Right Z Axis edge  // 18
//    2, 6,  // Top Right Z Axis edge     // 20
//    3, 7,  // Top Left Z Axis edge      // 22
//    8, 9,  // Right vector              // 24
//    8, 10,  // Up vector                // 26
//    8, 11,  // Front vector             // 28
//  };
//
//  Mesh::Attributes debugMeshData;
//  debugMeshData[GeometryBuffer::AttributeType::Position] = {
//    vertices,
//    3
//  };
//  debugMeshData[GeometryBuffer::AttributeType::TexCoord] = {
//    vertices,
//    2
//  };
//
//  debugMesh = std::make_shared<Mesh>("AABB_Debug_Mesh", debugMeshData, indices, static_cast<GLsizei>(5 * sizeof(float)));
//
//  // Create and setup material
//  auto shader = std::make_shared<Shader>("shaders/physics_test_vertex_shader.glsl\nshaders/physics_test_fragment_shader.glsl");
//  debugMaterial = std::make_shared<MaterialDeprecated>(shader);
//  debugMaterial->setProperty("useTexture", 0);
//  debugMaterial->setProperty("isTransparent", 0);
//}
//
//void AABB::drawDebugLines(Matrix4& view, Matrix4& projection) {
//  if (!debugMesh || !debugMaterial) return;
//
//  const Vector3 worldHalfExtents = this->getHalfExtents();
//  const Vector3 worldCenter = this->getCenter();
//
//  // Create model matrix that will transform our normalized box to the OBB's position and orientation
//  Matrix4 scale = Matrix4::scale(worldHalfExtents.x * 2, worldHalfExtents.y * 2, worldHalfExtents.z * 2);
//  Matrix4 rotation = Matrix4();
//  Matrix4 translation = Matrix4::translation(
//    worldCenter.x, worldCenter.y, worldCenter.z);
//  Matrix4 model = translation * rotation * scale;
//
//  // Draw box outline in green
//  debugMaterial->setProperty("Color", Vector3(0.0f, 1.0f, 0.0f));
//  debugMaterial->setProperty("ModelMatrix", model);
//  debugMaterial->setProperty("ViewMatrix", view);
//  debugMaterial->setProperty("ProjectionMatrix", projection);
//
//  debugMaterial->apply();
//  auto geomBuffer = debugMesh->getGeometryBuffer();
//  if (geomBuffer) {
//    geomBuffer->bind();
//
//    // Draw box outline
//    glLineWidth(2.0f);
//    renderer->draw(GL_LINES, 24, true);  // First 8 indices for box
//
//    // Draw direction vectors
//    // For these, we use a different scale matrix that keeps them unit length
//    Matrix4 vectorScale = Matrix4::scale(worldHalfExtents.x, worldHalfExtents.y, worldHalfExtents.z);
//    Matrix4 vectorModel = model;// translation* rotation* vectorScale;
//
//    // Draw right vector in red
//    debugMaterial->setProperty("Color", Vector3(1.0f, 0.0f, 0.0f));
//    debugMaterial->setProperty("ModelMatrix", vectorModel);
//    debugMaterial->apply();
//    glLineWidth(3.0f);
//    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));
//
//    // Draw up vector in blue
//    debugMaterial->setProperty("Color", Vector3(0.0f, 0.0f, 1.0f));
//    debugMaterial->apply();
//    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(26 * sizeof(unsigned int)));
//
//    // Draw front vector in yellow
//    debugMaterial->setProperty("Color", Vector3(1.0f, 1.0f, 0.0f));
//    debugMaterial->apply();
//    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(28 * sizeof(unsigned int)));
//
//    glLineWidth(1.0f);
//    geomBuffer->unbind();
//  }
//}

