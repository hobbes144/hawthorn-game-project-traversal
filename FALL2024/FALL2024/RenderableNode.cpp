// RenderableNode.cpp
#include "RenderableNode.h"

RenderableNode::RenderableNode(const std::string& name, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material,
    Renderer* renderer)
    : Node(name), mesh(mesh), material(material), isVisible(true), renderer(renderer) {}


void RenderableNode::update(float deltaTime) {

    // Call the base class update (if there's any additional logic there)
    // Parent class has the logic to go through all children
    Node::update(deltaTime);
}

void RenderableNode::draw(Matrix4& view, Matrix4& projection) {
    if (!isVisible || !mesh || !material)
        return;

    // Use the pre-calculated world matrix
    //Matrix4 mvpMatrix = viewProjection * worldMatrix;

    // Set properties in the material ProjectionMatrix * ViewMatrix * ModelMatrix 
    material->setProperty("ModelMatrix", getTransformMatrix());
    material->setProperty("ProjectionMatrix", projection);
    material->setProperty("ViewMatrix", view);

    // Apply the material (this will set uniforms and bind textures)
    material->apply();

    // Bind the mesh's geometry buffer
    std::shared_ptr<GeometryBuffer> geomBuffer = mesh->getGeometryBuffer();
    if (!geomBuffer) return;
    geomBuffer->bind();

    // Draw the mesh
    if (mesh->hasAttribute(GeometryBuffer::Attribute::Position)) {
        if (geomBuffer->getIndexCount() > 0) {
            renderer->draw(geomBuffer->getIndexCount(), GL_TRIANGLES, true);
        }
        else {
            renderer->draw(geomBuffer->getVertexCount(), GL_TRIANGLES, false);
        }
    }

    // Unbind geometry buffer
    geomBuffer->unbind();

    // Draw all children
    for (auto& child : getChildren()) {
        if (auto renderableChild = std::dynamic_pointer_cast<RenderableNode>(child)) {
            renderableChild->draw(view, projection);
        }
    }
}