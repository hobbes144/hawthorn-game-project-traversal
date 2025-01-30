/*!****************************************************************************
 * \file   Bullet.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 * 
 *****************************************************************************/
#include "Bullet.h"

/*!****************************************************************************
 * \brief Set the owner of the bullet
 * 
 * ## Usage:
 * 
 * This is used to find out who gets credit for the kill if it hits an enemy.
 * 
 * \param _owner
 * \return \b 
 *****************************************************************************/
std::shared_ptr<Bullet> Bullet::setOwner(std::shared_ptr<GameObject> _owner)
{
  owner = _owner;
  return std::static_pointer_cast<Bullet>(shared_from_this());
}

std::shared_ptr<GameObject> Bullet::getOwner()
{
  return owner;
}


void onBulletHit(std::shared_ptr<GameObject> obj1, std::shared_ptr<GameObject> obj2, const Vector3& point){
  std::shared_ptr<Bullet> bullet;
  std::shared_ptr<GameObject> other;
  if (!(bullet = std::dynamic_pointer_cast<Bullet>(obj1))) {
    bullet = std::dynamic_pointer_cast<Bullet>(obj2);
    other = obj1;
  }
  else {
    other = obj2;
  }

  auto tankPtr = std::dynamic_pointer_cast<Tank>(other);
  if (tankPtr) {
    tankPtr->disable();
    bullet->disable()->setLocalPosition(Vector3(100.0f, 0.0f, 0.0f));
    return;
  }

  auto wallPtr = std::dynamic_pointer_cast<Wall>(other);
  if (wallPtr) {
    bullet->disable()->setLocalPosition(Vector3(100.0f, 0.0f, 0.0f));
    return;
  }
}

std::shared_ptr<Bullet> createBullet(std::string name, Renderer* renderer, std::shared_ptr<Camera> camera, Vector3 color)
{
  auto bullet = std::make_shared<Bullet>(name);
  bullet->addComponent<Render2D>()
    ->setRenderer(renderer)->setCamera(camera)
    ->setMaterial(createSolidColorMaterial(color))
    ->setMesh(createSquareMesh(name));

  auto bulletShape = std::make_shared<AABB>(
    Vector3(-0.5f, -0.5f, -0.5f),
    Vector3(0.5f, 0.5f, 0.5f));

  bullet->addComponent<PhysicsBody>()
    ->setMass(1.0f)->setDrag(0.0f)
    ->setShape(bulletShape)
    ->registerToPhysicsManager(PhysicsManager::Instance());
  bullet->setLocalScaling(Vector3(0.2f, 0.2f, 0.2f));
  bullet->disable();

  return bullet;
}
