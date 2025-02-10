#include "LightManager.h"

int LightManager::addLight(std::shared_ptr<Light> light)
{
  lightStack.push_back(light);
  return static_cast<int>(lightStack.size() - 1);
}

std::shared_ptr<Light> LightManager::getLight(int index)
{
  if (index < lightStack.size())
    return lightStack[index];
  else
    return NULL;
}
