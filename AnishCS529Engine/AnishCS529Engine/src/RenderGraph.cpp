#include "RenderGraph.h"

void RenderGraph::addLight(std::shared_ptr<Light> light)
{
  lightStack.push_back(light);
}

void RenderGraph::draw(
  std::shared_ptr<Mesh> mesh,
  RenderPass::PropertyMap properties,
  GLenum mode)
{
  for (const auto& pass : renderStack) {
    pass->draw(mesh, mode, properties, lightStack);
  }
}
