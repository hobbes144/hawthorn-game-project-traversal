/*!****************************************************************************
 * \file   Movement3D.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-11-2025
 * \brief  Basic 3D movement component
 * 
 *****************************************************************************/
#pragma once

#include <cassert>
#include <functional>

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
class Movement3D :
  public Component, public std::enable_shared_from_this<Movement3D> {

public:
  Movement3D() :
    force(2000.0f), rotationalForce(10.0f) {}
  ~Movement3D() = default;

  void initialize();
  void update(float deltaTime);
  void shutdown();

  enum Action {
    Forward, Back,  // Z axis
    Left, Right,    // X axis
    Up, Down,       // Y axis
    RollClockwise, RollAntiClockwise,   // Z axis
    PitchClockwise, PitchAnticlockwise, // X axis
    YawClockwise, YawAntiClockwise,     // Y axis
    Invalid
  };

  std::shared_ptr<Movement3D> setInputSystem(
    Input* _inputSystem);

  std::shared_ptr<Movement3D> setForce(float _force);
  std::shared_ptr<Movement3D> setRotationalForce(float _rotationalForce);
  std::shared_ptr<Movement3D> setAction(Action action, Key key);

private:
  Input* inputSystem;
  float force;
  float rotationalForce;
  std::unordered_map<Action, std::function<void(std::shared_ptr<PhysicsBody>)>> registeredActions;
};
