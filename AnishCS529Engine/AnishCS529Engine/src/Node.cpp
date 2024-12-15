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
  child->siblingNumber = static_cast<unsigned int>(children.size()) - 1;
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

  return nullptr;
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
  auto foundNode = findNode(node->getID());
  // no node found, nothing to do
  if (!foundNode)
    return;

  // node found
  // 0. node will always have a parent (root is overrided)
  Node* parent = foundNode->getParent();

  // 1. erase the found node from parent's children vector and update
  // sibling numbers
  unsigned int removedIndex = foundNode->siblingNumber;
  // still have a reference shared in foundNode variable
  parent->children.erase(parent->children.begin() + removedIndex);
  parent->updateSiblingNumbers(removedIndex);

  // 2. foundNode has children, and now that we reset the children of parent,
  // let's just push back the new children
  for (auto& child : foundNode->getChildren()) parent->addChild(child);

  // 3. clear foundNode
  foundNode->children.clear();
  foundNode->parent = nullptr;
  foundNode->siblingNumber = 0;

  // foundNode will be automatically destroyed here since all references are
  // deleted.
}

/*!****************************************************************************
 * \brief Reparent a node to a new node
 * 
 * \param dstNode
 *****************************************************************************/
void Node::reparent(SharedNode dstNode) {
  //auto thisNode = shared_from_this(); // sasafe usage of 'this'

  Node* parent = getParent();
  // 1. erase the found node from parent's children vector and update sibling numbers
  unsigned int removedIndex = siblingNumber;
  parent->children.erase(parent->children.begin() + removedIndex); 
  // still have a reference shared in foundNode variable
  parent->updateSiblingNumbers(removedIndex);

  // 2. attach this to dstNode
  dstNode->addChild(shared_from_this());
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
    if (parent) {
      Matrix4 parentWorld = parent->getTransformMatrix();
      worldTransform.setPosition(parentWorld * localTransform.getPosition());
      worldTransform.setRotation(parent->worldTransform.getRotation() + localTransform.getRotation());
      worldTransform.setScaling(parent->worldTransform.getScaling() * localTransform.getScaling());
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
      localTransform.setScaling(worldTransform.getScaling() * parent->worldTransform.getScaling().reciprocal());
    }
    else {
      localTransform = worldTransform;
    }
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

void Node::setLocalScaling(const Vector3& scaling) {
  localTransform.setScaling(scaling);
  isLocalSpace = true;  // Ensure we're in local space after this operation
}

/*!****************************************************************************
 * \brief Debugging printing
 * 
 * \param os Stream to output to.
 * \param node Node to start with.
 * \param depth Depth to which nodes are printed.
 *****************************************************************************/
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

/*!****************************************************************************
 * \brief Debugging printing
 * 
 * \param os Stream to output to.
 * \param node Node to start with.
 * \return \b std::ostream& The output stream.
 *****************************************************************************/
std::ostream& operator<<(std::ostream& os, Node& node) {
  Node::printNodeRecursive(os, &node, 0);
  return os;
}
