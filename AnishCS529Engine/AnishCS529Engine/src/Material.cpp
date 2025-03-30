/*!****************************************************************************
 * \file   Material.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-14-2024
 *
 *****************************************************************************/
#include "precompiled.h"
#include "Material.h"

std::unordered_map<std::string, std::shared_ptr<Material>> Material::basicMaterials;

void Material::setRenderGraph(std::shared_ptr<RenderGraph> newRenderGraph) {
  renderGraph = newRenderGraph;
}

std::shared_ptr<RenderGraph> Material::getRenderGraph() const {
  return renderGraph;
}

//void Material::setTexture(const std::string& name, std::shared_ptr<Texture> texture, unsigned int unit) {
//  if (!textureData) {
//    textureData = std::unordered_map<std::string, TextureInfo>();
//  }
//  (*textureData)[name] = { texture, unit };
//}

void Material::draw(std::shared_ptr<Mesh> mesh) const {
  
  PropertyMap temp = properties;
  for (const auto& property : tempProperties) {
    temp[property.first] = property.second;
  }

  renderGraph->draw(mesh, temp);
}
