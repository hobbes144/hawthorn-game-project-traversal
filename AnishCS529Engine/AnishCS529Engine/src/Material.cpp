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

void Material::setProperty(const std::string& name, const float value) {
  properties[name] = value;
}

void Material::setProperty(const std::string& name, const Vector3& value) {
  properties[name] = value;
}

void Material::setProperty(const std::string& name, const Matrix4& value) {
  properties[name] = value;
}

void Material::apply() const {
  shader->use();

  for (const auto& [name, value] : properties) {
    /* visit takes a function as the first argument and the value to be sent
    to it in the second. */
    std::visit(
      [this, &name](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
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
}
