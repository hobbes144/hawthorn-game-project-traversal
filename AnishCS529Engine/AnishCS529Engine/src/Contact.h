/*!****************************************************************************
 * \file   Contact.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \author Mariojulio Osmin Zaldivar Alvarez (ex-Adjunct Professor)
 *   (zaldivaralvarez@gmail.com) (Advising and Base Code)
 * \par    **Course**
 *    GAM541
 * \brief  Contact class used to store the contact info
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 *
 *****************************************************************************/
#pragma once

#include "PhysicsBody.h"

class Contact {
public:
  Contact() : bodies{ nullptr, nullptr } {}

  std::shared_ptr<PhysicsBody> bodies[2];    // The two bodies in contact
  Vector3 point;             // Point of contact (if needed for visualization)
};