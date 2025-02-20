/*!****************************************************************************
 * \file   PointLight.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-03-2025
 * \brief  Point Light source class
 * 
 *****************************************************************************/
#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#pragma once

#include "Light.h"

class PointLight : public Light {
public:
  Vector3 position;
  /* Range for attenuation in many local lights pass */
  float range = 0.0f;

  void applyToShader(const std::shared_ptr<Shader>& shader, int lightIndex) const;

};

#endif // !POINT_LIGHT_H


