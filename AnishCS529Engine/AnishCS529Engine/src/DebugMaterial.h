/*!****************************************************************************
 * \file   DebugMaterial.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-10-2025
 * \brief  Debug Material to only draw lines
 * 
 *****************************************************************************/
#ifndef DEBUG_MATERIAL_H
#define DEBUG_MATERIAL_H

#pragma once

#include "Material.h"

class DebugMaterial : public Material {
public:
  DebugMaterial() : Material() {
    this->setProperty("isDebug", 1);
  }
};

#endif // !DEBUG_MATERIAL_H
