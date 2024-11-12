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
