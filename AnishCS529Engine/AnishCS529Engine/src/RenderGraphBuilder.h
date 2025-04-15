/*!****************************************************************************
 * \file   RenderGraphBuilder.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   04-09-2025
 * \brief  Render Graph Builder that manager resources related to the render
 * graph
 * 
 *****************************************************************************/
#ifndef RENDER_GRAPH_BUILDER_H
#define RENDER_GRAPH_BUILDER_H

#pragma once

#include "RenderFlags.h"
#include "TextureManager.h"
#include "FBO.h"

class Renderer;

class RenderGraphBuilder {
public:
  RenderGraphBuilder(Renderer* _renderer) : renderer(_renderer) {}
  ~RenderGraphBuilder() { clear(); };
  
  FBO* createScreenSizeFBO(const std::string& name, std::vector<std::string> attachments);
  TextureManager::TextureID createScreenSizeTexture(const std::string& name);

  FBO* getFBO(const std::string& name);
  TextureManager::TextureID getTexture(const std::string& name);

  void clearFBOs();
  void clearTextures();
  void clear();

  Renderer* getRenderer() { return renderer; };

private:
  Renderer* renderer;
  std::unordered_map<std::string, TextureManager::TextureID> textures;
  std::unordered_map<std::string, FBO*> fbos;
};

#endif // !RENDER_GRAPH_BUILDER_H
