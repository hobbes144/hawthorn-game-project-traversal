#include "RenderGraph.h"

void RenderGraph::addPass(std::shared_ptr<RenderPass> pass)
{
  renderStack.push_back(pass);
}

void RenderGraph::draw(Renderer* renderer, std::shared_ptr<Mesh> mesh)
{
  for (auto pass = renderStack.begin(); pass != renderStack.end(); ++pass) {
    pass->get()->apply(globalProperties);
    mesh->draw(renderer);
  }
}
