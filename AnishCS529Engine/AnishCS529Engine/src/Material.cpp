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
#include "Material.h"

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
  renderGraph->draw(mesh, properties);
}

///*!****************************************************************************
// * \brief Factory to create a solid color render material
// *
// * \param color Color to be rendered
// * \return \b std::shared_ptr<Material> Material created
// *****************************************************************************/
//std::shared_ptr<Material> createSolidColorMaterial(const Vector3& color)
//{
//  auto newShader = std::make_shared<Shader>("shaders/factory_vertex_shader.vert.glsl\nshaders/factory_frag_shader.frag.glsl");
//  auto newMaterial = std::make_shared<Material>(newShader);
//  newMaterial->setProperty("Color", color);
//  newMaterial->setProperty("useTexture", 0);
//  newMaterial->setProperty("isTransparent", 0);
//  return newMaterial;
//}

//std::shared_ptr<Material> createTextureMaterial(const std::string& textureFile)
//{
//  auto newShader = std::make_shared<Shader>("shaders/factory_vertex_shader.vert.glsl\nshaders/factory_frag_shader.frag.glsl");
//  auto newMaterial = std::make_shared<Material>(newShader);
//  std::shared_ptr<Texture> texture = Texture::create(textureFile);
//  newMaterial->setTexture("mainTexture", texture, 0);
//  newMaterial->setProperty("useTexture", 1);
//  newMaterial->setProperty("isTransparent", 1);
//  return newMaterial;
//}