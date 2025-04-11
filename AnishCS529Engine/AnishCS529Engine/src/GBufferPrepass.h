/*!****************************************************************************
 * \file   GBufferPrepass.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-09-2025
 * \brief  GBuffer Prepass
 * 
 *****************************************************************************/
#ifndef G_BUFFER_PREPASS_H
#define G_BUFFER_PREPASS_H

#pragma once

#include "RenderPass.h"

class GBufferPrepass : public RenderPass {
public:
  GBufferPrepass() : RenderPass() {
    this->addShader("shaders/gbuffer.vert\nshaders/gbuffer.frag");

    renderMask = RenderMask::GBufferPrepass;
  }

  virtual void initialize() {
    renderGraphBuilder->createTexture("GBuffer_position");
    renderGraphBuilder->createTexture("GBuffer_normal");
    renderGraphBuilder->createTexture("GBuffer_diffuse");
    renderGraphBuilder->createTexture("GBuffer_specular");
    gbuffer = renderGraphBuilder->createFBO(
      "GBuffer",
      {
        "GBuffer_position",
        "GBuffer_normal",
        "GBuffer_diffuse",
        "GBuffer_specular"
      });
  }

  virtual void draw(
    std::shared_ptr<Camera> camera,
    SceneGraph * scene) const {

    gbuffer->bind();

    RenderPass::draw(camera, scene);

    gbuffer->unbind();

  }

private:
  FBO* gbuffer;

};

#endif // !G_BUFFER_PREPASS_H
