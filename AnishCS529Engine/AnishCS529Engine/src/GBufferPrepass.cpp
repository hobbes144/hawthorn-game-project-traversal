#include "precompiled.h"
#include "GBufferPrepass.h"
#include "Renderer.h"

GBufferPrepass::GBufferPrepass() : RenderPass() {
  this->addShader("shaders/gbuffer.vert\nshaders/gbuffer.frag");

  renderMask = RenderMask::GBufferPrepass;
}

void GBufferPrepass::initialize() {
  renderGraphBuilder->createScreenSizeTexture("GBuffer_position");
  renderGraphBuilder->createScreenSizeTexture("GBuffer_normal");
  renderGraphBuilder->createScreenSizeTexture("GBuffer_diffuse");
  renderGraphBuilder->createScreenSizeTexture("GBuffer_specular");
  gbuffer = renderGraphBuilder->createScreenSizeFBO(
    "GBuffer",
    {
      "GBuffer_position",
      "GBuffer_normal",
      "GBuffer_diffuse",
      "GBuffer_specular"
    });
}

void GBufferPrepass::draw(std::shared_ptr<Camera> camera, SceneGraph* sceneGraph) const {
  gbuffer->bind();

  gbuffer->clear();

  RenderPass::draw(camera, sceneGraph);

  gbuffer->unbind();
}
