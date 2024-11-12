#include "Material.h"
#include <stdexcept>
#include <iostream>

Material::Material(std::shared_ptr<Shader> shader) : shader(shader) {}

void Material::setShader(std::shared_ptr<Shader> newShader) {
    shader = newShader;
}

std::shared_ptr<Shader> Material::getShader() const {
    return shader;
}

void Material::setProperty(const std::string& name, unsigned int value) {
    properties[name] = value;
}

void Material::setProperty(const std::string& name, int value) {
    properties[name] = value;
}

void Material::setProperty(const std::string& name, float value) {
    properties[name] = value;
}

void Material::setProperty(const std::string& name, const Vector3& value) {
    properties[name] = value;
}

void Material::setProperty(const std::string& name, const Matrix4& value) {
    properties[name] = value;
}

void Material::setTexture(const std::string& name, std::shared_ptr<Texture> texture, unsigned int unit){
    if (!textureData) {
        textureData = std::unordered_map<std::string, TextureInfo>();
    }
    (*textureData)[name] = { texture, unit };
}

void Material::apply() const {
    // Making sure shader exists
    if (!shader) {
        throw std::runtime_error("Shader not set for material");
    }
    shader->use();

    // Generic uniforms
    for (const auto& [name, value] : properties) {
        std::visit([this, &name](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, unsigned int>) {
                shader->setUInt(name, arg);
            }
            else if constexpr (std::is_same_v<T, int>) {
                shader->setInt(name, arg);
            }
            else if constexpr (std::is_same_v<T, float>) {
                shader->setFloat(name, arg);
            }
            else if constexpr (std::is_same_v<T, Vector3>) {
                shader->setVec3(name, arg);
            }
            else if constexpr (std::is_same_v<T, Matrix4>) {
                shader->setMat4(name, arg);
            }
            }, value);
    }

    // Texture samplers
    if (textureData) {
        for (const auto& [name, texInfo] : *textureData) {
            if (texInfo.texture) {
                texInfo.texture->bind();
                shader->setInt(name, texInfo.unit);
            }
            else {
                // You might not want to use textures in your shader 
                // and/or your vertex data doesn't support it
                std::cerr << "Warning: Null texture for uniform " << name << std::endl;
            }
        }
    }
    
}

