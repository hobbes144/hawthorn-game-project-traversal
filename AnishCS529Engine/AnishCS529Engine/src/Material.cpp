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

void Material::apply(std::shared_ptr<Shader> shader) const {
  for (const auto& [name, value] : properties) {
    if (auto item = std::get_if<unsigned int>(&value)) {
      shader->setUInt(name, *item);
    }
    else if (auto item = std::get_if<int>(&value)) {
      shader->setInt(name, *item);
    }
    else if (auto item = std::get_if<float>(&value)) {
      shader->setFloat(name, *item);
    }
    else if (auto item = std::get_if<VectorTemplated<float, 2>>(&value)) {
      shader->setVec2(name, (*item)[0], (*item)[1]);
    }
    else if (auto item = std::get_if<Vector3>(&value)) {
      shader->setVec3(name, *item);
    }
    else if (auto item = std::get_if<Matrix4>(&value)) {
      shader->setMat4(name, *item);
    }
    else if (auto item = std::get_if<TextureManager::TextureID>(&value)) {
      texturesToBind.emplace_back(name, *item);
    }
  }
}
