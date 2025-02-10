#include "AmbientLight.h"

void AmbientLight::applyToShader(const std::shared_ptr<Shader>& shader, int lightIndex) const
{
  std::string uniformBase = "ambientLights[" + std::to_string(lightIndex) + "]";
  shader->setVec3(uniformBase + ".color", color);
  shader->setFloat(uniformBase + ".intensity", intensity);
}
