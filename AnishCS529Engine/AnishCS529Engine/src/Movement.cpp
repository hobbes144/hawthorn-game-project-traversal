/*!****************************************************************************
 * \file   Movement.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 * 
 *****************************************************************************/
#include "Movement.h"


std::shared_ptr<Movement> Movement::setInputSystem(
  Input* _inputSystem)
{
  inputSystem = _inputSystem;

  return shared_from_this();
}

std::shared_ptr<Movement> Movement::setForce(float _f)
{
  f = _f;

  return shared_from_this();
}

std::shared_ptr<Movement> Movement::setUpKey(Key _upKey)
{
  upKey = _upKey;

  return shared_from_this();
}

std::shared_ptr<Movement> Movement::setDownKey(Key _downKey)
{
  downKey = _downKey;

  return shared_from_this();
}

std::shared_ptr<Movement> Movement::setLeftKey(Key _leftKey)
{
  leftKey = _leftKey;

  return shared_from_this();
}

std::shared_ptr<Movement> Movement::setRightKey(Key _rightKey)
{
  rightKey = _rightKey;

  return shared_from_this();
}

void Movement::initialize() {}

void Movement::update(float deltaTime)
{
  if (inputSystem->isKeyDown(upKey)) {
    parent->findComponent<PhysicsBody>()
      ->applyForce(Vector3(0.0f, f, 0.0f));
  }

  if (inputSystem->isKeyDown(downKey)) {
    parent->findComponent<PhysicsBody>()
      ->applyForce(Vector3(0.0f, -f, 0.0f));
  }

  if (inputSystem->isKeyDown(leftKey)) {
    parent->findComponent<PhysicsBody>()
      ->applyForce(Vector3(-f, 0.0f, 0.0f));
  }

  if (inputSystem->isKeyDown(rightKey)) {
    parent->findComponent<PhysicsBody>()
      ->applyForce(Vector3(f, 0.0f, 0.0f));
  }
}

void Movement::shutdown() {}