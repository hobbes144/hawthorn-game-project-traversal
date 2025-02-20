/*!****************************************************************************
 * \file   PointLight.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-03-2025
 * 
 *****************************************************************************/
#include "PointLight.h"

void PointLight::applyToShader(const std::shared_ptr<Shader>& shader, int lightIndex) const
{
  std::string uniformBase = "pointLights[" + std::to_string(lightIndex) + "]";
  shader->setVec3(uniformBase + ".position", position);
  shader->setFloat(uniformBase + ".range", range);
  shader->setVec3(uniformBase + ".color", color);
  shader->setFloat(uniformBase + ".intensity", intensity);
}
