#pragma once
#include "RenderableNode.h"

class RectanglePrimitive : public RenderableNode {
public:
    RectanglePrimitive(const std::string name,
        std::shared_ptr<GeometryBuffer>& geometryBuffer,
        Renderer* renderer);
    RectanglePrimitive(const std::string name, Renderer* renderer);
    ~RectanglePrimitive() = default;

    auto getGeometryBuffer() { return mesh ? mesh->getGeometryBuffer() : nullptr; }

private:

    void createMesh();
    void createMaterial();
};