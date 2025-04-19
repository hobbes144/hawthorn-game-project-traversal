/*!****************************************************************************
 * \file   LocalLightsPass.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-12-2025
 * \brief  Pass to draw point lights in the scene
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#ifndef LOCAL_LIGHTS_PASS_H
#define LOCAL_LIGHTS_PASS_H

#pragma once

#include "RenderPass.h"
#include "TextureManager.h"

class LocalLightsPass : public RenderPass {
private:
  std::shared_ptr<Mesh> sphereMesh;
public:
  LocalLightsPass();

  void initialize();

  void draw(
    std::shared_ptr<Camera> camera,
    SceneGraph* sceneGraph) const override;
};

#endif // !LOCAL_LIGHTS_PASS_H
