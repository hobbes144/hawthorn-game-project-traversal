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

void Material::setShader(std::shared_ptr<Shader> newShader) {
  shader = newShader;
}

std::shared_ptr<Shader> Material::getShader() const {
  return shader;
}

void Material::setTexture(const std::string& name, std::shared_ptr<Texture> texture, unsigned int unit) {
  if (!textureData) {
    textureData = std::unordered_map<std::string, TextureInfo>();
  }
  (*textureData)[name] = { texture, unit };
}

void Material::apply() const {
  shader->use();

  for (const auto& [name, value] : properties) {
    /* visit takes a function as the first argument and the value to be sent
    to it in the second. */
    std::visit(
      [this, &name](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, unsigned int>) {
          shader->setUInt(name, arg);
        }
        else if constexpr (std::is_same_v<T, int>) {
          shader->setInt(name, arg);
        }
        if constexpr (std::is_same_v<T, float>) {
          shader->setFloat(name, arg);
        }
        else if constexpr (std::is_same_v<T, Vector3>) {
          shader->setVec3(name, arg);
        }
        else if constexpr (std::is_same_v<T, Matrix4>) {
          shader->setMat4(name, arg);
        }
      },
      value
    );
  }
  // Texture samplers
  if (textureData) {
    for (const auto& [name, texInfo] : *textureData) {
      if (texInfo.texture) {
        texInfo.texture->bind();
        shader->setInt(name, texInfo.unit);
      }
      else {
        // You might not want to use textures in your shader 
        // and/or your vertex data doesn't support it
        std::cerr << "Warning: Null texture for uniform " << name << std::endl;
      }
    }
  }
}

/*!****************************************************************************
 * \brief Factory to create a solid color render material
 * 
 * \param color Color to be rendered
 * \return \b std::shared_ptr<Material> Material created
 *****************************************************************************/
std::shared_ptr<Material> createSolidColorMaterial(const Vector3& color)
{
  auto newShader = std::make_shared<Shader>("shaders/factory_vertex_shader.vert.glsl\nshaders/factory_frag_shader.frag.glsl");
  auto newMaterial = std::make_shared<Material>(newShader);
  newMaterial->setProperty("color", color);
  newMaterial->setProperty("useTexture", 0);
  newMaterial->setProperty("isTransparent", 1);
  return newMaterial;
}

std::shared_ptr<Material> createTextureMaterial(const std::string& textureFile)
{
  auto newShader = std::make_shared<Shader>("shaders/factory_vertex_shader.vert.glsl\nshaders/factory_frag_shader.frag.glsl");
  auto newMaterial = std::make_shared<Material>(newShader);
  std::shared_ptr<Texture> texture = Texture::create(textureFile);
  newMaterial->setTexture("mainTexture", texture, 0);
  newMaterial->setProperty("useTexture", 1);
  newMaterial->setProperty("isTransparent", 1);
  return std::shared_ptr<Material>();
}
