/*!****************************************************************************
 * \file   TextureMaterial.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-10-2025
 * 
 *****************************************************************************/
#include "precompiled.h"
#include "TextureMaterial.h"

const std::string TextureMaterial::defaultTextureFile = "media/FactoryMaterial.bmp";

TextureManager::TextureID TextureMaterial::addTexture(const std::string& textureFile)
{
  TextureManager::TextureID texture = TextureManager::getInstance().loadFile(textureFile);
  this->setProperty("mainTexture", texture);
  return texture;
}

TextureManager::TextureID TextureMaterial::addDefaultTexture()
{
  return addTexture("media/FactoryMaterial.bmp");
}
