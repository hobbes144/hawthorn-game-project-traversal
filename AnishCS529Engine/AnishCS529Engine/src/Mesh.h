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

#include <unordered_map>
#include <vector>

#include "GeometryBuffer.h"
#include "Renderer.h"

/** Struct VertexData not in use. */
struct VertexData {
  GeometryBuffer::AttributeType attribute;
  std::vector<float> data;
  int componentsPerVertex;
};

class Mesh {
public:
  using Attributes = 
    std::unordered_map<
      GeometryBuffer::AttributeType,
      std::pair<
        std::vector<float>,
        GLint
      >
    >;

  Mesh(const std::string& name);
  Mesh(
    const std::string& name,
    Attributes attrData,
    const GLsizei interleavedStride = 0);
  Mesh(
    const std::string& name,
    Attributes attrData,
    const std::vector<unsigned int>& indices,
    const GLsizei interleavedStride = 0);
  virtual ~Mesh() = default;

  void setVertexData(const std::shared_ptr<GeometryBuffer>& geometryBuffer);

  void setAttributeData(
    GeometryBuffer::AttributeType& type,
    const std::vector<float>& data,
    int componentsPerVertex,
    const GLsizei interleavedStride);
  void setIndices(const std::vector<unsigned int>& newIndices);

  std::shared_ptr<GeometryBuffer> getGeometryBuffer() const { 
    return geometryBuffer;
  }

  std::unique_ptr<Mesh> clone() const;

  size_t getVertexCount() const;
  size_t getIndexCount() const;

  bool hasAttribute(GeometryBuffer::AttributeType attr) const;
  const std::string& getName() const;

  void draw(Renderer* renderer);

private:
  std::shared_ptr<GeometryBuffer> geometryBuffer;
  std::vector<unsigned int> indices;

  void prepareAttributeData(
    GeometryBuffer::ModifiableAttributes& triangleBufferData,
    const Mesh::Attributes& attrData,
    const GLsizei stride = 0);

  std::string name;
};

std::shared_ptr<Mesh> createSquareMesh(const std::string name);
std::shared_ptr<Mesh> createCubeMesh(const std::string name);

#endif // MESH_H

