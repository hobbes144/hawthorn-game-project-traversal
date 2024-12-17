/*!****************************************************************************
 * \file   Bullet.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 * \brief  Bullet object
 * 
 *****************************************************************************/
#ifndef BULLET_H
#define BULLET_H

#pragma once

#include "AABB.h"
#include "CollisionListener.h"
#include "GameObject.h"
#include "PhysicsBody.h"
#include "PhysicsManager.h"
#include "Render2D.h"

#include "Tank.h"
#include "Wall.h"

class Bullet : public GameObject {
public:
  Bullet(std::string name) : GameObject(name) {};

  std::shared_ptr<Bullet> setOwner(std::shared_ptr<GameObject> _owner);
  std::shared_ptr<GameObject> getOwner();
private:
  std::shared_ptr<GameObject> owner;
};

void bulletHit(std::shared_ptr<GameObject> obj1, std::shared_ptr<GameObject> obj2);

std::shared_ptr<Bullet> createBullet(
  std::string name, Renderer* renderer,
  std::shared_ptr<Camera> camera, Vector3 color);

#endif // BULLET_H
