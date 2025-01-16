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
  RenderGraph() : globalProperties({}) {};

  void addPass(std::shared_ptr<RenderPass> pass);

  void draw(Renderer* renderer, std::shared_ptr<Mesh> mesh);

private:
  std::vector<std::shared_ptr<RenderPass>> renderStack;
  RenderPass::PropertyMap globalProperties;

};

#endif // !RENDER_GRAPH_H
