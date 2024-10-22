/*!****************************************************************************
 * \file   TrianglePrimitive.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-21-2024
 * \brief  Triangle Primitive object to create basic triangles with color
 * 
 *****************************************************************************/
#ifndef TRIANGLE_PRIMITIVE_H
#define TRIANGLE_PRIMITIVE_H

#pragma once
#include "RenderableNode.h"
#include "GeometryBuffer.h"
#include "Mesh.h"

class TrianglePrimitive : public RenderableNode {
public:
  TrianglePrimitive(const std::string name, Renderer* renderer);
  ~TrianglePrimitive() = default;

  void setColor(const Vector3& color);
  Vector3 getColor() const;
private:
  Vector3 color;

  void createMesh();
  void createMaterial();
};


#endif // TRIANGLE_PRIMITIVE_H
