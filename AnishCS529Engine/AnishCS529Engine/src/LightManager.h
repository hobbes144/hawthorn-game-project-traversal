/*!****************************************************************************
 * \file   LightManager.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-01-2025
 * \brief  Light Manager that handles registration and organization of lights
 *
 *****************************************************************************/
#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#pragma once

#include <memory>
#include <vector>

#include "Light.h"

class LightManager {
public:
  int addLight(std::shared_ptr<Light> light);
  std::shared_ptr<Light> getLight(int index);

private:
  std::vector<std::shared_ptr<Light>> lightStack;
};

#endif // !LIGHT_MANAGER_H
