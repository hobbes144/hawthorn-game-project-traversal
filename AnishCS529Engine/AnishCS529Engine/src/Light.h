/*!****************************************************************************
 * \file   Light.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-01-2025
 * \brief  Light class that stores light properties
 *
 *****************************************************************************/
#ifndef LIGHT_H
#define LIGHT_H

#pragma once

#include <memory>
#include <string>

#include "Vector3.h"

class Light : public std::enable_shared_from_this<Light> {
public:
  Vector3 color = Vector3(1.0);
  float intensity = 1.0f;
  bool castsShadows = false;
};

#endif // !LIGHT_H
