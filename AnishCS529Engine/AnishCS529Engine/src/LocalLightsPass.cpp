#include "precompiled.h"
#include "LocalLightsPass.h"
#include "Renderer.h"
#include "RendererStateSaver.h"

LocalLightsPass::LocalLightsPass() :
  RenderPass(), sphereMesh(Mesh::createSphereMesh("sphere", 32)) {

  this->addShader("shaders/local_lights.vert\nshaders/local_lights.frag");
  //shader->initializeUBO("camera", 0);
  //shader->initializeSSBO("LightBuffer", 2);

  renderMask = RenderMask::LocalLightsPass;
}

void LocalLightsPass::initialize()
{
  setProperty(
    "GBuffer_position", renderGraphBuilder->getTexture("GBuffer_position"));
  setProperty(
    "GBuffer_normal", renderGraphBuilder->getTexture("GBuffer_normal"));
  setProperty(
    "GBuffer_diffuse", renderGraphBuilder->getTexture("GBuffer_diffuse"));
  setProperty(
    "GBuffer_specular", renderGraphBuilder->getTexture("GBuffer_specular"));
}

void LocalLightsPass::draw(
  std::shared_ptr<Camera> camera,
  SceneGraph* sceneGraph) const {

  unsigned int lightCount = sceneGraph->getLights()->pointLights.size();

  if (lightCount == 0)
    return;

  Renderer::StateSaver savedState(*(renderGraphBuilder->getRenderer()));

  Renderer::Viewport viewport = renderGraphBuilder->getRenderer()->getCurrentState().viewport;
  
  renderGraphBuilder->getRenderer()->setDepthState(Renderer::DepthState(false));
  renderGraphBuilder->getRenderer()->setBlendState(Renderer::BlendState(true));

  Lights* lights = sceneGraph->getLights();

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  shader->use();

  applyProperties();

  shader->setUInt("height", viewport.height);
  shader->setUInt("width", viewport.width);

  for ( unsigned int lightIndex = 0; lightIndex < lightCount; ++lightIndex) {
    shader->setUInt("lightIndex", lightIndex);

    sphereMesh->draw(GL_TRIANGLES);
  }

  unbindTextures();

  shader->unuse();

  glDisable(GL_CULL_FACE);
}
