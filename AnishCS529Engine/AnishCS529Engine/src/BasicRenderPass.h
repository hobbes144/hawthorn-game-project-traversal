/*!****************************************************************************
 * \file   BasicRenderPass.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-10-2025
 * \brief  Basic RenderPass class for 2D rendering with no effects
 * 
 *****************************************************************************/
#ifndef BASIC_RENDER_PASS_H
#define BASIC_RENDER_PASS_H

#pragma once

#include "RenderPass.h"

class BasicRenderPass : public RenderPass {
public:
  BasicRenderPass() : RenderPass() {
    this->addShader("shaders/basic_render.vert.glsl\nshaders/basic_render.frag.glsl");
  };
};

#endif // !BASIC_RENDER_PASS_H
