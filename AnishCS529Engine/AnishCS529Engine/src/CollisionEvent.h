/*!****************************************************************************
 * \file   CollisionEvent.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \author Mariojulio Osmin Zaldivar Alvarez (ex-Adjunct Professor)
 *   (zaldivaralvarez@gmail.com) (Advising and Base Code)
 * \par    **Course**
 *    GAM541
 * \brief  Collision Event used by the Collision Generator
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 *
 *****************************************************************************/
#pragma once

#include "Event.h"
#include "GameObject.h"

class CollisionEvent : public Event {
public:
  CollisionEvent(
    std::shared_ptr<GameObject> obj1, std::shared_ptr<GameObject> obj2, Vector3 pnt)
    : object1(obj1), object2(obj2), point(pnt) {}

  std::shared_ptr<GameObject> object1;
  std::shared_ptr<GameObject> object2;
  Vector3 point;
};