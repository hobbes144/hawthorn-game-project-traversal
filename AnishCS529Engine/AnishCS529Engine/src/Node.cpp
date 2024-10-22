/*!****************************************************************************
 * \file   Node.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-14-2024
 * 
 *****************************************************************************/

#include "Node.h"

/* Initializing static Next ID counter. */
unsigned int Node::nextID = 0;

/*!****************************************************************************
 * \brief Node Constructor
 * 
 * \param name Name of the node.
 *****************************************************************************/
Node::Node(std::string name) : 
  id(nextID++), name(name), parent(nullptr), siblingNumber(0), isLocalSpace(true) {}

/*!****************************************************************************
 * \brief Add a passed node as a child to the current node
 * 
 * \param child Node to be added to children.
 *****************************************************************************/
void Node::addChild(SharedNode child) {
  children.push_back(child);
  child->siblingNumber = children.size() - 1;
  child->parent = this;
}

/*!****************************************************************************
 * \brief Find a node by passing the node id to be found
 * 
 * \param id ID of the node to be found.
 * \return \b Node::SharedNode pointer to the found node.
 *****************************************************************************/
Node::SharedNode Node::findNode(unsigned int id) {
  if (this->getID() == id) {
    return shared_from_this();
  }
  for (auto& child : children) {
    auto found = child->findNode(id);
    if (found) return found;
  }
  return nullptr;
}

/*!****************************************************************************
 * \brief Find a node by passing the node id to be found, but fast
 *
 * \param id ID of the node to be found.
 * \return \b Node::SharedNode pointer to the found node.
 *****************************************************************************/
Node::SharedNode Node::findNodeFast(unsigned int id) {
  std::stack<Node*> nodeStack;
  nodeStack.push(this);

  while (!nodeStack.empty()) {
    Node* currentNode = nodeStack.top();
    nodeStack.pop();

    if (currentNode->getID() == id) return currentNode->shared_from_this();

    for (
      auto it = currentNode->children.rbegin(); 
      it != currentNode->children.rend(); 
      it++) {
      nodeStack.push(it->get());
    }

  }
}

/*!****************************************************************************
 * \brief Update sibling numbers of the children when one child is removed
 * 
 * Will change the index of all proceeding children to the approriate index.
 * 
 * \param removedIndex index of the child that was removed.
 *****************************************************************************/
void Node::updateSiblingNumbers(unsigned int removedIndex) {
  for (unsigned int i = removedIndex; i < children.size(); i++) {
    children[i]->siblingNumber = i;
  }
}

/*!****************************************************************************
 * \brief Remove a node from the tree
 * 
 * Note: removeNode cannot be called on root of tree.
 * This will delete the node and reparent all children to the parent of the
 * node being deleted.
 * 
 * \param node
 *****************************************************************************/
void Node::removeNode(SharedNode node) {
  Node* parent = node->getParent();
  unsigned int removedIndex = node->siblingNumber;

  parent->children.erase(parent->children.begin() + removedIndex);
  parent->updateSiblingNumbers(removedIndex);

  for (auto& child : node->getChildren()) parent->addChild(child);

  node->children.clear();
  node->parent = nullptr;
  node->siblingNumber = 0;
}

/*!****************************************************************************
 * \brief Main update function
 * 
 * Todo: Add Transform object instead of local modelMatrix and implement world
 * transforms modifying local transfroms.
 * 
 * \param deltaTime
 *****************************************************************************/
void Node::update(float deltaTime) {
  /* Todo: add other update logic here? */
  if (!parent) throw std::runtime_error("ERROR::NODE::UPDATE::NOPARENT");

  if (isLocalSpace) {
    /* Todo: Move this to Renderable node again and use static cast. */
    worldTransform.setPosition(parent->worldTransform.getPosition() + localTransform.getPosition());
    worldTransform.setRotation(parent->worldTransform.getRotation() + 
                               localTransform.getRotation());
    worldTransform.setScaling(parent->worldTransform.getScaling() * localTransform.getScaling());
  }
  else {
    localTransform.setPosition(
      worldTransform.getPosition() - parent->worldTransform.getPosition());
    localTransform.setRotation(
      worldTransform.getRotation() - parent->worldTransform.getRotation());
    localTransform.setScaling(
      worldTransform.getScaling() * 
      parent->worldTransform.getScaling().reciprocal());
  }


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
}

void Node::setLocalRotation(const Vector3& rotation) {
  localTransform.setRotation(rotation);
}

void Node::setLocalScaling(const Vector3& scaling) {
  localTransform.setScaling(scaling);
}
