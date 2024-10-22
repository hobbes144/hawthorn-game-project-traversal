/*!****************************************************************************
 * \file   Mesh.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-15-2024
 * \brief  Mesh class
 * 
 *****************************************************************************/
#ifndef MESH_H
#define MESH_H

#pragma once

#include <glad/glad.h>

#include <unordered_map>
#include <vector>

#include "GeometryBuffer.h"

struct VertexData {
  GeometryBuffer::AttributeType attribute;
  std::vector<float> data;
  int componentsPerVertex;
};

class Mesh {
public:
  using Attributes = std::unordered_map<GeometryBuffer::AttributeType,
    std::pair<std::vector<float>, GLint>>;

  Mesh(Attributes attrData, std::string name);
  Mesh(Attributes attrData, const std::vector<unsigned int>& indices, std::string name);

  void setAttributeData(
    GeometryBuffer::AttributeType& type,
    const std::vector<float>& data,
    int componentsPerVertex);

  std::shared_ptr<GeometryBuffer> getGeometryBuffer() const { return geometryBuffer; }
  std::unique_ptr<Mesh> clone() const;

  size_t getVertexCount() const;
  size_t getIndexCount() const;

private:
  std::shared_ptr<GeometryBuffer> geometryBuffer;

  void prepareAttributeData(
    GeometryBuffer::ModifiableAttributes& triangleBufferData,
    const Mesh::Attributes& attrData);

  std::string name;
};

#endif // MESH_H

