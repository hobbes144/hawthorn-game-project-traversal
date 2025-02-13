/*!****************************************************************************
 * \file   Mesh.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-15-2024
 * 
 *****************************************************************************/
#include "Mesh.h"

std::unordered_map<Mesh::Type, std::shared_ptr<Mesh>> Mesh::shapeMeshes;

Mesh::Mesh(const std::string& name) : name(name) {}

Mesh::Mesh(
    const std::string& name,
    Attributes attrData,
    const GLsizei interleavedStride) {

  GeometryBuffer::ModifiableAttributes geometryBufferAttr;
  prepareAttributeData(geometryBufferAttr, attrData, interleavedStride);

  this->name = name;
  geometryBuffer = GeometryBuffer::create(
    geometryBufferAttr, 
    name, 
    (interleavedStride != 0));

}

Mesh::Mesh(
    const std::string& name,
    Attributes attrData,
    const std::vector<unsigned int>& indices,
    const GLsizei interleavedStride) {

  GeometryBuffer::ModifiableAttributes geometryBufferAttr;
  prepareAttributeData(geometryBufferAttr, attrData, interleavedStride);

  this->name = name;
  this->indices = indices;
  geometryBuffer = GeometryBuffer::create(
    geometryBufferAttr,
    indices,
    name,
    (interleavedStride != 0));
}

void Mesh::prepareAttributeData(
    GeometryBuffer::ModifiableAttributes& triangleBufferData,
    const Mesh::Attributes& attrData,
    const GLsizei stride) {

  for (const auto& [attr, info] : attrData) {
    triangleBufferData[attr] = {
      info.first,
      info.second,
      GL_FLOAT,
      GL_FALSE,
      stride
    };
  }
}

void Mesh::setAttributeData(
    GeometryBuffer::AttributeType& type,
    const std::vector<float>& data,
    int componentsPerVertex,
    const GLsizei interleavedStride = 0) {

  if (geometryBuffer)
    geometryBuffer->updateVertexAttribute(type, data);

  else {
    GeometryBuffer::ModifiableAttributes attributeMap;
    Mesh::Attributes attrData;
    attrData[type] = { data , componentsPerVertex };
    prepareAttributeData(attributeMap, attrData, interleavedStride);
    geometryBuffer = GeometryBuffer::create(attributeMap, name, false);
  }
}

void Mesh::setVertexData(
    const std::shared_ptr<GeometryBuffer>& geometryBuffer) {
  this->geometryBuffer = geometryBuffer;
  this->indices = geometryBuffer->getIndexData();
}

void Mesh::setIndices(const std::vector<unsigned int>& newIndices) {
  this->geometryBuffer->updateIndices(newIndices);
  this->indices = newIndices;
}

std::unique_ptr<Mesh> Mesh::clone() const {
  return std::make_unique<Mesh>(*this);
}

size_t Mesh::getVertexCount() const {
  return geometryBuffer ? geometryBuffer->getVertexCount() : 0;
}

size_t Mesh::getIndexCount() const {
  return geometryBuffer ? geometryBuffer->getIndexCount() : 0;
}

bool Mesh::hasAttribute(GeometryBuffer::AttributeType attr) const {
  return geometryBuffer && geometryBuffer->hasAttribute(attr);
}

const std::string& Mesh::getName() const {
  return name;
}

void Mesh::draw(GLenum mode) {
  if ( !geometryBuffer ) return;
  geometryBuffer->bind();

  /* Removed reference to renderer to avoid circular dependency issues.
  * This really should have been in Renderer, or some other encapsulating class
  * Todo: Move mesh draw OpenGL calls to different class.
  */
  if (this->hasAttribute(GeometryBuffer::AttributeType::Position) ) {
    if (this->getIndexCount() > 0) {
      glDrawElements(mode, geometryBuffer->getIndexCount(), GL_UNSIGNED_INT, 0);
    }
    else {
      glDrawArrays(mode, 0, geometryBuffer->getVertexCount());
    }
  }
  
  // For efficiency, removing unbind.
  // We will be running draw calls multiple times per frame because we have
  // multiple passes now. Doing an unbind every pass just to bind it again is
  // very inefficient.
  // 
  //geometryBuffer->unbind();
}

std::shared_ptr<Mesh> Mesh::createSquareMesh(const std::string name)
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

  Mesh::Attributes newMeshData;

  newMeshData[GeometryBuffer::AttributeType::Position] = {
    vertices,
    3
  };

  newMeshData[GeometryBuffer::AttributeType::TexCoord] = {
    vertices,
    2
  };

  std::shared_ptr<Mesh> newMesh = std::make_shared<Mesh>(
    name + "_Mesh",
    newMeshData,
    indices,
    static_cast<GLsizei>(5 * sizeof(float)));
  return newMesh;
}

std::shared_ptr<Mesh> Mesh::createCubeMesh(const std::string name)
{
  // Generate vertex data for a rectangle
  // We'll use a unit rectangle centered at the origin
  std::vector<float> vertices = {
    // Box corners in normalized coordinates (-0.5 to 0.5)
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  // Bottom-left-Back    //  0 A
     0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // Bottom-right-Back   //  1 B
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  // Top-right-Back      //  2 C
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,  // Top-left-Back       //  3 D
    -0.5f, -0.5f, 0.5f,   0.0f, 0.0f,  // Bottom-left-Front      //  4 E
     0.5f, -0.5f, 0.5f,   1.0f, 0.0f,  // Bottom-right-Front     //  5 F
     0.5f,  0.5f, 0.5f,   1.0f, 1.0f,  // Top-right-Front        //  6 G
    -0.5f,  0.5f, 0.5f,   0.0f, 1.0f,  // Top-left-Front         //  7 H
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // Bottom-left-Back    //  8 A
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  // Bottom-right-Back   //  9 B
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,  // Top-right-Back      // 10 C
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  // Top-left-Back       // 11 D
    -0.5f, -0.5f, 0.5f,   0.0f, 1.0f,  // Bottom-left-Front      // 12 E
     0.5f, -0.5f, 0.5f,   1.0f, 1.0f,  // Bottom-right-Front     // 13 F
     0.5f,  0.5f, 0.5f,   1.0f, 0.0f,  // Top-right-Front        // 14 G
    -0.5f,  0.5f, 0.5f,   0.0f, 0.0f,  // Top-left-Front         // 15 H
    -0.5f, -0.5f, 0.5f,   1.0f, 0.0f,  // Bottom-left-Front      // 16 E
     0.5f, -0.5f, 0.5f,   0.0f, 0.0f,  // Bottom-right-Front     // 17 F
     0.5f,  0.5f, 0.5f,   0.0f, 1.0f,  // Top-right-Front        // 18 G
    -0.5f,  0.5f, 0.5f,   1.0f, 1.0f,  // Top-left-Front         // 19 H
  };


  // Generate indices for two triangles
  std::vector<unsigned int> indices = {
    0, 1, 2,  // Bottom Right Back triangle     // 0
    2, 3, 0,  // Top left Back triangle          // 3
    4, 5, 6,  // Bottom Right Front triangle          // 6
    6, 7, 4,  // Top Left Front triangle           // 9
    8, 9, 13,  // Bottom Right Bottom triangle     // 12
    13, 12, 8,  // Top left Bottom triangle          // 15
    15, 14, 10,  // Bottom Right Top triangle          // 18
    10, 11, 15,  // Top Left Top triangle           // 21
    16, 8, 11,  // Bottom Right Left triangle     // 24
    11, 19, 16,  // Top left Left triangle          // 27
    10, 9, 17,  // Bottom Right Right triangle          // 30
    17, 18, 10,  // Top Left Right triangle           // 33
  };

  Mesh::Attributes newMeshData;

  newMeshData[GeometryBuffer::AttributeType::Position] = {
    vertices,
    3
  };

  newMeshData[GeometryBuffer::AttributeType::TexCoord] = {
    vertices,
    2
  };

  std::shared_ptr<Mesh> newMesh = std::make_shared<Mesh>(
    name + "_Mesh",
    newMeshData,
    indices,
    static_cast<GLsizei>(5 * sizeof(float)));
  return newMesh;
}

std::shared_ptr<Mesh> Mesh::createMesh(const std::string name, Type type)
{
  switch (type) {
  case Square:
    return createSquareMesh(name);
    break;
  case Cube:
    return createCubeMesh(name);
    break;
  default:
    assert(("MESH::CREATEMESH::INVALIDTYPE") && false);
  }
  return nullptr;
}

std::shared_ptr<Mesh> Mesh::getShapeMesh(Type type)
{
  if (shapeMeshes.contains(type))
    return shapeMeshes[type];

  std::string name;
  switch (type) {
  case Square:
    name = "SquareShape";
    break;
  case Cube:
    name = "CubeShape";
    break;
  default:
    assert(("MESH::GETSHAPEMESH::INVALIDTYPE") && false);
    name = "InvalidShape";
  }

  shapeMeshes[type] = createMesh(name, type);
  return shapeMeshes[type];

}
