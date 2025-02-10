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
#include "Transform.h"

class RenderableNode : public Node {
public:
  RenderableNode(
    const std::string& name,
    std::shared_ptr<Mesh> mesh,
    std::shared_ptr<Material> material,
    Renderer* render,
    bool isIndexed = true) : Node(name), mesh(mesh), material(material),
                             renderer(renderer), isVisible(true),
                             isIndexed(isIndexed) {}
  virtual ~RenderableNode() = default;

  std::shared_ptr<Mesh> getMesh() const { return mesh; }
  std::shared_ptr<Material> getMaterial() const { return material; }
  bool getVisible() const { return isVisible; }

  void setVisible(const bool visible) { isVisible = visible; }

  void update(float deltaTime) override;
  void draw(const Matrix4& view, const Matrix4& projection);

protected:
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;
  bool isVisible;
  bool isIndexed;

private:
  Renderer* renderer;
};


#endif // RENDERABLE_NODE_H
