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
