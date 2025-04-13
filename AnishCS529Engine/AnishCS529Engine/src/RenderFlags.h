/*!****************************************************************************
 * \file   RenderFlags.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-09-2025
 * \brief  Render specific flags and names for easier referencing
 * 
 *****************************************************************************/
#ifndef RENDER_FLAGS_H
#define RENDER_FLAGS_H

#pragma once

#include <cstdint>
#include <vector>

namespace RenderMask {
  /** No render pass */
  constexpr uint32_t None               = 0;
  /** Skydome render pass, this doesn't render any objects other than
  * the skydome so should be first. */
  constexpr uint32_t SkydomePass        = 1 << 0;
  /** Prepass for advanced lighting */
  constexpr uint32_t GBufferPrepass     = 1 << 1;
  /** Shadow processing pass */
  constexpr uint32_t ShadowPass         = 1 << 2;
  /** Debug pass for solid color or GL_LINES */
  constexpr uint32_t DebugPass          = 1 << 3;
  /** Textured object render pass with BRDF */
  constexpr uint32_t LightingPass = 1 << 4;
  /** Lights pass to render all the lights in the scene */
  constexpr uint32_t LocalLightsPass = 1 << 5;
  /** Pass specifically for 2D UI elements with no lighting or 3D
  * considerations, should always be last. */
  constexpr uint32_t UIPass             = 1 << 6;

  /** Default lit object passes */
  constexpr uint32_t DefaultLit         = GBufferPrepass | LightingPass | ShadowPass;

  static std::vector<uint32_t> RenderPassOrder;
}

#endif // !RENDER_FLAGS_H
