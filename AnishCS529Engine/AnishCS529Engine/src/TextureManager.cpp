/*!****************************************************************************
 * \file   TextureManager.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-08-2025
 * 
 *****************************************************************************/
#include "TextureManager.h"

TextureManager::~TextureManager()
{
  for (auto& texture : textures) {
    delete texture;
  }
}

TextureManager::TextureID TextureManager::loadFile(const std::string& filePath)
{
  /* Checking if Texture was already loaded and returning it. */
  if (loadedFiles.contains(filePath)) {
    return loadedFiles[filePath];
  }

  TextureInfo* textureInfo = new TextureInfo();

  textures.push_back(textureInfo);
  TextureID textureID = TextureID(textures.size() - 1);
  loadedFiles[filePath] = textureID;

  glGenTextures(1, &(textureInfo->id));
  glBindTexture(TEXTURE_2D, textureInfo->id);

  if (stbi_is_hdr(filePath.c_str())) {
    loadHDRFile(textureInfo, filePath);
  }
  else {
    loadSDRFile(textureInfo, filePath);
  }

  glBindTexture(TEXTURE_2D, 0);

  return TextureID();
}

TextureManager::TextureID TextureManager::createTexture(
  const unsigned int width, const unsigned int height,
  Texture::Format internal_format, const void* data,
  TextureParameters textureParameters)
{
  TextureInfo* textureInfo = new TextureInfo();
  textureInfo->width = width;
  textureInfo->height = height;
  textureInfo->format = internal_format;

  textures.push_back(textureInfo);
  TextureID textureID = TextureID(textures.size() - 1);

  glGenTextures(1, &(textureInfo->id));
  glBindTexture(TEXTURE_2D, textureInfo->id);

  createOpenGLTexture(textureInfo, data, textureParameters);

  glBindTexture(TEXTURE_2D, 0);

  return textureID;
}

void TextureManager::setTextureParameters(TextureID id, TextureParameters textureParameters)
{
  TextureInfo* textureInfo = textures[id];

  glBindTexture(TEXTURE_2D, textureInfo->id);
  setTextureParameters(*textureInfo, textureParameters);
  glBindTexture(TEXTURE_2D, 0);
}

void TextureManager::loadHDRFile(TextureInfo* textureInfo, const std::string& filepath)
{
  TextureParameters textureParameters = TextureParameters(
    TEXTURE_NEAREST, TEXTURE_LINEAR_MIPMAP_LINEAR,
    TEXTURE_REPEAT, TEXTURE_REPEAT);

  stbi_set_flip_vertically_on_load(true);
  int channels;
  float* data = stbi_loadf(
    filepath.c_str(), &(textureInfo->width), &(textureInfo->height), &channels, 4);

  assert(("ERROR::TEXTURE::LOADTEXTURE::LOADFAILED::" + filepath).c_str(), data);

  textureInfo->format = TEXTURE_RGBA32F;

  createOpenGLTexture(textureInfo, data, textureParameters);

  stbi_image_free(data);
}

void TextureManager::loadSDRFile(TextureInfo* textureInfo, const std::string& filepath)
{
  TextureParameters textureParameters = TextureParameters(
    TEXTURE_NEAREST, TEXTURE_LINEAR_MIPMAP_LINEAR,
    TEXTURE_REPEAT, TEXTURE_REPEAT);

  stbi_set_flip_vertically_on_load(true);
  int channels;
  unsigned char* data = stbi_load(
    filepath.c_str(), &(textureInfo->width), &(textureInfo->height), &channels, 0);

  assert(("ERROR::TEXTURE::LOADTEXTURE::LOADFAILED::" + filepath).c_str(), data);

  if (channels == 3)
    textureInfo->format = TEXTURE_RGB;
  else if (channels == 4)
    textureInfo->format = TEXTURE_RGBA;

  createOpenGLTexture(textureInfo, data, textureParameters);

  stbi_image_free(data);
}

void TextureManager::generateMipmaps(const TextureInfo& textureInfo)
{
  glGenerateMipmap(TEXTURE_2D);
}

void TextureManager::setTextureParameters(const TextureInfo& textureInfo, TextureParameters textureParameters)
{
  glTexParameteri(TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureParameters.mag_filter);
  glTexParameteri(TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureParameters.min_filter);

  glTexParameteri(TEXTURE_2D, GL_TEXTURE_WRAP_S, textureParameters.wrap_s);
  glTexParameteri(TEXTURE_2D, GL_TEXTURE_WRAP_T, textureParameters.wrap_t);

  if (
    textureParameters.min_filter == TEXTURE_NEAREST_MIPMAP_NEAREST ||
    textureParameters.min_filter == TEXTURE_NEAREST_MIPMAP_LINEAR ||
    textureParameters.min_filter == TEXTURE_LINEAR_MIPMAP_NEAREST ||
    textureParameters.min_filter == TEXTURE_LINEAR_MIPMAP_LINEAR
    ) {
    generateMipmaps(textureInfo);
  }
}

void TextureManager::createOpenGLTexture(TextureInfo* textureInfo, const void* data,
  TextureParameters textureParameters)
{
  glGenTextures(1, &(textureInfo->id));
  glBindTexture(TEXTURE_2D, textureInfo->id);

  Texture::Format format;
  if (textureInfo->format == TEXTURE_RGB || textureInfo->format == TEXTURE_RGB32F)
    format = TEXTURE_RGB;
  else if (textureInfo->format == TEXTURE_RGBA || textureInfo->format == TEXTURE_RGBA32F)
    format = TEXTURE_RGBA;
  else {
    std::cout << "WARNING::TEXTUREMANAGER::CREATETEXTURE::INVALIDFORMAT" 
      << "::Defaulting to TEXTURE_RGBA" << std::endl;
    format = TEXTURE_RGBA;
  }

  glTexImage2D(
    TEXTURE_2D, 0, textureInfo->format, textureInfo->width, textureInfo->height,
    0, format, GL_UNSIGNED_BYTE, data);

  setTextureParameters(*textureInfo, textureParameters);

  glBindTexture(TEXTURE_2D, 0);
}
