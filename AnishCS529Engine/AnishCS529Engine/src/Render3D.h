/*!****************************************************************************
 * \file   Render3D.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \author Mariojulio Osmin Zaldivar Alvarez (ex-Adjunct Professor)
 *   (zaldivaralvarez@gmail.com) (Advising and Base Code)
 * \date   04-07-2025
 * \brief  Render component for 3D objects
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#ifndef RENDER_3D_H
#define RENDER_3D_H

#pragma once

 /* Base class */
#include "Component.h"

/* Used classes */
#include "Material.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Renderable.h"

/*!****************************************************************************
 * \brief Render3D object that performs rendering to the screen
 *
 *
 *
 *****************************************************************************/
class Render3D :
  public Renderable, public std::enable_shared_from_this<Render3D> {
public:
  using PropertyMap = RenderPass::PropertyMap;
  Render3D() = default;
  ~Render3D() = default;

  /* Component functions */
  void initialize();
  void update(float deltaTime);
  void shutdown();

  void draw(std::shared_ptr<Shader> shader);

  /* Pre-initialization functions */
  std::shared_ptr<Render3D> setMesh(std::shared_ptr<Mesh> _mesh);
  std::shared_ptr<Render3D> setMaterial(std::shared_ptr<Material> _material);
  std::shared_ptr<Render3D> setDrawMode(GLenum _drawMode);

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
