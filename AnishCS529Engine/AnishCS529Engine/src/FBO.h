/*!****************************************************************************
 * \file   FBO.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-09-2025
 * \brief  A slight encapsulation of a Frame Buffer Object (i'e' Render
 * Target) and its associated texture.  When the FBO is "Bound", the
 * output of the graphics pipeline is captured into the texture.  When
 * it is "Unbound", the texture is available for use as any normal
 * texture.
 * 
 *****************************************************************************/
#ifndef FBO_H
#define FBO_H

#pragma once

#include "TextureManager.h"

class Renderer;

class FBO {
public:
  unsigned int fboID;
  std::vector<unsigned int> textureIDs;
  int width, height;  // Size of the Buffer
  int x, y;  // Offset of the Buffer
  unsigned int attachedTextures = 0;

  void initialize();
  void finalize();

  void setViewport(
    const int _x, const int _y,
    const int _width, const int _height);

  void updateViewport();
  void updateViewport(
    const int _x, const int _y,
    const int _width, const int _height);

  void addScreenSizeBufferUpdateCallback(Renderer* renderer);

  void attachTexture(TextureManager::TextureID textureID);

  // Bind this FBO to receive the output of the graphics pipeline.
  void bind();

  // Unbind this FBO from the graphics pipeline;  graphics goes to screen by default.
  void unbind();

  void clear();
};

#endif // !FBO_H
