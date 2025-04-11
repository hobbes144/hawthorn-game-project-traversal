#include "precompiled.h"
#include "RenderGraphBuilder.h"
#include "Renderer.h"

FBO* RenderGraphBuilder::createFBO(const std::string& name, std::vector<std::string> attachments) {
  FBO* fbo = new FBO();
  Renderer::Viewport viewport = renderer->getCurrentState().viewport;
  fbo->setViewport(viewport.width, viewport.height);
  fbo->initialize();
  fbos[name] = fbo;

  for (const auto& attachment : attachments) {
    fbo->attachTexture(textures[attachment]);
  }

  return fbo;
}

TextureManager::TextureID RenderGraphBuilder::createTexture(
  const std::string& name) {
  TextureManager::TextureInfo textureInfo = TextureManager::TextureInfo();
  Renderer::Viewport viewport = renderer->getCurrentState().viewport;
  textureInfo.width = viewport.width;
  textureInfo.height = viewport.height;
  textureInfo.format = TEXTURE_RGBA32F;
  TextureManager::TextureID texture = TextureManager::getInstance().createTexture(textureInfo);
  textures[name] = texture;

  return texture;
}

FBO* RenderGraphBuilder::getFBO(const std::string & name) {
  return fbos[name];
}

TextureManager::TextureID RenderGraphBuilder::getTexture(const std::string & name) {
  return textures[name];
}

void RenderGraphBuilder::clearFBOs() {
  for ( const auto & [name, fbo] : fbos ) {
    delete fbo;
  }
}
