#include "Material.h"
/*!****************************************************************************
 * \file   Material.inl
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-10-2025
 * 
 *****************************************************************************/
#ifndef MATERIAL_INL
#define MATERIAL_INL

#pragma once

template<typename T>
std::shared_ptr<T> Material::getMaterial(
    const std::string& name) {
  static_assert(std::is_base_of<Material, T>::value,
    "Material must be derived from Material class");

  if (basicMaterials.contains(name))
    return std::dynamic_pointer_cast<T>(basicMaterials[name]);

  auto material = std::make_shared<T>();
  basicMaterials[name] = material;
  return material;
}

#endif // !MATERIAL_INL
