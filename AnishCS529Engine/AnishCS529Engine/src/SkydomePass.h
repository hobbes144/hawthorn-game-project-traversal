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
  SkydomePass(TextureManager::TextureID textureID) :
    RenderPass(), sphereMesh(Mesh::createSphereMesh("sphere", 32)),
    scale(Matrix4::scale(Vector3(2000.0f))) {

    this->addShader("shaders/skydome.vert\nshaders/skydome.frag");
    shader->initializeUBO("camera", 0);

    skydomeTexture = textureID;
    HDR = TextureManager::getInstance().isHDR(skydomeTexture);
  }

  SkydomePass(const std::string& textureName) :
    RenderPass(), sphereMesh(Mesh::createSphereMesh("sphere", 32)),
    scale(Matrix4::scale(Vector3(2000.0f))) {

    this->addShader("shaders/skydome.vert\nshaders/skydome.frag");
    shader->initializeUBO("camera", 0);

    skydomeTexture = TextureManager::getInstance().loadFile(textureName);
    HDR = TextureManager::getInstance().isHDR(skydomeTexture);
  }

  SkydomePass() = delete;

  void draw(
    std::shared_ptr<Camera> camera,
    SceneGraph* scene) const override {

    shader->use();

    shader->setInt("HDR", HDR);
    shader->setMat4("ModelMatrix", Matrix4::scale(Vector3(2000.0f)));
    shader->bindTexture(0, "skydomeTexture", skydomeTexture);

    sphereMesh->draw(GL_TRIANGLES);
  }
};

#endif // !SKYDOME_PASS_H
