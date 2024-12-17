/*!****************************************************************************
 * \file   Wall.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 * \brief  Wall object
 * 
 *****************************************************************************/
#ifndef WALL_H
#define WALL_H

#pragma once

#include "AABB.h"
#include "GameObject.h"
#include "PhysicsBody.h"
#include "PhysicsManager.h"
#include "Render2D.h"

class Wall : public GameObject {
public:
  Wall(std::string name) : GameObject(name) {};
};

std::shared_ptr<Wall> createWall(
  std::string name, Renderer* renderer,
  std::shared_ptr<Camera> camera, Vector3 color);

#endif // WALL_H
