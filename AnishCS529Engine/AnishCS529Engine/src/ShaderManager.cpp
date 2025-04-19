/*!****************************************************************************
 * \file   ShaderManager.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    GAM541
 * \date   04-18-2025
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 *
 *****************************************************************************/
#include "precompiled.h"
#include "ShaderManager.h"

std::shared_ptr<Shader> ShaderManager::loadFile(const std::string& filePath)
{
  if (loadedFiles.contains(filePath))
    return loadedFiles[filePath];

  loadedFiles[filePath] = std::shared_ptr<Shader>(new Shader(filePath));
  return loadedFiles[filePath];
}
