/*!****************************************************************************
 * \file   Movement.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 * \brief  Movement system for the tanks
 * 
 *****************************************************************************/
#pragma once

#include "Component.h"
#include "Input.h"
#include "GameObject.h"
#include "PhysicsBody.h"


/*!****************************************************************************
 * \brief Simple movement component implementing 2D movement
 * 
 * ## Usage:
 * 
 * This can be assigned to a GameObject to enable movement for it.
 * 
 * ## Pre-initialization calls:
 * 
 * - setInputSystem(std::shared_ptr<Input> _inputSystem)
 * - setForce(float _f)
 * 
 *****************************************************************************/
class Movement : 
  public Component, public std::enable_shared_from_this<Movement> {

public:
  Movement() :
    upKey(KEY_W), downKey(KEY_S), leftKey(KEY_A), rightKey(KEY_D),
    f(2000.0f) {}
  ~Movement() = default;

  void initialize();
  void update(float deltaTime);
  void shutdown();

  std::shared_ptr<Movement> setInputSystem(
    Input* _inputSystem);

  std::shared_ptr<Movement> setForce(float _f);
  std::shared_ptr<Movement> setUpKey(Key _upKey);
  std::shared_ptr<Movement> setDownKey(Key _downKey);
  std::shared_ptr<Movement> setLeftKey(Key _leftKey);
  std::shared_ptr<Movement> setRightKey(Key _rightKey);

private:
  Input* inputSystem;
  float f;
  Key upKey;
  Key downKey;
  Key leftKey;
  Key rightKey;
};
