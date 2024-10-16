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

Mesh::Mesh(Attributes attrData, std::string name) {
  GeometryBuffer::ModifiableAttributes geometryBufferAttr;
  prepareAttributeData(geometryBufferAttr, attrData);
  
  /* Todo: Allow for modifications? */
  /*if (geometryBuffer)
    geometryBuffer->updateVertexAttribute(attr, data);

  else*/
  geometryBuffer = GeometryBuffer::create(geometryBufferAttr, name);

}

void Mesh::prepareAttributeData(
  GeometryBuffer::ModifiableAttributes& triangleBufferData,
  const Mesh::Attributes& attrData) {

  for (const auto& [attr, info] : attrData) {
    triangleBufferData[attr] = {
      info.first,
      info.second,
      GL_FLOAT,
      GL_FALSE
    };
  }
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

