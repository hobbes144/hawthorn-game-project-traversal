/*!****************************************************************************
 * \file   ShaderManager.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-10-2025
 * \brief  Shader Manager class
 * 
 *****************************************************************************/
#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#pragma once

#include "Shader.h"

class ShaderManager {
public:
  static ShaderManager& getInstance() {
    static ShaderManager instance;
    return instance;
  }

  std::shared_ptr<Shader> loadFile(const std::string& filePath);

private:
  ShaderManager() = default;
  std::unordered_map<std::string, std::shared_ptr<Shader>> loadedFiles;
};

#endif // !SHADER_MANAGER_H
