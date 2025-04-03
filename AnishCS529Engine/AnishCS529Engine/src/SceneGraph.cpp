/*!****************************************************************************
 * \file   SceneGraph.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-15-2024
 * 
 *****************************************************************************/
#include "precompiled.h"
#include "SceneGraph.h"


void SceneGraph::addNode(std::shared_ptr<Node> node) {
  if (!node) 
    throw std::invalid_argument(
      "ERROR::SCENEGRAPH::ADDNODE::INVALID::NULL");

  root->addChild(node);
}

void SceneGraph::removeNode(std::shared_ptr<Node> node) {
  if (!node) 
    throw std::invalid_argument(
      "ERROR::SCENEGRAPH::REMOVENODE::INVALID::NULL");
  if (node == root)
    throw std::invalid_argument(
      "ERROR::SCENEGRAPH::REMOVENODE::INVALID::ROOT");
  root->removeNode(node);
}

std::shared_ptr<Node> SceneGraph::findNode(unsigned int id) {
  return root->findNode(id);
}

std::shared_ptr<Node> SceneGraph::findNodeFast(unsigned int id) {
  return root->findNode(id);
}

void SceneGraph::update(float deltaTime) {
  updateNode(root, deltaTime);
}

void SceneGraph::updateNode(const std::shared_ptr<Node>& node, float deltaTime) {
  nodeUpdateStack.push(node);
  std::shared_ptr<Node> currNode;
  while (nodeUpdateStack.size() > 0) {
    currNode = nodeUpdateStack.top();
    nodeUpdateStack.pop();
    currNode->update(deltaTime);
    for (auto child : currNode->getChildren()) {
      nodeUpdateStack.push(child);
    }
  }
  
}

void SceneGraph::drawNode(const std::shared_ptr<Node>& node,
  const Matrix4& view, const Matrix4& projection) const {
  auto renderableNode = std::dynamic_pointer_cast<RenderableNode>(node);
  if (renderableNode != nullptr) {
    renderableNode->draw(view, projection);
  }

  for (const auto& child : node->getChildren()) {
    drawNode(child, view, projection);
  }
}

void SceneGraph::draw(const Matrix4& view, const Matrix4& projection) const {
  drawNode(root, view, projection);
}

void SceneGraph::printSceneTree() {
  std::cout << *root << std::endl;
}

void SceneGraph::clear()
{
    for (auto child : root->getChildren()) {
        nodeUpdateStack.push(child);
    }
    std::shared_ptr<Node> currNode;
    while (nodeUpdateStack.size() > 0) {
        currNode = nodeUpdateStack.top();
        nodeUpdateStack.pop();
        for (auto child : currNode->getChildren()) {
            nodeUpdateStack.push(child);
        }
        currNode->deleteNode();
    }

    root->removeChildren();

}