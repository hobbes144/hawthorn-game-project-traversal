#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Vector3.h"
#include "RenderableNode.h"
#include <memory>

class TrianglePrimitive : public RenderableNode{
public:
    TrianglePrimitive(const std::string name,
        std::shared_ptr<GeometryBuffer>& geometryBuffer,
        Renderer* renderer);
    TrianglePrimitive(const std::string name, Renderer* renderer);
    ~TrianglePrimitive() = default;

    void setColor(const Vector3& color);
    Vector3 getColor() const;

    auto getGeometryBuffer() { return mesh ? mesh->getGeometryBuffer() : nullptr; }

private:
    Vector3 color;

    void createMesh();
    void createMaterial();
};