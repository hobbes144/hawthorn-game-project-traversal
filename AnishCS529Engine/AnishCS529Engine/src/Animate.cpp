/*!****************************************************************************
 * \file   Animate.cpp
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
#include "Animate.h"


std::shared_ptr<Animate> Animate::setAnimateFunction(std::function<void(std::shared_ptr<GameObject>, float)> _animateFunction)
{
  animateFunction = _animateFunction;
  return shared_from_this();
}

std::shared_ptr<Animate> Animate::runAnimateFunction(bool _run)
{
  run = _run;
  return shared_from_this();
}

void Animate::initialize()
{
}

void Animate::update(float deltaTime)
{
  animateFunction(this->getParent(), deltaTime);
}

void Animate::shutdown()
{
}
