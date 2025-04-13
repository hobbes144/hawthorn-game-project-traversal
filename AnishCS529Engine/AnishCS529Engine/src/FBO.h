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

class FBO {
public:
  unsigned int fboID;
  unsigned int textureID;
  int width, height;  // Size of the texture.
  unsigned int attachedTextures = 0;

  void initialize();
  void finalize();

  void setViewport(const int w, const int h);

  void attachTexture(TextureManager::TextureID textureID);

  // Bind this FBO to receive the output of the graphics pipeline.
  void bind();

  // Unbind this FBO from the graphics pipeline;  graphics goes to screen by default.
  void unbind();
};

#endif // !FBO_H
