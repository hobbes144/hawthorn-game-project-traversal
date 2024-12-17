/*!****************************************************************************
 * \file   BulletSpawnEvent.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 * \brief  Bullet Spawn Event class
 * 
 *****************************************************************************/

#pragma once

#include "Event.h"
#include "GameObject.h"

/*!****************************************************************************
 * \brief 
 *****************************************************************************/
class BulletSpawnEvent : public Event {
public:
  BulletSpawnEvent(
    std::shared_ptr<GameObject> _shooter)
    : shooter(_shooter) {}

  std::shared_ptr<GameObject> shooter;
};