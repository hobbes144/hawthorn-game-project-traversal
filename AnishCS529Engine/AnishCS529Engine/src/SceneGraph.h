/*!****************************************************************************
 * \file   SceneGraph.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-15-2024
 * \brief  Scene Graph to control all nodes in the scene.
 * 
 *****************************************************************************/
#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#pragma once

#include "Node.h"
#include "RenderableNode.h"

class SceneGraph {
private:
  class RootNode : public Node {
  public:
    RootNode() : Node("Root") {}
    ~RootNode() override = default;

    void removeNode(SharedNode node) override {
      throw std::runtime_error("ERROR::SCENEGRAPH::ROOTNODE::REMOVENODE::FORBIDDEN");
    }

    void reparent(SharedNode node) override {
      throw std::runtime_error("ERROR::SCENEGRAPHvoid::ROOTNODE::REPARENTNODE::FORBIDDEN");
    }

    void update(float deltaTime) override {
      localTransform = localTransform;
      for (auto& child : children) {
        child->update(deltaTime);
      }
    }
  };

  std::shared_ptr<RootNode> root;

  void drawNode(const std::shared_ptr<Node>& node, 
    const Matrix4& view, const Matrix4& projection) const;

public:
  SceneGraph() : root(std::make_shared<RootNode>()) {}

  void addNode(std::shared_ptr<Node> node);
  void removeNode(std::shared_ptr<Node> node);

  std::shared_ptr<Node> findNode(unsigned int id);
  std::shared_ptr<Node> findNodeFast(unsigned int id);

  void update(float deltaTime);
  void updateNode(const std::shared_ptr<Node>& node, float deltaTime);
  void draw(const Matrix4& view, const Matrix4& projection) const;
  void printSceneTree();

  Vector3 getRootPosition() const { return root->getLocalPosition(); }
  Vector3 getRootRotation() const { return root->getLocalRotation(); }
  Vector3 getRootScaling() const { return root->getLocalScaling(); }

  void setRootPosition(const Vector3& position) { root->setLocalPosition(position); }
  void setRootRotation(const Vector3& rotation) { root->setLocalRotation(rotation); }
  void setRootScaling(const Vector3& scaling) { root->setLocalScaling(scaling); }

};

#endif // SCENE_GRAPH_H
