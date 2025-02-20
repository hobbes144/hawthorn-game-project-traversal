/*!****************************************************************************
 * \file   LightingPass.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-10-2025
 * \brief  Lighting RenderPass class for 3D rendering
 * 
 *****************************************************************************/
#ifndef LIGHTING_PASS_H
#define LIGHTING_PASS_H

#pragma once

#include "RenderPass.h"

class LightingPass : public RenderPass {
public:
  LightingPass() : RenderPass() {
    this->addShader("shaders/lighing.vert.glsl\nshaders/lighting.frag.glsl");
  };
};

#endif // !LIGHTING_PASS_H
