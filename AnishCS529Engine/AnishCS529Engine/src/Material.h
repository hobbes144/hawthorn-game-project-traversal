/*!****************************************************************************
 * \file   Material.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-14-2024
 * \brief  Material class
 *
 *****************************************************************************/
#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once

#include <unordered_map>
#include <variant>
#include <optional>

#include "Matrix4.h"
#include "Mesh.h"
#include "RenderGraph.h"
#include "Vector3.h"
#include "Texture.h"

 /*!****************************************************************************
  * \brief Class to manage Materials used by objects
  *
  * This class handles creation of shaders and setting parameters for them.
  *****************************************************************************/
class Material {
public:
  using PropertyMap = RenderPass::PropertyMap;

  Material(std::shared_ptr<RenderGraph> renderGraph) : renderGraph(renderGraph) {}
  virtual ~Material() = default;

  void setRenderGraph(std::shared_ptr<RenderGraph> newRenderGraph);
  std::shared_ptr<RenderGraph> getRenderGraph() const;

  template<typename T>
  void setProperty(const std::string& name, const T& value) {
    properties[name] = value;
  }

  virtual void draw(std::shared_ptr<Mesh> mesh) const;

private:
  std::shared_ptr<RenderGraph> renderGraph;
  PropertyMap properties;

  std::optional<std::unordered_map<std::string, TextureManager::TextureID>> textureData;

};

//std::shared_ptr<Material> createSolidColorMaterial(const Vector3& color);
//std::shared_ptr<Material> createTextureMaterial(const std::string& textureFile);

#endif // MATERIAL_H

// Challenge for you: Can you think of a way to templetize the setProperty() function?
// What about the properties map? Instead of a variant, could you use a template parameter? In that case, how would you handle setting the uniforms?