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

#include <typeindex>

#include "Mesh.h"
#include "SceneGraph.h"
#include "RenderPass.h"

class RenderGraph {
public:

  void initialize();

  template <typename T>
  std::shared_ptr<T> addPass();
  template <typename T>
  std::shared_ptr<T> addPass(std::shared_ptr<T> pass);
  template <typename T>
  std::shared_ptr<T> getPass();

  void draw(SceneGraph* scene);

private:
  std::vector<std::shared_ptr<RenderPass>> renderStack;
  unsigned int uboLights;
  unsigned int uboCamera;

  std::unordered_map<uint32_t, size_t> maskSortIndex;
  std::unordered_set<std::type_index> addedPassTypes;

  void initializeLightUBOs();
  void initializeCameraUBO();

  void updateLightUBOs(Lights lights);
  void updateCameraUBO(std::shared_ptr<Camera> camera);
};

#include "RenderGraph.inl"

#endif // !RENDER_GRAPH_H
