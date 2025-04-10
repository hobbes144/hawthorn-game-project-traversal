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
protected:

public:
  LightingPass() : RenderPass() {
    this->addShader("shaders/lighting.vert\nshaders/lighting.frag");

    renderMask = RenderMask::LightingPass;
  };
};

#endif // !LIGHTING_PASS_H
