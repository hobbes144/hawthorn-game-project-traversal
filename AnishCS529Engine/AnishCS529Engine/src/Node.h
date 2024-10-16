/*!****************************************************************************
 * \file   Node.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-14-2024
 * \brief  Node class used for the Scene Graph
 * 
 *****************************************************************************/
#ifndef NODE_H
#define NODE_H

#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "Matrix4.h"
#include "Transform.h"

class Node : public std::enable_shared_from_this<Node> {
protected:
  using ChildrenContainer = std::vector<std::shared_ptr<Node>>;
  using SharedNode = std::shared_ptr<Node>;

  /* Static Next ID counter to ensure every node gets a unique ID. */
  static unsigned int nextID;

  unsigned int id;
  std::string name;
  Node* parent;
  unsigned int siblingNumber;
  ChildrenContainer children;

  /* Todo: Find a way to kick these down to the RenderableNode. */
  Transform localTransform;
  Transform worldTransform;
  Matrix4 modelMatrix;
  bool isLocalSpace;

  void updateSiblingNumbers(unsigned int removedIndex);

public:
  Node(std::string name);
  virtual ~Node() { std::cout << "Node " << name << " destroyed\n"; }//= default;

  virtual void removeNode(SharedNode node);
  /* Todo: implement reparent */
  // virtual void reparent(SharedNode node);
  virtual void update(float deltaTime);
  void worldToLocalSpace();
  void localToWorldSpace();
  void addChild(SharedNode node);
  SharedNode findNode(unsigned int id);
  SharedNode findNodeFast(unsigned int id);

  unsigned int getID() const { return id; }
  std::string getName() const { return name; }
  Node* getParent() const { return parent; }
  const ChildrenContainer& getChildren() const { return children; }

  Matrix4 getTransformMatrix() const { 
    return isLocalSpace ?
      localTransform.getLocalMatrix() : 
      worldTransform.getLocalMatrix();
  }
  Transform getLocalTransform() const { return localTransform; }
  Transform getWorldTransform() const { return worldTransform; }

  Vector3 getLocalPosition() const { return localTransform.getPosition(); }
  Vector3 getLocalRotation() const { return localTransform.getRotation(); }
  Vector3 getLocalScaling() const { return localTransform.getScaling(); }

  void setLocalPosition(const Vector3& position);
  void setLocalRotation(const Vector3& rotation);
  void setLocalScaling(const Vector3& scaling);

};

#endif // NODE_H
