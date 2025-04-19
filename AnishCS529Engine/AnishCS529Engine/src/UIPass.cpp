/*!****************************************************************************
 * \file   UIPass.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    GAM541
 * \date   04-18-2025
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 *
 *****************************************************************************/
#include "precompiled.h"
#include "UIPass.h"

UIPass::UIPass() : RenderPass() {
  this->addShader("shaders/ui.vert\nshaders/ui.frag");

  renderMask = RenderMask::UIPass;
}
