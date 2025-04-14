#include "precompiled.h"
#include "RenderGraphBuilder.h"
#include "Renderer.h"

FBO* RenderGraphBuilder::createScreenSizeFBO(
  const std::string& name, std::vector<std::string> attachments) {
  FBO* fbo = new FBO();
  Renderer::Viewport viewport = renderer->getCurrentState().viewport;
  fbo->setViewport(viewport.x, viewport.y, viewport.width, viewport.height);
  fbo->initialize();
  fbos[name] = fbo;

  for (const auto& attachment : attachments) {
    fbo->attachTexture(textures[attachment]);
  }

  fbo->finalize();
  fbo->addScreenSizeBufferUpdateCallback(renderer);

  return fbo;
}

TextureManager::TextureID RenderGraphBuilder::createScreenSizeTexture(
  const std::string& name) {
  TextureManager::TextureInfo textureInfo = TextureManager::TextureInfo();
  Renderer::Viewport viewport = renderer->getCurrentState().viewport;
  textureInfo.width = viewport.width;
  textureInfo.height = viewport.height;
  textureInfo.format = TEXTURE_RGBA32F;
  TextureManager::TextureParameters textureParameters = TextureManager::TextureParameters();
  textureParameters.max_level = 0;
  textureParameters.wrap_s = TEXTURE_CLAMP_TO_EDGE;
  textureParameters.wrap_t = TEXTURE_CLAMP_TO_EDGE;
  textureParameters.mag_filter = TEXTURE_LINEAR;
  textureParameters.min_filter = TEXTURE_LINEAR;
  TextureManager::TextureID texture = TextureManager::getInstance().createTexture(textureInfo, nullptr, textureParameters);
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
