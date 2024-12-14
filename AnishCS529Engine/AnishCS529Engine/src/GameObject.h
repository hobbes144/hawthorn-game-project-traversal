/*!****************************************************************************
 * \file   GameObject.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-13-2024
 * \brief  Scene Object that represents a renderable object component
 * 
 *****************************************************************************/
#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#pragma once

#include "Node.h"
#include "Component.h"

class GameObject : public Node {
  GameObject(std::string& name) : Node(name ) {};

  void initialize();
  virtual void update(float deltaTime);
  void shutdown();

  void addComponent(std::shared_ptr<Component> _component);
  void removeComponent(Component* _component);

  template<typename T>
  T* findComponent();

  void markForDeletion();
  bool isMarkedForDeletion();
protected:
  std::vector<std::shared_ptr<Component>> components;

  bool enabled;
  bool markedForDeletion;
};

#endif // !SCENE_OBJECT_H
