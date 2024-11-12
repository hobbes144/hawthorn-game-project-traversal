#include "Texture.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::shared_ptr<Texture> Texture::create(const std::string& filepath, Type type) {
    return std::shared_ptr<Texture>(new Texture(filepath, type));
}

Texture::Texture(const std::string& filepath, Type type)
    : textureID(0), width(0), height(0), channels(0), format(GL_RGB), type(type) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    loadTexture(filepath);
    setupTextureParameters();
}

Texture::~Texture() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
}

Texture::Texture(Texture&& other) noexcept
    : textureID(other.textureID), width(other.width), height(other.height),
    channels(other.channels), format(other.format), type(other.type) {
    other.textureID = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
    if (this != &other) {
        if (textureID != 0) {
            glDeleteTextures(1, &textureID);
        }
        textureID = other.textureID;
        width = other.width;
        height = other.height;
        channels = other.channels;
        format = other.format;
        type = other.type;
        other.textureID = 0;
    }
    return *this;
}

void Texture::loadTexture(const std::string& filepath) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

    if (!data) {
        throw std::runtime_error("Failed to load texture: " + filepath);
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if (channels == 3)
        format = GL_RGB;
    else if (channels == 4)
        format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

void Texture::setupTextureParameters() {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setFilterMode(FilterMode mode) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    switch (mode) {
    case FilterMode::Nearest:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    case FilterMode::Linear:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    case FilterMode::MipmapNearest:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    case FilterMode::MipmapLinear:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setWrapMode(WrapMode mode) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    GLint glMode;
    switch (mode) {
    case WrapMode::Repeat:
        glMode = GL_REPEAT;
        break;
    case WrapMode::MirroredRepeat:
        glMode = GL_MIRRORED_REPEAT;
        break;
    case WrapMode::ClampToEdge:
        glMode = GL_CLAMP_TO_EDGE;
        break;
    case WrapMode::ClampToBorder:
        glMode = GL_CLAMP_TO_BORDER;
        break;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glMode);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::generateMipmaps() {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}