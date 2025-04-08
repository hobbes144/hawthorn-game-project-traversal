/*!****************************************************************************
 * \file   Renderable.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-07-2025
 * \brief  Renderable base class for Render classes
 * 
 *****************************************************************************/
#ifndef RENDERABLE_H
#define RENDERABLE_H

#pragma once

#include "Shader.h"
#include "Component.h"

class Renderable : public Component {
public:
  virtual void draw(std::shared_ptr<Shader> shader) = 0;
};

#endif // !RENDERABLE_H
