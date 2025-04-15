#include "precompiled.h"
#include "SkydomePass.h"

SkydomePass::SkydomePass(TextureManager::TextureID textureID) :
  RenderPass(), sphereMesh(Mesh::createSphereMesh("sphere", 32)),
  scale(Matrix4::scale(Vector3(2000.0f))) {

  this->addShader("shaders/skydome.vert\nshaders/skydome.frag");
  shader->initializeUBO("camera", 0);

  skydomeTexture = textureID;
  HDR = TextureManager::getInstance().isHDR(skydomeTexture);

  renderMask = RenderMask::SkydomePass;
}

SkydomePass::SkydomePass(const std::string& textureName) :
  RenderPass(), sphereMesh(Mesh::createSphereMesh("sphere", 32)),
  scale(Matrix4::scale(Vector3(2000.0f))) {

  this->addShader("shaders/skydome.vert\nshaders/skydome.frag");
  shader->initializeUBO("camera", 0);

  skydomeTexture = TextureManager::getInstance().loadFile(textureName);
  HDR = TextureManager::getInstance().isHDR(skydomeTexture);

  setProperty(
    "skydomeTexture", skydomeTexture);
  setProperty(
    "HDR", HDR);

  renderMask = RenderMask::SkydomePass;
}

void SkydomePass::draw(
  std::shared_ptr<Camera> camera,
  SceneGraph* sceneGraph) const {
  glDepthMask(GL_FALSE);

  shader->use();

  applyProperties();

  sphereMesh->draw(GL_TRIANGLES);

  unbindTextures();

  shader->unuse();

  glDepthMask(GL_TRUE);
  glClear(GL_DEPTH_BUFFER_BIT);
}
