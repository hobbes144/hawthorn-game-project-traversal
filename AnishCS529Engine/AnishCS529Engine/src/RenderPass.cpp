#include "RenderPass.h"

void RenderPass::setShader(std::shared_ptr<Shader> _shader)
{
  shader = _shader;
}

std::shared_ptr<Shader> RenderPass::getShader() const
{
  return shader;
}

void RenderPass::setTexture(const std::string& name, std::shared_ptr<Texture> texture, unsigned int unit)
{
  if (!textureData) {
    textureData = std::unordered_map<std::string, TextureInfo>();
  }
  (*textureData)[name] = { texture, unit };
}

void RenderPass::apply(const PropertyMap& tempProperties) const
{
  shader->use();

  applyProperties(properties);
  applyProperties(tempProperties);
  
  // Texture samplers
  if (textureData) {
    for (const auto& [name, texInfo] : *textureData) {
      if (texInfo.texture) {
        texInfo.texture->bind();
        shader->setInt(name, texInfo.unit);
      }
      else {
        std::cerr << "Warning: Null texture for uniform " << name << std::endl;
      }
    }
  }
}

void RenderPass::applyProperties(PropertyMap _properties) const
{
  for (const auto& [name, value] : _properties) {
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
        else if constexpr (std::is_same_v<T, TextureManager::TextureID>) {
          shader->setMat4(name, arg);
        }
      },
      value
    );
  }
}
