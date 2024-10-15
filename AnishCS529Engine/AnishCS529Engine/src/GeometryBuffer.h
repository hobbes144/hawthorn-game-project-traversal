/*!****************************************************************************
 * \file   GeometryBuffer.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-14-2024
 * \brief  Geometry Buffer factory class that manages OpenGL buffers and their
 * data.
 * 
 *****************************************************************************/
#ifndef GEOMETRY_BUFFER_H
#define GEOMETRY_BUFFER_H

#pragma once

#include <glad/glad.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


class GeometryBuffer {
public:
  enum class AttributeType {
    Position,
    Color
  };

  /* Todo: Implement EBO and add indices as a list here */

  /*
    AttributeInfo stores:
      Data: 1D vector of size (Dimension * numpoints)
      elementSize: Number of dimensions
      Type: GL type
      Normalized: If should normalize
  */
  struct AttributeInfo {
    std::vector<float>  data;
    GLint               elementSize;
    GLenum              type;
    GLboolean           normalized;
  };

  /*
    Attribute stores:
      Type (position or color, etc)
      AttributeInfo:
        Data: 1D vector of size (Dimension * numpoints)
        elementSize: Number of dimensions
        Type: GL type
        Normalized: If should normalize
  */
  using Attribute = const std::unordered_map<
    AttributeType,
    AttributeInfo
  >;
  
  ~GeometryBuffer();

  // Prevent copying
  GeometryBuffer(const GeometryBuffer&) = delete;
  GeometryBuffer& operator=(const GeometryBuffer&) = delete;

  // Allow moving
  GeometryBuffer(GeometryBuffer&&) noexcept;
  GeometryBuffer& operator=(GeometryBuffer&&) noexcept;

  static std::shared_ptr<GeometryBuffer> create(Attribute& attributeData, std::string name);

  void bind() const;
  void unbind() const;

  /* Todo: Add update methods here for attributes and indices */

  GLsizei getVertexCount() const { return vertexCount; }
  GLsizei getIndexCount() const { return indexCount; }
  GLuint getVAO() const { return vao; }
  GLuint getVBO() const { return vbo; }
  GLuint getEBO() const { return ebo; }

private:
  GLuint vao;
  GLuint vbo;
  GLuint ebo;

  /* Todo: Figure out why this is here. */
  GLsizei vertexCount;
  GLsizei indexCount;

  std::unordered_map<AttributeType, GLsizei> attributeOffsets;
  std::unordered_map<AttributeType, GLsizei> attributeStrides;

  std::string name;

  GeometryBuffer(std::string name) : vao(0), vbo(0), ebo(0), vertexCount(0), indexCount(0), name(name) {};

  void initializeBuffers(Attribute& attributeData);
  void cleanupBuffers();

};
//class GeometryBuffer {
//public:
//	// We define in this class each attribute as vector.
//	enum class Attribute {
//		Position,
//		Normal,
//		TexCoord,
//		Color,
//		Tangent,
//		Bitangent
//	};
//
//	struct AttributeInfo {
//		GLint				size;
//		GLenum			type;
//		GLboolean		normalized;
//		GLsizei			stride;
//	};
//
//	static std::shared_ptr<GeometryBuffer> create(
//		const std::unordered_map<Attribute, std::pair<std::vector<float>, AttributeInfo>>& attrinbuteData,
//		const std::vector<unsigned int>& indices,
//		const 
//	)
//
//	~GeometryBuffer();
//
//	// Prevent copying
//	GeometryBuffer(const GeometryBuffer&) = delete;
//	GeometryBuffer& operator=(const GeometryBuffer&) = delete;
//
//private:
//	GeometryBuffer();
//
//	void initializeBuffers()
//};
//
//GeometryBuffer ::GeometryBuffer()
//{
//}
//
//GeometryBuffer ::~GeometryBuffer()
//{
//}

#endif // GEOMETRY_BUFFER_H
