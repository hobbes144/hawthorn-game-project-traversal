#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <optional>
#include <vector>
#include "Vector3.h"
#include "Matrix4.h"

#include "Shader.h"
#include "Texture.h"

class Material {
public:
    Material(std::shared_ptr<Shader> shader);
    virtual ~Material() = default;

    // Shader management
    void setShader(std::shared_ptr<Shader> shader);
    std::shared_ptr<Shader> getShader() const;

    // Property setters
    void setProperty(const std::string& name, unsigned int value);
    void setProperty(const std::string& name, int value);
    void setProperty(const std::string& name, float value);
    void setProperty(const std::string& name, const Vector3& value);
    void setProperty(const std::string& name, const Matrix4& value);

    // Texture setter
    void setTexture(const std::string& name, std::shared_ptr<Texture> texture, unsigned int unit);

    // Apply the material (to be called before rendering an object)
    virtual void apply() const;

private:
    std::shared_ptr<Shader> shader;
    std::unordered_map<std::string, std::variant<unsigned int, int, float, Vector3, Matrix4 >> properties;

    // Texture info data structure to handle texture unit mapped to a texture
    struct TextureInfo {
        std::shared_ptr<Texture> texture;
        unsigned int unit;
    };
    
    // Optional texture data
    // No memory is allocated if we decide for a texture-less material / renderable node
    std::optional<std::unordered_map<std::string, TextureInfo>> textureData;
};