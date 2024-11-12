#include "Node.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>

Node::Node(std::string name) : parent(nullptr), name(name), siblingNumber(0), isLocalSpace(true) {}

void Node::addChild(Node::SharedNode child) {
    children.push_back(child);
    child->siblingNumber = children.size() - 1;
    child->parent = this;
}

Node::SharedNode Node::findNode(SharedNode node) {
    if (this == node.get()) {
        return shared_from_this();
    }
    for (auto& child : children) {
        auto found = child->findNode(node);
        if (found) {
            return found;
        }
    }
    return nullptr;
}

Node::SharedNode Node::findNodeFast(SharedNode node) {
    std::stack<Node*> nodeStack;
    nodeStack.push(this);

    while (!nodeStack.empty()) {
        Node* currentNode = nodeStack.top();
        nodeStack.pop();

        if (currentNode == node.get()) {
            return currentNode->shared_from_this();
        }

        for (auto it = currentNode->children.rbegin(); it != currentNode->children.rend(); ++it) {
            nodeStack.push(it->get());
        }
    }

    return nullptr;
}

void Node::removeNode(Node::SharedNode node)
{
    auto foundNode = findNode(node);

    // no node found, nothing to do
    if (!foundNode)
        return;

    // node found
    // 0. node will always have a parent (root should be present in the scene, always!)
    Node* parent = foundNode->getParent();

    // 1. erase the found node from parent's children vector and update sibling numbers
    unsigned int removedIndex = foundNode->siblingNumber;
    parent->children.erase(parent->children.begin() + removedIndex); // still have a reference shared in foundNode variable
    parent->updateSiblingNumbers(removedIndex);

    // 2. foundNode has children, and now that we reset the children of parent, let's just push back the new children
    for (auto& child : foundNode->getChildren())
        parent->addChild(child);

    // 3. clear foundNode
    foundNode->children.clear();
    foundNode->parent = nullptr;
    foundNode->siblingNumber = 0;

    // foundNode will be automatically destroyed here.
}

void Node::reparent(SharedNode dstNode){
    //auto thisNode = shared_from_this(); // sasafe usage of 'this'

    Node* parent = getParent();
    // 1. erase the found node from parent's children vector and update sibling numbers
    unsigned int removedIndex = siblingNumber;
    parent->children.erase(parent->children.begin() + removedIndex); // still have a reference shared in foundNode variable
    parent->updateSiblingNumbers(removedIndex);

    // 2. attach this to dstNode
    dstNode->addChild(shared_from_this());
}

void Node::update(float deltaTime) {

    /*if (parent) {
        localTransform.setPosition(parent->getLocalPosition() + localTransform.getPosition());
        localTransform.setRotation(parent->getLocalRotation() + localTransform.getRotation());
        localTransform.setScale(parent->getLocalScale() * localTransform.getScale());

        worldTransform.setPosition(parent->getTransformMatrix() * localTransform.getPosition());
        worldTransform.setRotation(parent->worldTransform.getRotation() + localTransform.getRotation());
        worldTransform.setScale(parent->worldTransform.getScale() * localTransform.getScale());

    }*/
    




    if (isLocalSpace) {
        if (parent) {
            Matrix4 parentWorld = parent->getTransformMatrix();
            worldTransform.setPosition(parentWorld * localTransform.getPosition());
            worldTransform.setRotation(parent->worldTransform.getRotation() + localTransform.getRotation());
            worldTransform.setScale(parent->worldTransform.getScale() * localTransform.getScale());
        }
        else {
            worldTransform = localTransform;
        }
    }
    else {
        if (parent) {
            Matrix4 parentWorldInv = parent->worldTransform.getInverseLocalMatrix();
            localTransform.setPosition(parentWorldInv * worldTransform.getPosition());
            localTransform.setRotation(worldTransform.getRotation() - parent->worldTransform.getRotation());
            localTransform.setScale(worldTransform.getScale() * parent->worldTransform.getScale().reciprocal());
        }
        else {
            localTransform = worldTransform;
        }
    }


    // Update all children
    for (auto& child : children) {
        child->update(deltaTime);
    }
}


void Node::worldToLocalSpace() {
    isLocalSpace = true;
}

void Node::localToWorldSpace() {
    isLocalSpace = false;
}

void Node::setLocalPosition(const Vector3& position) {
    localTransform.setPosition(position);
    isLocalSpace = true;  // Ensure we're in local space after this operation
}

void Node::setLocalRotation(const Vector3& rotation) {
    localTransform.setRotation(rotation);
    isLocalSpace = true;  // Ensure we're in local space after this operation
}

void Node::setLocalScale(const Vector3& scale) {
    localTransform.setScale(scale);
    isLocalSpace = true;  // Ensure we're in local space after this operation
}

Vector3 Node::getLocalPosition() const {
    return localTransform.getPosition();
}

Vector3 Node::getLocalRotation() const {
    return localTransform.getRotation();
}

Vector3 Node::getLocalScale() const {
    return localTransform.getScale();
}

Matrix4 Node::getTransformMatrix() {
    return isLocalSpace ? localTransform.getLocalMatrix() : worldTransform.getLocalMatrix();
}

void Node::updateSiblingNumbers(unsigned int startIndex) {
    for (unsigned int i = startIndex; i < children.size(); ++i) {
        children[i]->siblingNumber = i;
    }
}

void Node::printNodeRecursive(std::ostream& os, Node* node, int depth) {
    if (!node) return;

    // Print indentation
    for (int i = 0; i < depth; ++i) {
        os << "  ";
    }

    // Print current node
    os << "+-" << node->getName() << std::endl;

    // Print children
    for (const auto& child : node->getChildren()) {
        printNodeRecursive(os, child.get(), depth + 1);
    }
}

// Overload the << operator for Node
std::ostream& operator<<(std::ostream& os, Node& node) {
    Node::printNodeRecursive(os, &node, 0);
    return os;
}