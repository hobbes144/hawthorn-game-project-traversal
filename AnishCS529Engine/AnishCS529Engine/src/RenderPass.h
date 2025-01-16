/*!****************************************************************************
 * \file   RenderPass.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   01-15-2025
 * \brief  Render Pass class
 * 
 *****************************************************************************/
#ifndef RENDER_PASS_H
#define RENDER_PASS_H

#pragma once

#include <variant>
#include <optional>

#include "Matrix4.h"
#include "Shader.h"
#include "Vector3.h"
#include "Texture.h"

/*!****************************************************************************
 * \brief Render Pass class used to render using a shader
 * 
 * ## Usage:
 * 
 * This class is meant to be used to render using a shader. Each shading pass
 * for rendering should be handled using a RenderPass.
 * 
 * Typically after the shader and resources are set, this class should be
 * registered to the RenderGraph, which will handle rendering.
 * 
 * ## Pre-registration calls:
 * 
 * - setResource(const std::string& name, void* value)
 * 
 * If FBO functionality is needed,
 * - setFBO(std::shared_ptr<FBO> FBO)
 * 
 * ## Explanation:
 * 
 * The class provides an interface for the Shader class. It stores the required
 * resources to run the specific pass, and applies them when apply() is run.
 * 
 * FBO functionality is supported if needed, and is diabled by default unless
 * the setFBO() call is used.
 * 
 *****************************************************************************/
class RenderPass {
public:
  RenderPass(std::shared_ptr<Shader> _shader) : shader(_shader) {};
  virtual ~RenderPass() = default;

  void setShader(std::shared_ptr<Shader> _shader);
  std::shared_ptr<Shader> getShader() const;

  template<typename T>
  void setProperty(const std::string& name, const T& value) {
    properties[name] = value;
  }
  template<typename T>
  T getProperty(const std::string& name) {
    return properties[name];
  }

  //void setFBO(std::shared_ptr<FBO> FBO);
  //std::shared_ptr<FBO> getFBO() const;

  void setTexture(const std::string& name, std::shared_ptr<Texture> texture, unsigned int unit);

  virtual void apply() const;

protected:
  //std::optional<std::shared_ptr<FBO>> FBO;
  std::shared_ptr<Shader> shader;
  std::unordered_map<
    std::string,
    std::variant<unsigned int, int, float, Vector3, Matrix4>
  > properties;

  struct TextureInfo {
    std::shared_ptr<Texture> texture;
    unsigned int unit;
  };

  std::optional<std::unordered_map<std::string, TextureInfo>> textureData;

};

#endif // RENDER_PASS_H
