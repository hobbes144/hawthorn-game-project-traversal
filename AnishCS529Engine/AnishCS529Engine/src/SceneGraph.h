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

    /* Todo: Implement this when reparent is implented in Node. */
    /*void reparent(SharedNode node) override {
      throw std::runtime_error("ERROR::SCENEGRAPHvoid::ROOTNODE::REPARENTNODE::FORBIDDEN");
    }*/

    Matrix4 getModelMatrix() const { return modelMatrix; }
    /* Todo: instead use a Transform object and take rotation, scale and
    position as input instead to modify Transform. */
    void setModelMatrix(const Matrix4& newModelMatrix) { 
      modelMatrix = newModelMatrix;
    }

    void update(float deltaTime) override {
      //worldTranslate = localTranslate;
      Node::update(deltaTime);
    }
  private:
    /* Todo: Create separate world and local transform objects */
    /*Transform localTransform;
    Transform worldTransform;*/
    Matrix4 modelMatrix;
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
  void draw(const Matrix4& view, const Matrix4& projection) const;

  void setRootModelMatrix(const Matrix4& newModelMatrix) {
    root->setModelMatrix(newModelMatrix);
  }
  Matrix4 getRootModelMatrix() {
    return root->getModelMatrix();
  }

};

#endif // SCENE_GRAPH_H
