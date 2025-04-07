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

  void initialize();

  template <typename T>
  std::shared_ptr<T> addPass(const std::string& name);
  template <typename T>
  std::shared_ptr<T> addPass(const std::string& name, std::shared_ptr<T> pass);
  template <typename T>
  std::shared_ptr<T> getPass(const std::string& name);

  void draw(SceneGraph* scene);

private:
  std::vector<std::shared_ptr<RenderPass>> renderStack;
  std::unordered_map<std::string, std::shared_ptr<RenderPass>> registeredPasses;
  unsigned int uboLights;
  unsigned int uboCamera;

  void initializeLightUBOs();
  void initializeCameraUBO();

  void updateLightUBOs(Lights lights);
  void updateCameraUBO(std::shared_ptr<Camera> camera);
};

#include "RenderGraph.inl"

#endif // !RENDER_GRAPH_H
