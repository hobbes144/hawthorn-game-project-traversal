#include "precompiled.h"
#include "RenderGraphBuilder.h"
#include "Renderer.h"

FBO * RenderGraphBuilder::createFBO(const std::string & name, std::vector<std::string> attachments) {
  FBO * fbo = new FBO();

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
}

TextureManager::TextureID RenderGraphBuilder::getTexture(const std::string & name) {
  return textures[name];
}
