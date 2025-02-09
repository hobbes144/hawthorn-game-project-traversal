/*!****************************************************************************
 * \file   RenderGraph.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   01-16-2025
 * \brief  RenderGraph class
 * 
 *****************************************************************************/
#ifndef RENDER_GRAPH_H
#define RENDER_GRAPH_H

#pragma once

#include "Mesh.h"
#include "RenderPass.h"

class RenderGraph {
public:
  RenderGraph(Renderer* renderer) : renderer(renderer) {};

  void addPass(std::shared_ptr<RenderPass> pass);

  void draw(std::shared_ptr<Mesh> mesh, RenderPass::PropertyMap peroperties);

private:
  Renderer* renderer;
  std::vector<std::shared_ptr<RenderPass>> renderStack;

};

#endif // !RENDER_GRAPH_H
