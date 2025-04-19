/*!****************************************************************************
 * \file   CollisionListener.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \author Mariojulio Osmin Zaldivar Alvarez (ex-Adjunct Professor)
 *   (zaldivaralvarez@gmail.com) (Advising and Base Code)
 * \par    **Course**
 *    GAM541
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 *
 *****************************************************************************/
#include "precompiled.h"
#include "CollisionListener.h"

CollisionListener::CollisionListener(std::shared_ptr<GameObject> owner) : 
  owner(owner) {

  RegisterListener();
}


void CollisionListener::OnEvent(const CollisionEvent& event) {

  if (event.object1 == owner || event.object2 == owner) {
    //std::cout << "Collision detected for " << owner->getName() << std::endl;

    std::shared_ptr<GameObject> other = 
      (event.object1 == owner) ? event.object2 : event.object1;
    if (onCollisionCallback) {
      onCollisionCallback(owner, other, event.point);
    }
  }
}
