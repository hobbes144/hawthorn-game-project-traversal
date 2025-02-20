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
#include "Light.h"

#include "LightingPass.h"

class RenderGraph {
public:
  template <typename T>
  std::shared_ptr<T> addPass(const std::string& name);
  template <typename T>
  std::shared_ptr<T> addPass(const std::string& name, std::shared_ptr<T> pass);
  template <typename T>
  std::shared_ptr<T> getPass(const std::string& name);

  void addLight(std::shared_ptr<Light> light);

  void draw(
    std::shared_ptr<Mesh> mesh, 
    RenderPass::PropertyMap properties, 
    GLenum mode = GL_TRIANGLES);

private:
  std::vector<std::shared_ptr<RenderPass>> renderStack;
  std::vector<std::shared_ptr<Light>> lightStack;
  std::unordered_map<std::string, std::shared_ptr<RenderPass>> registeredPasses;
};

#include "RenderGraph.inl"

#endif // !RENDER_GRAPH_H
