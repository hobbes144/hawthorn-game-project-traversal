/*!****************************************************************************
 * \file   GeometryBuffer.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-14-2024
 * \brief  Geometry Buffer factory class that manages OpenGL buffers and their data.
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

  struct AttributeInfo {
    GLint       size;
    GLenum      type;
    GLboolean   normalized;
    GLsizei     stride;
  };

  /*
    Attribute stores:
      Type (position or color, etc)
      Pair:
        Data (as 1D vector of Dimension * numpoints)
        AttributeInfo:
          Size: Number of dimensions
          Type: GL type
          Normalized: If should normalize
          Stride: Num bytes between each element
  */
  using Attribute = const std::unordered_map<
    AttributeType, 
    std::pair<
      std::vector<float>, 
      AttributeInfo
    >
  >;
  
  ~GeometryBuffer();

  // Prevent copying
  GeometryBuffer(const GeometryBuffer&) = delete;
  GeometryBuffer& operator=(const GeometryBuffer&) = delete;

  // Allow moving
  GeometryBuffer(GeometryBuffer&&) noexcept;
  GeometryBuffer& operator=(GeometryBuffer&&) noexcept;

  static std::shared_ptr<GeometryBuffer> CreateBuffer(std::string name);

  void bind() const;
  void unbind() const;

  GLuint getVAO() const { return vao; }
  GLuint getVBO() const { return vbo; }
  GLuint getEBO() const { return ebo; }

private:
  GLuint vao;
  GLuint vbo;
  GLuint ebo;
  int vertexCount;
  int indexCount;

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
