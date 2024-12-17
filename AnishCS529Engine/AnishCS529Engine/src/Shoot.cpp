/*!****************************************************************************
 * \file   Shoot.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 * 
 *****************************************************************************/
#include "Shoot.h"


std::shared_ptr<Shoot> Shoot::setInputSystem(
  Input* _inputSystem)
{
  inputSystem = _inputSystem;

  return shared_from_this();
}

std::shared_ptr<Shoot> Shoot::setBulletPool(
  std::vector<std::shared_ptr<Bullet>> _bulletPool)
{
  bulletPool = _bulletPool;

  return shared_from_this();
}

std::shared_ptr<Shoot> Shoot::setBulletVelocity(float _bulletVelocity)
{
  bulletVelocity = _bulletVelocity;

  return shared_from_this();
}

std::shared_ptr<Shoot> Shoot::setShootKey(Key _shootKey)
{
  shootKey = _shootKey;

  return shared_from_this();
}

void Shoot::initialize() {}

void Shoot::update(float deltaTime)
{
  if (inputSystem->isKeyPressed(shootKey)) {
    auto bulletFound = std::find_if(
      bulletPool.begin(),
      bulletPool.end(),
      [&](std::shared_ptr<Bullet> candidate) {
        if (!candidate->isEnabled()) return true;
        else return false;
      }
    );
    if (bulletFound == bulletPool.end()) {
      std::cout << "No bullets left";
      return;
    }

    std::shared_ptr<Bullet> bullet = *bulletFound;
    float offset;
    if (parent->getName() == "protag") {
      offset = 1.0f;
    }
    else {
      offset = -1.0f;
    }

    bullet->setLocalPosition(
        bullet->getLocalScaling().reciprocal() * (
          parent->getLocalPosition() + Vector3(offset, 0.0f, 0.0f)
        )
      );
    bullet->findComponent<PhysicsBody>()
      ->setVelocity(Vector3(offset * bulletVelocity, 0.0f, 0.0f));
    bullet->enable();
  }
}

void Shoot::shutdown() {}