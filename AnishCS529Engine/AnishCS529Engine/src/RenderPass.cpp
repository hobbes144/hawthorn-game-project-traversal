#include "RenderPass.h"

std::shared_ptr<Shader> RenderPass::addShader(std::string shaderFile)
{
  shader = ShaderManager::getInstance().loadFile(shaderFile);
  return shader;
}

std::shared_ptr<Shader> RenderPass::addShader(std::shared_ptr<Shader> _shader)
{
  shader = _shader;
  return shader;
}

std::shared_ptr<Shader> RenderPass::getShader() const
{
  return shader;
}

void RenderPass::setTexture(const std::string& name, TextureManager::TextureID textureID, unsigned int unit)
{
  if (!textureData) {
    textureData = std::unordered_map<std::string, TextureManager::TextureID>();
  }
  (*textureData)[name] = textureID;
}

void RenderPass::draw(std::shared_ptr<Mesh> mesh, GLenum mode,
  const PropertyMap& materialProperties,
  const LightStack& lightStack) const
{
  if (materialProperties.contains("isDebug")) return;
  shader->use();
  applyProperties(properties, materialProperties);

  unsigned int lightIndex = 0;
  for (const auto& light : lightStack) {
    light->applyToShader(shader, lightIndex);
  }

  mesh->draw(mode);
}

void RenderPass::applyProperties(
  const PropertyMap& passProperties,
  const PropertyMap& materialProperties) const
{
  /* Todo: this is VERY inefficient. We don't need to be using variant
  * and doing TWO loops over the same variant data is really bad for
  * performance. Please fix this when you get time.
  * 
  * Also a nightmare to manage. I forgot to add Vector2 to one and
  * took half an hour to realise.
  */
  std::vector<std::pair<std::string, TextureManager::TextureID>> texturesToBind;

  for (const auto& [name, value] : passProperties) {
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

  for (const auto& [name, value] : materialProperties) {
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

  unsigned int textureUnit = 0;

  for (const auto& [name, textureID] : texturesToBind) {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(TEXTURE_2D, textureID.id);

    shader->setInt(name, textureUnit);
    ++textureUnit;
  }
}

/*!****************************************************************************
 * \brief Enable the Pass
 *
 *****************************************************************************/
void RenderPass::enable() {
  enabled = true;
}

/*!****************************************************************************
 * \brief Disable the Pass
 *
 *****************************************************************************/
void RenderPass::disable() {
  enabled = false;
}

/*!****************************************************************************
 * \brief Is Pass enabled
 *
 * \return \b bool true if Pass enabled.
 *****************************************************************************/
bool RenderPass::isEnabled() const {
  return enabled;
}
