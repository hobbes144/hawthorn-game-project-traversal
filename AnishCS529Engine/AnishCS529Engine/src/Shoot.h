/*!****************************************************************************
 * \file   Shoot.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 * \brief  Shoot component for the tanks
 * 
 *****************************************************************************/
#pragma once

#include "Component.h"
#include "Input.h"
#include "GameObject.h"
#include "PhysicsBody.h"
#include "Bullet.h"


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
class Shoot :
  public Component, public std::enable_shared_from_this<Shoot> {

public:
  Shoot() :
    shootKey(KEY_SPACE),
    bulletVelocity(100.0f) {}
  ~Shoot() = default;

  void initialize();
  void update(float deltaTime);
  void shutdown();

  std::shared_ptr<Shoot> setInputSystem(
    Input* _inputSystem);
  std::shared_ptr<Shoot> setBulletPool(
    std::vector<std::shared_ptr<Bullet>> _bulletPool);

  std::shared_ptr<Shoot> setBulletVelocity(float _bulletVelocity);
  std::shared_ptr<Shoot> setShootKey(Key _shootKey);

private:
  Input* inputSystem;
  std::vector<std::shared_ptr<Bullet>> bulletPool;
  float bulletVelocity;
  Key shootKey;
};
