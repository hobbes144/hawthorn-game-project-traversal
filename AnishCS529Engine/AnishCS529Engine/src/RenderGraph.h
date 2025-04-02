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
#include "SceneGraph.h"
#include "RenderPass.h"

class RenderGraph {
public:
  template <typename T>
  std::shared_ptr<T> addPass(const std::string& name);
  template <typename T>
  std::shared_ptr<T> addPass(const std::string& name, std::shared_ptr<T> pass);
  template <typename T>
  std::shared_ptr<T> getPass(const std::string& name);

  void draw(std::shared_ptr<SceneGraph> scene);

private:
  std::vector<std::shared_ptr<RenderPass>> renderStack;
  std::unordered_map<std::string, std::shared_ptr<RenderPass>> registeredPasses;
};

#include "RenderGraph.inl"

#endif // !RENDER_GRAPH_H
