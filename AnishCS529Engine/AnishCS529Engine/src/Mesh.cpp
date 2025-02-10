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

void Mesh::draw(Renderer* renderer) {
  if ( !geometryBuffer ) return;
  geometryBuffer->bind();

  if (this->hasAttribute(GeometryBuffer::AttributeType::Position) ) {
    if (this->getIndexCount() > 0) {
      renderer->draw(GL_TRIANGLES, geometryBuffer->getIndexCount(), true);
    }
    else {
      renderer->draw(GL_TRIANGLES, geometryBuffer->getVertexCount(), false);
    }
  }
  
  // For efficiency, removing unbind.
  // We will be running draw calls multiple times per frame because we have
  // multiple passes now. Doing an unbind every pass just to bind it again is
  // very inefficient.
  // 
  // geometryBuffer->unbind();
}

std::shared_ptr<Mesh> createSquareMesh(const std::string name)
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

std::shared_ptr<Mesh> createCubeMesh(const std::string name)
{
  // Generate vertex data for a rectangle
  // We'll use a unit rectangle centered at the origin
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
  };


  // Generate indices for two triangles
  std::vector<unsigned int> indices = {
    0, 1,  // Bottom Front edge         // 0
    1, 2,  // Right Front edge          // 2
    2, 3,  // Top Front edge            // 4
    3, 0,  // Left Front edge           // 6
    4, 5,  // Bottom Back edge          // 8
    5, 6,  // Right Back edge           // 10
    6, 7,  // Top Back edge             // 12
    7, 4,  // Left Back edge            // 14
    0, 4,  // Bottom Left Z Axis edge   // 16
    1, 5,  // Bottom Right Z Axis edge  // 18
    2, 6,  // Top Right Z Axis edge     // 20
    3, 7,  // Top Left Z Axis edge      // 22
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
