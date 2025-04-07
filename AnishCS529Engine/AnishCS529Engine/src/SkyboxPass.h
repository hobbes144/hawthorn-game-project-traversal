/*!****************************************************************************
 * \file   SkyboxPass.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-06-2025
 * \brief  Skybox Pass for rendering
 * 
 *****************************************************************************/
#ifndef SKYBOX_PASS_H
#define SKYBOX_PASS_H

#pragma once

#include "RenderPass.h"
#include "TextureManager.h"

class SkyboxPass : public RenderPass {
private:
  TextureManager::TextureID skyboxTexture;
  bool HDR;
  std::shared_ptr<Mesh> sphereMesh;
  Matrix4 scale;

public:
  SkyboxPass(TextureManager::TextureID textureID) :
    RenderPass(), sphereMesh(Mesh::createSphereMesh("sphere", 32)),
    scale(Matrix4::scale(Vector3(2000.0f))) {
    this->addShader("shaders/skybox.vert\nshaders/skybox.frag");
    skyboxTexture = textureID;
    HDR = TextureManager::getInstance().isHDR(textureID);
    shader->initializeUBO("camera", 0);
  }

  SkyboxPass() = delete;

  void draw(
    std::shared_ptr<Camera> camera,
    SceneGraph* scene) const override {

    shader->use();
    shader->setUInt("HDR", HDR);
    shader->setMat4("viewProjectionMatrix",
      camera->getViewProjectionWithoutPositionMatrix());
    shader->setMat4("ModelMatrix", scale);
    skyboxTexture;

    sphereMesh->draw(GL_TRIANGLES);
  }
};

#endif // !SKYBOX_PASS_H
