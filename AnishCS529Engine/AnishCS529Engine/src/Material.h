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

class Material {
public:
  Material(std::shared_ptr<Shader> shader) : shader(shader) {}
  virtual ~Material() = default;

  void setShader(std::shared_ptr<Shader> shader);
  std::shared_ptr<Shader> getShader() const;

  void setProperty(const std::string& name, const float value);
  void setProperty(const std::string& name, const Vector3& value);
  void setProperty(const std::string& name, const Matrix4& value);

  virtual void apply() const;

private:
  std::shared_ptr<Shader> shader;
  std::unordered_map<std::string, std::variant<unsigned int, int, float, Vector3, Matrix4>> properties;



};

#endif // MATERIAL_H
