/*!****************************************************************************
 * \file   TextureMaterial.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-10-2025
 * \brief  Texture Material to draw basic textures
 *
 *****************************************************************************/
#ifndef TEXTURE_MATERIAL_H
#define TEXTURE_MATERIAL_H

#pragma once

#include "Material.h"

class TextureMaterial : public Material {
public:
  TextureMaterial() : Material() {

    TextureManager::TextureID texture = 
      TextureManager::getInstance().loadFile("media/FactoryMaterial.bmp");

    this->setProperty("mainTexture", texture);
    this->setProperty("useTexture", 1);
    this->setProperty("isTransparent", 0);
  }

  TextureManager::TextureID addTexture(const std::string& textureFile);
  TextureManager::TextureID addDefaultTexture();
private:
  static const std::string defaultTextureFile;
};

#endif // !TEXTURE_MATERIAL_H
