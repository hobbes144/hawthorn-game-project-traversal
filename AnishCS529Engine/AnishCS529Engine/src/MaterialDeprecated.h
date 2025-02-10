///*!****************************************************************************
// * \file   Material.h
// * \author Anish Murthy (anish.murthy.dev@gmail.com)
// * \par    **DigiPen Email**
// *    anish.murthy@digipen.edu
// * \par    **Course**
// *    CS529
// * \date   10-14-2024
// * \brief  Material class
// * 
// *****************************************************************************/
//#ifndef MATERIAL_H
//#define MATERIAL_H
//
//#pragma once
//
//#include <unordered_map>
//#include <variant>
//#include <optional>
//
//#include "Matrix4.h"
//#include "Shader.h"
//#include "Vector3.h"
//#include "Texture.h"
//
///*!****************************************************************************
// * \brief Class to manage Materials used by objects
// * 
// * This class handles creation of shaders and setting parameters for them.
// *****************************************************************************/
//class MaterialDeprecated {
//public:
//  MaterialDeprecated(std::shared_ptr<Shader> shader) : shader(shader) {}
//  virtual ~MaterialDeprecated() = default;
//
//  void setShader(std::shared_ptr<Shader> shader);
//  std::shared_ptr<Shader> getShader() const;
//
//  template<typename T>
//  void setProperty(const std::string& name, const T& value) {
//    properties[name] = value;
//  }
//
//  void setTexture(const std::string& name, std::shared_ptr<Texture> texture, unsigned int unit);
//
//  virtual void apply() const;
//
//protected:
//  std::shared_ptr<Shader> shader;
//  std::unordered_map<
//    std::string, 
//    std::variant<unsigned int, int, float, Vector3, Matrix4>
//  > properties;
//
//  struct TextureInfo {
//    std::shared_ptr<Texture> texture;
//    unsigned int unit;
//  };
//
//  std::optional<std::unordered_map<std::string, TextureInfo>> textureData;
//
//};
//
//std::shared_ptr<MaterialDeprecated> createSolidColorMaterial(const Vector3& color);
//std::shared_ptr<MaterialDeprecated> createTextureMaterial(const std::string& textureFile);
//
//#endif // MATERIAL_H
//
//// Challenge for you: Can you think of a way to templetize the setProperty() function?
//// What about the properties map? Instead of a variant, could you use a template parameter? In that case, how would you handle setting the uniforms?