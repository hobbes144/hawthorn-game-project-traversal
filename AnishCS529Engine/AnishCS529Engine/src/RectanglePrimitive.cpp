#include "RectanglePrimitive.h"

RectanglePrimitive::RectanglePrimitive(const std::string name,
    std::shared_ptr<GeometryBuffer>& geometryBuffer,
    Renderer* renderer) : RenderableNode(name, nullptr, nullptr, renderer) {
  mesh = std::make_shared<Mesh>(getName() + "_Mesh");
  mesh->setVertexData(geometryBuffer);
  createMaterial();
}

RectanglePrimitive::RectanglePrimitive(const std::string name, 
    Renderer* renderer) : RenderableNode(name, nullptr, nullptr, renderer) {
  createMesh();
  createMaterial();
}

void RectanglePrimitive::createMesh()
{
  // Generate vertex data for a rectangle
  // We'll use a unit rectangle centered at the origin
  std::vector<float> vertices = {
    // Position (x, y, z)
    -0.5f, -0.5f, 0.0f,      0.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f, 0.0f,      1.0f, 0.0f,  // Bottom-right
     0.5f,  0.5f, 0.0f,      1.0f, 1.0f,  // Top-right
    -0.5f,  0.5f, 0.0f,      0.0f, 1.0f   // Top-left
  };


  // Generate indices for two triangles
  std::vector<unsigned int> indices = {
      0, 1, 2,  // First triangle
      2, 3, 0   // Second triangle
  };

  Mesh::Attributes rectangleMeshData;

  rectangleMeshData[GeometryBuffer::AttributeType::Position] = {
    vertices,
    3
  };

  rectangleMeshData[GeometryBuffer::AttributeType::TexCoord] = {
    vertices,
    2
  };

  mesh = std::make_shared<Mesh>(
    getName() + "_Mesh",
    rectangleMeshData,
    indices,
    static_cast<GLsizei>(5 * sizeof(float)));

}

void RectanglePrimitive::createMaterial()
{
  auto shader = std::make_shared<Shader>("shaders/physics_test_vertex_shader.glsl\nshaders/physics_test_fragment_shader.glsl");
  material = std::make_shared<Material>(shader);
  std::shared_ptr<Texture> texture = Texture::create("media/ImgTexture120_100.bmp");
  material->setTexture("mainTexture", texture, 0);
  material->setProperty("useTexture", 1);
  material->setProperty("isTransparent", 1);
}
