#pragma once
#include <string>
#include <memory>
#include <glew.h>

class Texture {
public:
    enum class FilterMode { Nearest, Linear, MipmapNearest, MipmapLinear };
    enum class WrapMode { Repeat, MirroredRepeat, ClampToEdge, ClampToBorder };
    enum class Type { Texture2D, Texture3D, CubeMap };

    // Factory method
    static std::shared_ptr<Texture> create(const std::string& filepath, Type type = Type::Texture2D);

    ~Texture();

    // Prevent copying
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    // Allow moving
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void bind(unsigned int unit = 0) const;
    void unbind() const;

    GLuint getID() const { return textureID; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getChannels() const { return channels; }
    GLenum getFormat() const { return format; }
    Type getType() const { return type; }

    void setFilterMode(FilterMode mode);
    void setWrapMode(WrapMode mode);
    void generateMipmaps();

private:
    Texture(const std::string& filepath, Type type);
    void loadTexture(const std::string& filepath);
    void setupTextureParameters();

    GLuint textureID;
    int width, height, channels;
    GLenum format;
    Type type;
};