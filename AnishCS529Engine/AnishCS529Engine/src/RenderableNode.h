/*!****************************************************************************
 * \file   RenderableNode.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-15-2024
 * \brief  Renderable Node class used to represent renderable objects in 
 * the world.
 * 
 *****************************************************************************/
#ifndef RENDERABLE_NODE_H
#define RENDERABLE_NODE_H

#pragma once

#include "Material.h"
#include "Matrix4.h"
#include "Mesh.h"
#include "Node.h"
#include "Renderer.h"

class RenderableNode : public Node {
public:
  RenderableNode(
    const std::string& name,
    std::shared_ptr<Mesh> mesh,
    std::shared_ptr<Material> material,
    Renderer* render) : Node(name), mesh(mesh), material(material), renderer(renderer), isVisible(true) {}
  virtual ~RenderableNode() = default;

  std::shared_ptr<Mesh> getMesh() const { return mesh; }
  std::shared_ptr<Material> getMaterial() const { return material; }
  Matrix4 getModelMatrix() const { return modelMatrix; }
  bool getVisible() const { return isVisible; }

  /* Todo: instead use a Transform object and take rotation, scale and
  position as input instead to modify Transform. */
  void setModelMatrix(const Matrix4& newModelMatrix);
  void setVisible(const bool visible) { isVisible = visible; }

  void update(float deltaTime) override;
  void draw(Matrix4& view, Matrix4& projection);

protected:
  /* Todo: Create separate world and local transform objects */
  /*Transform localTransform;
  Transform worldTransform;*/
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;
  Matrix4 modelMatrix;
  bool isVisible;

private:
  Renderer* renderer;
};


#endif // RENDERABLE_NODE_H
