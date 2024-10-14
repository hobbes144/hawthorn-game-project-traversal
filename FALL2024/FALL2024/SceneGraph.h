#pragma once

#include "Node.h"
#include "Transform.h"
#include <memory>
#include <stdexcept>

class SceneGraph {
private:
    // Internal class representing the root node of the scene graph
    class RootNode : public Node {
    public:
        RootNode() : Node("Root") {}
        ~RootNode() override = default;

        // Prevent removal of the root node
        void removeNode(SharedNode node) override {
            throw std::runtime_error("Cannot remove the root node");
        }

        // Prevent reparenting of the root node
        void reparent(SharedNode node) override {
            throw std::runtime_error("Cannot reparent the root node");
        }

        // Update function
        void update(float deltaTime) override {
            worldTransform = localTransform;

            // Update all children
            Node::update(deltaTime);
        }

    };

    std::shared_ptr<RootNode> root;  // Root node of the scene graph
    
    void drawNode(const std::shared_ptr<Node>& node, const Matrix4& view, const Matrix4& projection) const;

public:
    SceneGraph();

    // Returns the root node of the scene graph (const version)
    const std::shared_ptr<Node>& getRoot() const;

    // Adds a new node to the scene graph
    void addNode(std::shared_ptr<Node> node);

    // Removes a node from the scene graph
    void removeNode(std::shared_ptr<Node> node);

    // Finds a node in the scene graph
    std::shared_ptr<Node> findNode(std::shared_ptr<Node> node);

    // Updates the scene graph with delta time
    void update(float deltaTime);

    // Draw the entire scene graph if and only if Node is an instance of RenderableNode
    void draw(const Matrix4& view, const Matrix4& projection) const;

    

    // inline functions to get data from root, if needed
    // Root node transform getters
    Vector3 getRootPosition() const { return root->getLocalPosition(); }
    Vector3 getRootRotation() const { return root->getLocalRotation(); }
    Vector3 getRootScale() const { return root->getLocalScale(); }

    //Root node transform setters
    void setRootPosition(const Vector3& position) { root->setLocalPosition(position); }
    void setRootRotation(const Vector3& rotation) { root->setLocalRotation(rotation); }
    void setRootScale(const Vector3& scale) { root->setLocalScale(scale); }

    // Get the root node's world matrix
    //const Matrix4& getRootWorldMatrix() const { return root->getWorldMatrix(); }
};
