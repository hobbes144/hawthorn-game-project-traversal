#include "precompiled.h"
#include "GBufferPrepass.h"
#include "Renderer.h"

GBufferPrepass::GBufferPrepass() : RenderPass() {
  this->addShader("shaders/gbuffer.vert\nshaders/gbuffer.frag");

  renderMask = RenderMask::GBufferPrepass;
}

void GBufferPrepass::initialize() {
  renderGraphBuilder->createTexture("GBuffer_position");
  renderGraphBuilder->createTexture("GBuffer_normal");
  renderGraphBuilder->createTexture("GBuffer_diffuse");
  renderGraphBuilder->createTexture("GBuffer_specular");
  gbuffer = renderGraphBuilder->createFBO(
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

  renderGraphBuilder->getRenderer()->clear();

  RenderPass::draw(camera, sceneGraph);

  gbuffer->unbind();
}
