/*!****************************************************************************
 * \file   DebugPass.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-10-2025
 * \brief  DebugPass class for 3D rendering
 *
 *****************************************************************************/
#ifndef DEBUG_PASS_H
#define DEBUG_PASS_H

#pragma once

#include "RenderPass.h"

class DebugPass : public RenderPass {
public:
  DebugPass() : RenderPass() {
    this->addShader("shaders/debug.vert.glsl\nshaders/debug.frag.glsl");
    this->setProperty("isDebug", 0);
  };

  virtual void draw(std::shared_ptr<Mesh> mesh, GLenum mode,
    const PropertyMap& materialProperties = {},
    const LightStack& lightStack = {}) const;
};

#endif // !DEBUG_PASS_H
