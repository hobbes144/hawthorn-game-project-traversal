#include "RenderGraph.h"
/*!****************************************************************************
 * \file   RenderGraph.inl
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-10-2025
 *
 *****************************************************************************/
#ifndef RENDER_GRAPH_INL
#define RENDER_GRAPH_INL

#pragma once


template <typename T>
std::shared_ptr<T> RenderGraph::addPass(const std::string& name) {
  static_assert(std::is_base_of<RenderPass, T>::value,
    "Pass must be derived from RenderPass class");

  if (registeredPasses.contains(name))
    return std::dynamic_pointer_cast<T>(registeredPasses[name]);

  auto pass = std::make_shared<T>();
  registeredPasses[name] = pass;
  renderStack.push_back(pass);
  return pass;
}


template <typename T>
std::shared_ptr<T> RenderGraph::addPass(const std::string& name, std::shared_ptr<T> pass) {
  if (registeredPasses.contains(name))
    return std::dynamic_pointer_cast<T>(registeredPasses[name]);

  registeredPasses[name] = pass;
  renderStack.push_back(pass);
  return pass;
}

template<typename T>
inline std::shared_ptr<T> RenderGraph::getPass(const std::string& name)
{
  return std::dynamic_pointer_cast<T>(registeredPasses[name]);
}

#endif // !RENDER_PASS_INL
