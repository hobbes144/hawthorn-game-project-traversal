//#pragma once
//
//#include <vector>
//#include <string>
//#include <iostream>
//
//class Node : public std::enable_shared_from_this<Node> {
//protected:
//  //aliases for code clarity
//  using ChildrenContainer = std::vector<std::shared_ptr<Node>>;
//  using SharedNode = std::shared_ptr<Node>;
//  
//  unsigned int      siblingNumber;
//  Node*             parent;
//  ChildrenContainer children;
//  std::string       name;
//
//  void updateSiblingNumbers(unsigned int startIndex);
//  static void printNodeRecursive(std::ostream& os, Node* node, int depth);
//
//  friend std::ostream& operator<<(std::ostream& os, Node& node);
//
//public:
//  Node(std::string name);
//  virtual ~Node() { std::cout << "Node " << name << " destroyed\n"; }
//
//  void              addChild(SharedNode node);
//  void              removeNode(SharedNode node);
//  void              reparent(SharedNode node);
//  SharedNode        findNode(SharedNode node);
//  SharedNode        fineNodeFast(SharedNode node);
//  virtual void      update(float deltaTime);
//
//  // Getter methods
//  Node*                   getParent()     const { return parent; }
//  const ChildrenContainer getChildren()   const { return children; }
//
//#ifdef DEBUG
//  std::string             getName()       const { return name; };
//#endif
//
//}
