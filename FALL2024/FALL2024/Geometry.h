#pragma once
#include "GeometryBuffer.h"
#include <memory>
#include <string>
#include <vector>

struct VertexData {
    GeometryBuffer::Attribute attribute;
    std::vector<float> data;
    int componentsPerVertex;
};

class Geometry {
public:
    virtual ~Geometry() = default;

    // Get the GeometryBuffer
    virtual std::shared_ptr<GeometryBuffer> getGeometryBuffer() const = 0;

    // Get the type of geometry
    virtual std::string getType() const = 0;

    // Clone the geometry
    virtual std::unique_ptr<Geometry> clone() const = 0;

protected:
    std::shared_ptr<GeometryBuffer> geometryBuffer;

    // Helper function to prepare attribute data for GeometryBuffer
    void prepareAttributeData(
        std::unordered_map
        <GeometryBuffer::Attribute, std::pair<std::vector<float>, GeometryBuffer::AttributeInfo>>& attributeMap,
        const std::vector<VertexData>& vertexData,
        const GLsizei stride) {
        for (const auto& vda : vertexData) {
            attributeMap[vda.attribute] = {
                vda.data,
                {vda.componentsPerVertex, GL_FLOAT, GL_FALSE, stride}
            };
        }
    }
};