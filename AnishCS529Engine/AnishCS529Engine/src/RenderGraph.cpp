#include "RenderGraph.h"

void RenderGraph::addPass(std::shared_ptr<RenderPass> pass)
{
  renderStack.push_back(pass);
}

void RenderGraph::draw(std::shared_ptr<Mesh> mesh, RenderPass::PropertyMap properties)
{
  for (auto pass = renderStack.begin(); pass != renderStack.end(); ++pass) {
    pass->get()->apply(properties);
    mesh->draw(renderer);
  }
}
