#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "Transform.h"

class Node : public std::enable_shared_from_this<Node> {

protected:
    // aliases for code clarity
    using ChildrenContainer = std::vector<std::shared_ptr<Node>>;
    using SharedNode        = std::shared_ptr<Node>;

    unsigned int        siblingNumber;
    Node*               parent;
    ChildrenContainer   children;
    std::string         name;

    // Transform related properties of a node
    Transform localTransform;
    Transform worldTransform;
    Matrix4 localMatrix;
    bool isLocalSpace;

    void        updateSiblingNumbers(unsigned int startIndex);
    static void printNodeRecursive(std::ostream& os, Node* node, int depth);

    friend std::ostream& operator<<(std::ostream& os, Node& node);

public:
    Node(std::string name);
    virtual ~Node() { std::cout << "Node " << name << " destroyed\n"; }//= default;

    virtual void    removeNode(SharedNode node);
    virtual void    reparent(SharedNode node);
    virtual void    update(float deltaTime);
    void            addChild(SharedNode node);
    SharedNode      findNode(SharedNode node);
    SharedNode      findNodeFast(SharedNode node);

    // Getter methods
    Node*                    getParent()    const { return parent; }
    const ChildrenContainer& getChildren()  const { return children; }
    std::string              getName()      const { return name; };

    // Node space data
    void setLocalPosition(const Vector3& position);
    void setLocalRotation(const Vector3& rotation);
    void setLocalScale(const Vector3& scale);

    Vector3 getLocalPosition() const;
    Vector3 getLocalRotation() const;
    Vector3 getLocalScale() const;
    
    

    // Get the Matrix of whatever this node is
    void worldToLocalSpace();
    void localToWorldSpace();
    Matrix4 getTransformMatrix();

    
};