#pragma once
#include "Node.h"
#include "Mesh.h"
#include "Transform.h"
#include "Renderer.h"
#include "Material.h"
#include <memory>

class RenderableNode : public Node {
public:
    RenderableNode(const std::string& name, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material,
        Renderer* render);
    virtual ~RenderableNode() = default;

    // Getters for components
    const Mesh*         getMesh()       const { return mesh.get(); }
    const Material*     getMaterial()   const { return material.get(); }   
    
    // Update function (overrides Node::update)
    void update(float deltaTime) override;

    // Drawing function (to be called by the rendering system)
    void draw(Matrix4& view, Matrix4& projection);

    // Enable/disable rendering
    void setVisible(bool visible) { isVisible = visible; }
    bool getVisible() const { return isVisible; }

private:
    Renderer* renderer;

protected:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    bool isVisible;
};