#pragma once
#include <glew.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

class GeometryBuffer {
public:
    // We define in this class each attribute as a separate vector
    enum class Attribute {
        Position,
        Normal,
        TexCoord,
        Color,
        Tangent,
        Bitangent
    };

    // We also define a structure of the attribute data type, 
    // for flexibility when sending data to GPU
    struct AttributeInfo {
        GLint       size;
        GLenum      type;
        GLboolean   normalized;
        GLsizei     stride;
    };

    // Static factory method to create shared GeometryBuffer
    static std::shared_ptr<GeometryBuffer> create(
        const std::unordered_map<Attribute, std::pair<std::vector<float>, AttributeInfo>>& attributeData,
        const std::vector<unsigned int>& indices,
        const std::string& name);

    ~GeometryBuffer();

    // Prevent copying
    GeometryBuffer(const GeometryBuffer&) = delete;
    GeometryBuffer& operator=(const GeometryBuffer&) = delete;

    // Allow moving
    GeometryBuffer(GeometryBuffer&&) noexcept;
    GeometryBuffer& operator=(GeometryBuffer&&) noexcept;

    // Core functionality
    void bind() const;
    void unbind() const;

    // Update methods
    void updateVertexAttribute(Attribute attr, const std::vector<float>& newData);
    void updateIndices(const std::vector<unsigned int>& newIndices);

    // Getters
    GLsizei             getVertexCount() const { return vertexCount; }
    GLsizei             getIndexCount() const { return indexCount; }
    const std::string&  getName() const { return name; }

    // Utility methods
    bool    hasAttribute(Attribute attr) const;
    auto    getIndexData()  const { return indexData; }
    GLuint  getVAO()        const { return vao; }
    GLuint  getVBO()        const { return vbo; }
    GLuint  getEBO()        const { return ebo; }

private:
    GeometryBuffer(const std::string& name);

    void initializeBuffers( 
        const std::unordered_map<Attribute, std::pair<std::vector<float>, AttributeInfo>>& attributeData,
        const std::vector<unsigned int>& indices);
    void cleanupBuffers();

    GLuint  vao, vbo, ebo;
    GLsizei vertexCount;
    GLsizei indexCount;
    std::unordered_map<Attribute, GLuint> attributeOffsets; // To track when each attribute starts
    std::unordered_map<Attribute, AttributeInfo> attributeInfos;
    std::string name;  // For debugging and resource management
    std::vector<unsigned int> indexData;
};