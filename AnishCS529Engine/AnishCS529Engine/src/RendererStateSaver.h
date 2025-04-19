/*!****************************************************************************
 * \file   RendererStateSaver.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-08-2025
 * \brief  State Saver class for the Renderer
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#ifndef RENDERER_STATE_SAVER_H
#define RENDERER_STATE_SAVER_H

#pragma once

#include "Renderer.h"

class Renderer::StateSaver {
public:
  explicit StateSaver(Renderer& renderer);
  ~StateSaver();

  // Disable moving
  StateSaver(const StateSaver&) = delete;
  StateSaver& operator=(const StateSaver&) = delete;

private:
  Renderer& savedRenderer;
  State savedState;
};

#endif // !RENDERER_STATE_SAVER_H
