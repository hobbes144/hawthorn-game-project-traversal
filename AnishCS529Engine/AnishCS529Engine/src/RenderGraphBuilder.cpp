#include "precompiled.h"
#include "RenderGraphBuilder.h"
#include "Renderer.h"

TextureManager::TextureID RenderGraphBuilder::createTexture(
  const std::string& name) {
  TextureManager::TextureInfo textureInfo = TextureManager::TextureInfo();
  Renderer::Viewport viewport = renderer->getCurrentState().viewport;
  textureInfo.width = viewport.width;
  textureInfo.height = viewport.height;
  TextureManager::TextureID texture = TextureManager::getInstance().createTexture(textureInfo);
  textures[name] = texture;
}

TextureManager::TextureID RenderGraphBuilder::getTexture(const std::string & name) {
  return textures[name];
}
