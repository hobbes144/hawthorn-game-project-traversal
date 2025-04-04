#include "precompiled.h"
#include "RenderGraph.h"

void RenderGraph::draw(SceneGraph* scene)
{
  for (const auto& camera : scene->getCameras()) {

    // Setup camera specific stuff here
    // For now, we completely ignore this and just assume only one camera.
    // Adding multiple cameras is too complex for me now.

    for (const auto& pass : renderStack) {
      pass->draw(camera, scene);
    }

  }
}
