/*!****************************************************************************
 * \file   TextureManager.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-08-2025
 * \brief  Texture Manager class
 * 
 *****************************************************************************/
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#pragma once

#ifndef ENGINE_GRAPHICS_LIBRARY_H
#define ENGINE_GRAPHICS_LIBRARY_H
#include <glad/glad.h>
#endif // !ENGINE_GRAPHICS_LIBRARY_H

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "TextureParametersOpenGL.h"

/*
* ToDo: Figure out a more efficient way of calling commands here that do not
* involve repeatedly binding and unbinding the same texture.
*/

class TextureManager {
public:
  struct TextureID {
    unsigned int id;

    TextureID() : id(0) {}
    explicit TextureID(unsigned int id) : id(id) {}

    unsigned int operator=(unsigned int _id) { return id = _id; }
    operator unsigned int() const { return id; }
    bool operator==(const TextureID& other) const { return id == other.id; }
  };

  struct TextureParameters {
    Texture::FilterMode mag_filter;
    Texture::FilterMode min_filter;
    Texture::WrapMode wrap_s;
    Texture::WrapMode wrap_t;

    TextureParameters(
      Texture::FilterMode mag_filter = TEXTURE_NEAREST,
      Texture::FilterMode min_filter = TEXTURE_NEAREST_MIPMAP_LINEAR,
      Texture::WrapMode wrap_s = TEXTURE_CLAMP_TO_EDGE,
      Texture::WrapMode wrap_t = TEXTURE_CLAMP_TO_EDGE
      ) : 
      mag_filter(mag_filter), min_filter(min_filter),
      wrap_s(wrap_s), wrap_t(wrap_t) {}
  };

  struct TextureInfo {
    GLuint id;
    int width, height;
    Texture::Format format;
  };

  static TextureManager& getInstance() {
    static TextureManager instance;
    return instance;
  }
  ~TextureManager();

  TextureID loadFile(const std::string& filePath);
  TextureID createTexture(
    const unsigned int width, const unsigned int height,
    Texture::Format internal_format, const void* data,
    TextureParameters textureParameters = TextureParameters()
    );

  void setTextureParameters(
    TextureID id, TextureParameters textureParameters);

private:
  TextureManager() = default;
  std::vector<TextureInfo*> textures;
  std::unordered_map<std::string,TextureID> loadedFiles;

  void loadHDRFile(TextureInfo* textureInfo, const std::string& filepath);
  void loadSDRFile(TextureInfo* textureInfo, const std::string& filepath);

  void generateMipmaps(const TextureInfo& textureInfo);

  void setTextureParameters(
    const TextureInfo& textureInfo, TextureParameters textureParameters);

  void createOpenGLTexture(TextureInfo* textureInfo, const void* data,
    TextureParameters textureParameters);
};

#endif // !TEXTURE_MANAGER_H
