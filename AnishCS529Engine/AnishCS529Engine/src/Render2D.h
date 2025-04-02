/*!****************************************************************************
 * \file   Render2D.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-14-2024
 * \brief  Render component for 2D objects
 * 
 *****************************************************************************/
#ifndef RENDER_2D_H
#define RENDER_2D_H

#pragma once

/* Base class */
#include "Component.h"

/* Used classes */
#include "Material.h"
#include "Mesh.h"
#include "Renderer.h"

/*!****************************************************************************
 * \brief Render2D object that performs rendering to the screen
 * 
 * 
 * 
 *****************************************************************************/
class Render2D : 
  public Component, public std::enable_shared_from_this<Render2D> {
public:
  using PropertyMap = RenderPass::PropertyMap;
  Render2D() = default;
  ~Render2D() = default;

  /* Component functions */
  void initialize();
  void update(float deltaTime);
  void shutdown();

  void draw(std::shared_ptr<Shader> shader);

  /* Pre-initialization functions */
  std::shared_ptr<Render2D> setMesh(std::shared_ptr<Mesh> _mesh);
  std::shared_ptr<Render2D> setMaterial(std::shared_ptr<Material> _material);

  template<typename T>
  void setProperty(const std::string& name, const T& value) {
    properties[name] = value;
  }

private:
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;
  PropertyMap properties;

  GLenum drawMode = GL_TRIANGLES;
};

#endif // !RENDER_3D_H
