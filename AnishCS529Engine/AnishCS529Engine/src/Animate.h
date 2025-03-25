/*!****************************************************************************
 * \file   Animate.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   03-24-2025
 * \brief  Animation component
 * 
 *****************************************************************************/
#ifndef ANIMATE_H
#define ANIMATE_H

#pragma once

#include "Component.h"
#include <functional>

class Animate : public Component, public std::enable_shared_from_this<Animate> {
public:
  Animate() : Component(), 
    animateFunction([](std::shared_ptr<GameObject>, float){return;}), 
    run(false) {}

  virtual void initialize();
  virtual void update(float deltaTime);
  virtual void shutdown();

  std::shared_ptr<Animate> setAnimateFunction(
    std::function<void(std::shared_ptr<GameObject>, float)> _animateFunction);

  std::shared_ptr<Animate> runAnimateFunction(bool _run);


private:
  std::function<void(std::shared_ptr<GameObject>, float)> animateFunction;
  bool run;
};
#endif // !ANIMATE_H
