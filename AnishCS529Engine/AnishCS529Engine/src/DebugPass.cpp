#include "precompiled.h"
#include "DebugPass.h"

void DebugPass::draw(std::shared_ptr<Mesh> mesh, GLenum mode,
  const PropertyMap& materialProperties, const LightStack& lightStack) const
{
  if (!materialProperties.contains("isDebug")) return;
  shader->use();
  applyProperties(properties, materialProperties);
  unsigned int lightIndex = 0;
  for (const auto& light : lightStack) {
    light->applyToShader(shader, lightIndex);
  }

  mesh->draw(GL_LINES);
}
