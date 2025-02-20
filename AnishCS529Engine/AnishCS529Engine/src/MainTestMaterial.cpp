#include "MainTestMaterial.h"

TextureManager::TextureID MainTestMaterial::addTexture(const std::string& textureFile, float scaleX, float scaleY)
{
  TextureManager::TextureID texture = TextureManager::getInstance().loadFile(textureFile);
  textures.push_back(texture);
  this->setProperty("numTextures", static_cast<int>(textures.size()));
  this->setProperty("texture" + std::to_string(textures.size() - 1), texture);
  this->setProperty("texScale" + std::to_string(textures.size() - 1),
    VectorTemplated<float, 2>(std::array<float, 2>{scaleX, scaleY}));

  return texture;
}

