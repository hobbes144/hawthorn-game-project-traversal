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
#ifndef RENDER_3D_H
#define RENDER_3D_H

#pragma once

/* Base class */
#include "Component.h"

/* Used classes */
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "Renderer.h"

class Render2D : public Component {
public:
  Render2D() = default;
  ~Render2D() = default;

  /* Component functions */
  void initialize();
  void update(float deltaTime);
  void shutdown();

  /* Pre-initialization functions */
  void setRenderer(Renderer* _renderer);
  void setCamera(Camera* _camera);

private:
  Renderer* renderer;
  Camera* camera;
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;
};

#endif // !RENDER_3D_H
