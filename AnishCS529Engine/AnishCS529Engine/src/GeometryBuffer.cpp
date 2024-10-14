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


static std::shared_ptr<GeometryBuffer> CreateBuffer(std::string name) {

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
