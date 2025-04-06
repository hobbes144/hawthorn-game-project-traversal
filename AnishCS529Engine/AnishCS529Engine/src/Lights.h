/*!****************************************************************************
 * \file   Lights.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-04-2025
 * \brief  Lights supported by the engine
 * 
 *****************************************************************************/
#ifndef LIGHTS_H
#define LIGHTS_H

#pragma once

#include "Vector3.h"

struct DirectionalLight {
  Vector3 direction;
  Vector3 color;
  float intensity;
};

struct PointLight {
  Vector3 position;
  Vector3 color;
  float intensity;
  float range;
};

struct AmbientLight {
  Vector3 color;
  float intensity;
};

struct Lights {
  std::optional<DirectionalLight> sunLight;
  std::optional<AmbientLight> ambientLight;
  std::vector<PointLight> pointLights;
};

#endif // !LIGHTS_H
