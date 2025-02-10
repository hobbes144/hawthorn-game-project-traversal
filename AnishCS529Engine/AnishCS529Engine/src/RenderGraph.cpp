#include "RenderGraph.h"

void RenderGraph::addPass(std::shared_ptr<RenderPass> pass)
{
  renderStack.push_back(pass);
}

void RenderGraph::addLight(std::shared_ptr<Light> light)
{
  lightStack.push_back(light);
}

void RenderGraph::draw(std::shared_ptr<Mesh> mesh, RenderPass::PropertyMap properties)
{
  for (const auto& pass : renderStack) {
    pass->apply(properties, lightStack);

    mesh->draw();
  }
}
