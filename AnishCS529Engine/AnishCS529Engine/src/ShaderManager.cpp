#include "ShaderManager.h"

std::shared_ptr<Shader> ShaderManager::loadFile(const std::string& filePath)
{
  if (loadedFiles.contains(filePath))
    return loadedFiles[filePath];

  loadedFiles[filePath] = std::shared_ptr<Shader>(new Shader(filePath));
  return loadedFiles[filePath];
}
