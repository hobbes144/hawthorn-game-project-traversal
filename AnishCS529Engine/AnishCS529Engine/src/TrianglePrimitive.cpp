/*!****************************************************************************
 * \file   TrianglePrimitive.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-21-2024
 * 
 *****************************************************************************/
#include "TrianglePrimitive.h"

TrianglePrimitive::TrianglePrimitive(const std::string name, Renderer* renderer) :
    RenderableNode(name, nullptr, nullptr, renderer),
    color(Vector3(0.0f, 0.0f, 0.0f)) {
  createMesh();
  createMaterial();
}

void TrianglePrimitive::setColor(const Vector3& newColor)
{
  color = newColor;
  if (material)
    material->setProperty("color", color);
}

Vector3 TrianglePrimitive::getColor() const
{
  return color;
}

void TrianglePrimitive::createMesh()
{
  Mesh::Attributes triangleMeshData;

  std::vector<float> vertices = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f,  0.5f, 0.0f
  };
  triangleMeshData[GeometryBuffer::AttributeType::Position] = {
    vertices,
    3
  };

  std::vector<unsigned int> indices = { 0, 1, 2 };

  mesh = std::make_shared<Mesh>(triangleMeshData, indices, getName() + "_Mesh");
}

void TrianglePrimitive::createMaterial()
{
  auto shader = std::make_shared<Shader>("shaders/main_vertex_shader.glsl\nshaders/main_fragment_shader.glsl");
  material = std::make_shared<Material>(shader);
}
