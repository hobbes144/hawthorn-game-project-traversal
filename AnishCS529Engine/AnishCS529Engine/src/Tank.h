/*!****************************************************************************
 * \file   Tank.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-13-2024
 * \brief  Tank object
 * 
 *****************************************************************************/
#ifndef TANK_H
#define TANK_H

#pragma once

#include "AABB.h"
#include "GameObject.h"
#include "PhysicsBody.h"
#include "RigidBody.h"
#include "PhysicsManager.h"
#include "Render2D.h"

#include "Wall.h"

class Tank : public GameObject {
public:
  Tank(std::string name) : GameObject(name) {};
};

void onTankHit(
  std::shared_ptr<GameObject> obj1, 
  std::shared_ptr<GameObject> obj2, 
  const Vector3& point);

std::shared_ptr<Tank> createTank(
  std::string name, Renderer* renderer, 
  std::shared_ptr<Camera> camera, Vector3 color);

std::shared_ptr<Tank> createTank(
  std::string name, Renderer* renderer,
  std::shared_ptr<Camera> camera, const std::string& textureFile);

#endif // TANK_H
