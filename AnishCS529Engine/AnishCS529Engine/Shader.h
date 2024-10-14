#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>


class Shader {
public:
  Shader(std::string& shaderFilePaths);
  ~Shader();

  unsigned int getId() { return programID; };
  void use();
  
private:
  std::unordered_map<GLenum, GLuint> shaderIDs;
  GLuint programID;

  GLenum readShaderType(std::string path);
  std::string readShaderFile(std::string path);
  GLuint loadShader(GLenum type, const GLchar* source);
  void deleteShader(GLuint id);
  void linkShaders();
  void initializeBasicUniforms();

  std::string toLowerCase(const std::string& str);

};
