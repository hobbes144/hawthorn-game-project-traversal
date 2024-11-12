#include "SceneGraph.h"
#include "RenderableNode.h"

// Constructor initializes the root node
SceneGraph::SceneGraph() : root(std::make_shared<RootNode>()) {}

// Returns the root node of the scene graph
const std::shared_ptr<Node>& SceneGraph::getRoot() const {
    return root;
}

// Adds a node to the scene graph
void SceneGraph::addNode(std::shared_ptr<Node> node) {
    if (!node) {
        throw std::invalid_argument("Cannot add null node to scene graph");
    }
    root->addChild(node);
}

// Removes a node from the scene graph
void SceneGraph::removeNode(std::shared_ptr<Node> node) {
    if (!node) {
        throw std::invalid_argument("Cannot remove null node from scene graph");
    }
    if (node == root) {
        throw std::runtime_error("Cannot remove the root node");
    }
    root->removeNode(node);
}

// Finds a node in the scene graph
std::shared_ptr<Node> SceneGraph::findNode(std::shared_ptr<Node> node) {
    return root->findNode(node);
}

// Updates the scene graph by propagating delta time to the root node
void SceneGraph::update(float deltaTime) {
    root->update(deltaTime);
}

void SceneGraph::draw(const Matrix4& view, const Matrix4& projection) const{
    drawNode(root, view, projection);
}

void SceneGraph::drawNode(const std::shared_ptr<Node>& node, const Matrix4& view, const Matrix4& projection) const{
    // Try to cast to RenderableNode
    auto renderableNode = dynamic_cast<RenderableNode*>(node.get());
    if (renderableNode != nullptr) {
        renderableNode->draw(const_cast<Matrix4&>(view), const_cast<Matrix4&>(projection));
    }

    // Recursively draw children
    for (const auto& child : node->getChildren()) {
        drawNode(child, view, projection);
    }
}