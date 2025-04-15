/*!****************************************************************************
 * \file   SkydomePass.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-06-2025
 * \brief  Skydome Pass for rendering
 * 
 *****************************************************************************/
#ifndef SKYDOME_PASS_H
#define SKYDOME_PASS_H

#pragma once

#include "RenderPass.h"
#include "TextureManager.h"

class SkydomePass : public RenderPass {
private:
  TextureManager::TextureID skydomeTexture;
  bool HDR;
  std::shared_ptr<Mesh> sphereMesh;
  Matrix4 scale;

public:
  SkydomePass(TextureManager::TextureID textureID);

  SkydomePass(const std::string& textureName);

  SkydomePass() = delete;

  void draw(
    std::shared_ptr<Camera> camera,
    SceneGraph* sceneGraph) const override;
};

#endif // !SKYDOME_PASS_H
