/*!****************************************************************************
 * \file   GBufferPrepass.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-09-2025
 * \brief  GBuffer Prepass
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#ifndef G_BUFFER_PREPASS_H
#define G_BUFFER_PREPASS_H

#pragma once

#include "RenderPass.h"

class GBufferPrepass : public RenderPass {
public:
  GBufferPrepass();

  virtual void initialize() override;

  virtual void draw(
    std::shared_ptr<Camera> camera,
    SceneGraph* sceneGraph) const override;

private:
  FBO* gbuffer;

};

#endif // !G_BUFFER_PREPASS_H
