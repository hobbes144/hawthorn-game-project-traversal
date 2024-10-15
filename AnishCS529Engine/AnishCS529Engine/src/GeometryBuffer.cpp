/*!****************************************************************************
 * \file   GeometryBuffer.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-14-2024
 * 
 *****************************************************************************/
#include "GeometryBuffer.h"

/*!****************************************************************************
 * \brief GeometryBuffer Object Factory
 * 
 * \param attributeData Attribute type information used to construct the VAO.
 * \param name Name of the Buffer.
 * \return \b std::shared_ptr<GeometryBuffer> Initialized GeometryBuffer object
 *****************************************************************************/
std::shared_ptr<GeometryBuffer> GeometryBuffer::CreateBuffer(
  Attribute& attributeData,  std::string name) {

  auto buffer = std::shared_ptr<GeometryBuffer>(new GeometryBuffer(name));
  /* This is because using just std::make_shared<GeometryBuffer>(name) fails.
   * The above calls the constructor from external object make_shared which
   * fails since it is private.
   * This specifically calls the private constructor here and then sends the
   * object to the shared_ptr instead.
  */

  buffer->initializeBuffers(attributeData);
  return buffer;
}

/*!****************************************************************************
 * \brief Destructor which runs cleanup
 * 
 *****************************************************************************/
GeometryBuffer::~GeometryBuffer() {
  cleanupBuffers();
}

/*!****************************************************************************
 * \brief Move Constructor
 * 
 * We do not cleanup other's buffers since this object will now control the
 * existing ones.
 * 
 * \param other GeometryBuffer object to be moved from.
 *****************************************************************************/
GeometryBuffer::GeometryBuffer(GeometryBuffer&& other) noexcept : 
  vao(other.vao), vbo(other.vbo), ebo(other.ebo), 
  vertexCount(other.vertexCount), indexCount(other.indexCount) {
  other.vao = other.vbo = other.ebo = 0;
  other.vertexCount = other.indexCount = 0;
}

/*!****************************************************************************
 * \brief Move assignment operator
 * 
 * This is used when existing object is already instanciated, but we are moving
 * another object's data into it.
 * 
 * \param other GeometryBuffer object to be moved from.
 * \return \b GeometryBuffer& this
 *****************************************************************************/
GeometryBuffer& GeometryBuffer::operator=(GeometryBuffer&& other) noexcept {
  if (this != &other) {
    // Clean up current object's old buffers
    cleanupBuffers();

    vao = other.vao;
    vbo = other.vbo;
    ebo = other.ebo;
    vertexCount = other.vertexCount;
    indexCount = other.indexCount;

    // Reset other
    other.vao = other.vbo = other.ebo = 0;
    other.indexCount = other.vertexCount = 0;
  }

  return *this;
}

/*!****************************************************************************
 * \brief Bind the VAO, making it the current AO for draw calls
 * 
 *****************************************************************************/
void GeometryBuffer::bind() const {
  glBindVertexArray(vao);
}

/*!****************************************************************************
 * \brief Unbind the VAO, resetting the current AO to 0
 * 
 *****************************************************************************/
void GeometryBuffer::unbind() const {
  glBindVertexArray(0);
}

// This is for if or when we do dynamic typing
//size_t get_sizeof_gltype(GLenum type) {
//  switch (type) {
//  case GL_BYTE:
//  case GL_UNSIGNED_BYTE:
//    return sizeof(GLbyte);
//
//  case GL_SHORT:
//  case GL_UNSIGNED_SHORT:
//    return sizeof(GLshort);
//
//  case GL_INT_2_10_10_10_REV:
//  case GL_INT:
//  case GL_UNSIGNED_INT_2_10_10_10_REV:
//  case GL_UNSIGNED_INT:
//    return sizeof(GLint);
//
//  case GL_FLOAT:
//    return sizeof(GLfloat);
//
//  case GL_DOUBLE:
//    return sizeof(GLdouble);
//
//  case GL_FIXED:
//    return sizeof(GLfixed);
//
//  case GL_HALF_FLOAT:
//    return sizeof(GLhalf);
//  }
//}

/*!****************************************************************************
 * \brief Initialize the Buffers
 * 
 * We are creating the VAO, VBO here (EBO to be added later).
 * We are storing the vertexes and color as blocks instead of interleaved.
 * Each block has all the vectors next to each other with no extra stride.
 * (Stride = sizeof(vector))
 * 
 * \param attributeData Attribute data for each attribute. Refer to Attribute
 *  type for more info.
 *****************************************************************************/
void GeometryBuffer::initializeBuffers(Attribute& attributeData) {
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  GLsizei totalSize = 0;
  for (const auto& [type, info] : attributeData) {
    attributeOffsets[type] = totalSize;
    totalSize += (info.data.size() * sizeof(float));
  }
  
  auto it = attributeData.begin();
  vertexCount = it->second.data.size() / it->second.elementSize;

  glBufferData(GL_ARRAY_BUFFER, totalSize, nullptr, GL_STATIC_DRAW);

  GLuint index = 0;
  for (const auto& [type, info] : attributeData) {
    glBufferSubData(GL_ARRAY_BUFFER, attributeOffsets[type], info.data.size() * sizeof(float), info.data.data());
    glVertexAttribPointer(index, info.elementSize, info.type, info.normalized, info.elementSize * sizeof(float), (void*)attributeOffsets[type]);
    glEnableVertexAttribArray(index);
    index++;
  }

  glBindVertexArray(0);

}

/*!****************************************************************************
 * \brief Delete all VAO, VBO and EBO
 * 
 *****************************************************************************/
void GeometryBuffer::cleanupBuffers() {
  if (vao != 0) {
    glDeleteVertexArrays(1, &vao);
    vao = 0;
  }
  if (vbo != 0) {
    glDeleteBuffers(1, &vbo);
    vbo = 0;
  }
  if (ebo != 0) {
    glDeleteBuffers(1, &ebo);
    ebo = 0;
  }
}
