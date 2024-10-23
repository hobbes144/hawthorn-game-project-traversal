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

#include "Matrix4.h"
#include "Shader.h"
#include "Vector3.h"

/*!****************************************************************************
 * \brief Class to manage Materials used by objects
 * 
 * This class handles creation of shaders and setting parameters for them.
 *****************************************************************************/
class Material {
public:
  Material(std::shared_ptr<Shader> shader) : shader(shader) {}
  virtual ~Material() = default;

  void setShader(std::shared_ptr<Shader> shader);
  std::shared_ptr<Shader> getShader() const;

  template<typename T>
  void setProperty(const std::string& name, const T& value) {
    properties[name] = value;
  }

  virtual void apply() const;

private:
  std::shared_ptr<Shader> shader;
  std::unordered_map<
    std::string, 
    std::variant<unsigned int, int, float, Vector3, Matrix4>
  > properties;

};

#endif // MATERIAL_H

// Challenge for you: Can you think of a way to templetize the setProperty() function?
// What about the properties map? Instead of a variant, could you use a template parameter? In that case, how would you handle setting the uniforms?