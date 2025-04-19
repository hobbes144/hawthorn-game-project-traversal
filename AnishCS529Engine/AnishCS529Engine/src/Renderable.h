/*!****************************************************************************
 * \file   Renderable.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-07-2025
 * \brief  Renderable base class for Render classes
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#ifndef RENDERABLE_H
#define RENDERABLE_H

#pragma once

#include "Shader.h"
#include "Component.h"

class Renderable : public Component {
protected:
  uint32_t renderMask;
public:
  virtual void draw(std::shared_ptr<Shader> shader) = 0;

  virtual void setRenderMask(uint32_t _renderMask) { renderMask = _renderMask; }
  virtual uint32_t getRenderMask() { return renderMask; }

};

#endif // !RENDERABLE_H
