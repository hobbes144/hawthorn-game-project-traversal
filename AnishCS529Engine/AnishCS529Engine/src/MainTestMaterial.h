/*!****************************************************************************
 * \file   MainTestMaterial.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-13-2025
 * \brief  Testing material for Engine demo
 * 
 *****************************************************************************/
#ifndef MAIN_TEST_MATERIAL_H
#define MAIN_TEST_MATERIAL_H

#pragma once

#include "Material.h"

class MainTestMaterial : public Material {
public:
  MainTestMaterial() : Material() {
    this->setProperty("numTextures", 0);
    this->setProperty("enableShadows", 0);
    this->setProperty("enableReflections", 0);
    this->setProperty("enableIrradiance", 0);
    this->setProperty("enableExposure", 0);
    this->setProperty("objectId", 0);
  }

  TextureManager::TextureID addTexture(const std::string& textureFile,
    float scaleX = 1.0f, float scaleY = 1.0f);

private:
  std::vector<TextureManager::TextureID> textures;
  bool textureMode = false;
};

#endif // !MAIN_TEST_MATERIAL_H
