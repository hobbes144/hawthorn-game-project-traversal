#include "RenderPass.h"

void RenderPass::setShader(std::shared_ptr<Shader> _shader)
{
  shader = _shader;
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

void RenderPass::apply(const PropertyMap& materialProperties,
  const LightStack& lightStack) const
{
  shader->use();
  applyProperties(properties, materialProperties);

  unsigned int lightIndex = 0;
  for (const auto& light : lightStack) {
    light->applyToShader(shader, lightIndex);
  }
}

void RenderPass::applyProperties(
  const PropertyMap& passProperties,
  const PropertyMap& materialProperties) const
{
  /* Todo: this is VERY inefficient. We don't need to be using variant
  * and doing TWO loops over the same variant data is really bad for
  * performance. Please fix this when you get time.
  */
  std::vector<std::pair<std::string, TextureManager::TextureID>> texturesToBind;

  for (const auto& propertySet : { passProperties, materialProperties }) {
    for (const auto& [name, value] : propertySet) {
      if (auto item = std::get_if<unsigned int>(&value)) {
        shader->setUInt(name, *item);
      }
      if (auto item = std::get_if<int>(&value)) {
        shader->setInt(name, *item);
      }
      if (auto item = std::get_if<float>(&value)) {
        shader->setFloat(name, *item);
      }
      if (auto item = std::get_if<Vector3>(&value)) {
        shader->setVec3(name, *item);
      }
      if (auto item = std::get_if<Matrix4>(&value)) {
        shader->setMat4(name, *item);
      }
      if (auto item = std::get_if<TextureManager::TextureID>(&value)) {
        texturesToBind.emplace_back(name, *item);
      }
    }
  }

  unsigned int textureUnit = 0;

  for (const auto& [name, textureID] : texturesToBind) {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(TEXTURE_2D, textureID.id);

    shader->setUInt(name, textureUnit);
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
