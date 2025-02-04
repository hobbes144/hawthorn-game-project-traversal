/*!****************************************************************************
 * \file   PointLight.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-03-2025
 * 
 *****************************************************************************/
#include "PointLight.h"

void PointLight::applyToShader(Shader& shader, int lightIndex) const
{
  shader.setVec3("pointLight_" + std::to_string(lightIndex) + "_position", position);
  shader.setFloat("pointLight_" + std::to_string(lightIndex) + "_range", range);
  shader.setVec3("pointLight_" + std::to_string(lightIndex) + "_color", color);
  shader.setFloat("pointLight_" + std::to_string(lightIndex) + "_intensity", intensity);
}
