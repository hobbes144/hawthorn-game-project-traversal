#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Vector3.h"
#include "Matrix4.h"
#include <glew.h>

class Shader {
public:
    Shader(const std::string& shaderPaths);
    ~Shader();

    void use() const;
    void unuse() const;

    void setUInt(const std::string& name, unsigned int value) const;
    void setInt(const std::string& name, int value) const;
    void set2Int(const std::string& name, int v0, int v1) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, const Vector3& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setMat4(const std::string& name, const Matrix4& value) const;

    unsigned int getID() const { return programID; }

private:
    unsigned int programID;
    mutable std::unordered_map<std::string, int> uniformLocationCache;
    std::unordered_map<GLenum, unsigned int> shaderIDs;

    unsigned int loadShader(const std::string& shaderCode, GLenum shaderType);
    void linkShaders();
    int getUniformLocation(const std::string& name) const;
    GLenum getShaderType(const std::string& filePath);
    std::string readShaderFile(const std::string& filePath);
    std::string toLowercase(const std::string& str);
};