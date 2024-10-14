#pragma once

#include "Matrix4.h"
#include "Vector3.h"

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
  Shader(const std::string& shaderFilePaths);
  ~Shader();

  void use();

  void setUInt(const std::string& name, unsigned int value) const;
  void setInt(const std::string& name, int value) const;
  void set2Int(const std::string& name, int v0, int v1) const;
  void setFloat(const std::string& name, float value) const;
  void setVec2(const std::string& name, float x, float y) const;
  void setVec3(const std::string& name, const Vector3& value) const;
  void setVec4(const std::string& name, float x, float y, float z, float w) const;
  void setMat4(const std::string& name, const Matrix4& value) const;

  unsigned int getId() { return programID; };
  
private:
  std::unordered_map<GLenum, GLuint> shaderIDs;
  mutable std::unordered_map<std::string, GLint> uniformLocationCache; // Todo: Why is this mutable?
  GLuint programID;

  GLenum readShaderType(std::string path);
  std::string readShaderFile(std::string path);
  GLuint loadShader(GLenum type, const GLchar* source);
  void deleteShader(GLuint id);
  void linkShaders();
  GLint getUniformLocation(const std::string& name) const;

  std::string toLowerCase(const std::string& str);

};
