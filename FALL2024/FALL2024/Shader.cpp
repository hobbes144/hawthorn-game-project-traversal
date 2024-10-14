#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

Shader::Shader(const std::string& shaderPaths) {
    std::istringstream pathsStream(shaderPaths);
    std::string shaderPath;

    while (std::getline(pathsStream, shaderPath)) {
        std::string shaderCode = readShaderFile(shaderPath);
        GLenum shaderType = getShaderType(shaderPath);

        if (shaderType != GL_INVALID_ENUM) {
            unsigned int shaderID = loadShader(shaderCode, shaderType);
            shaderIDs[shaderType] = shaderID;
        }
        else {
            std::cerr << "Unrecognized shader type for file: " << shaderPath << std::endl;
        }
    }

    linkShaders();
}

Shader::~Shader() {
    glDeleteProgram(programID);
}

void Shader::use() const {
    glUseProgram(programID);
}

void Shader::unuse() const {
    glUseProgram(0);
}

void Shader::setUInt(const std::string& name, unsigned int value) const {
    glUniform1ui(getUniformLocation(name), value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::set2Int(const std::string& name, int v0, int v1) const {
    glUniform2i(getUniformLocation(name), v0, v1);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setVec2(const std::string& name, float x, float y) const {
    glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setVec3(const std::string& name, const Vector3& value) const {
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setMat4(const std::string& name, const Matrix4& value) const {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value.getData());
}


unsigned int Shader::loadShader(const std::string& shaderCode, GLenum shaderType) {
    unsigned int shaderID = glCreateShader(shaderType);
    const char* code = shaderCode.c_str();
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << "Shader compilation error: " << infoLog << std::endl;
    }

    return shaderID;
}

void Shader::linkShaders() {
    programID = glCreateProgram();

    for (const auto& [type, id] : shaderIDs) {
        glAttachShader(programID, id);
    }

    glLinkProgram(programID);

    int success;
    char infoLog[512];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "Shader program linking error: " << infoLog << std::endl;
    }

    for (const auto& [type, id] : shaderIDs) {
        glDeleteShader(id);
    }
}

int Shader::getUniformLocation(const std::string& name) const {
    auto it = uniformLocationCache.find(name);
    if (it != uniformLocationCache.end()) {
        return it->second;
    }

    int location = glGetUniformLocation(programID, name.c_str());
    uniformLocationCache[name] = location;

    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' doesn't exist!" << std::endl;
    }

    return location;
}

GLenum Shader::getShaderType(const std::string& filePath) {
    std::string lowercasePath = toLowercase(filePath);
    if (lowercasePath.find("vertex") != std::string::npos) return GL_VERTEX_SHADER;
    if (lowercasePath.find("fragment") != std::string::npos) return GL_FRAGMENT_SHADER;
    if (lowercasePath.find("geometry") != std::string::npos) return GL_GEOMETRY_SHADER;
    if (lowercasePath.find("compute") != std::string::npos) return GL_COMPUTE_SHADER;
    return GL_INVALID_ENUM;
}

std::string Shader::readShaderFile(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}

std::string Shader::toLowercase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}