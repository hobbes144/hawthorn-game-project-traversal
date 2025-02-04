#include "AmbientLight.h"

void AmbientLight::applyToShader(Shader& shader, int lightIndex) const
{
  shader.setVec3("ambientLight_" + std::to_string(lightIndex) + "_color", color);
  shader.setFloat("ambientLight_" + std::to_string(lightIndex) + "_intensity", intensity);
}
