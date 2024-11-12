#include "TrianglePrimitive.h"
#include "Shader.h"

TrianglePrimitive::TrianglePrimitive(const std::string name, 
    std::shared_ptr<GeometryBuffer>& geometryBuffer, 
    Renderer* renderer)
    : RenderableNode(name, nullptr, nullptr, renderer), color(Vector3(0.0f, 0.0f, 0.0f))
{
    mesh = std::make_shared<Mesh>(getName() + "_Mesh");
    mesh->setVertexData(geometryBuffer);
    createMaterial();
}

TrianglePrimitive::TrianglePrimitive(const std::string name, Renderer* renderer)
    : RenderableNode(name, nullptr, nullptr, renderer), color(Vector3(0.0f, 0.0f, 0.0f))
{
    createMesh();
    createMaterial();
}

void TrianglePrimitive::setColor(const Vector3& newColor)
{
    color = newColor;
    if(material)
        material->setProperty("Color", color);
}

Vector3 TrianglePrimitive::getColor() const
{
    return color;
}

void TrianglePrimitive::createMesh()
{
    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    std::vector<unsigned int> indices = { 0, 1, 2 };

    mesh = std::make_shared<Mesh>(getName() + "_Mesh");
    mesh->setVertexData({
        {GeometryBuffer::Attribute::Position, vertices, 3}
        }, 3 * sizeof(float), indices);
    
}

void TrianglePrimitive::createMaterial()
{
    auto shader = std::make_shared<Shader>("vertex_shader.glsl\nfragment_shader.glsl");
    material = std::make_shared<Material>(shader);
    material->setProperty("isTransparent", 0);
}