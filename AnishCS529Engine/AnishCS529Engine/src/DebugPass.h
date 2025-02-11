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
    this->addShader("shaders/basic_render.vert.glsl\nshaders/basic_render.frag.glsl");
    this->setProperty("isDebug", 0);
  };
};

#endif // !DEBUG_PASS_H
