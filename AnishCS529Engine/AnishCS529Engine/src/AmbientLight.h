/*!****************************************************************************
 * \file   AmbientLight.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-03-2025
 * \brief  Ambient Light source
 * 
 *****************************************************************************/
#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#pragma once

#include "Light.h"

class AmbientLight : public Light {
public:
  void applyToShader(Shader& shader, int lightIndex) const;
};

#endif // !AMBIENT_LIGHT_H


