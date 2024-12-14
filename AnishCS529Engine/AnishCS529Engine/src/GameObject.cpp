/*!****************************************************************************
 * \file   GameObject.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-13-2024
 * 
 *****************************************************************************/

#include "GameObject.h"

void GameObject::initialize() {
  if (enabled) {
    for (auto component : components) {
      component->initialize();
    }
  }
}

void GameObject::update(float deltaTime) {

  if (enabled) {
    for (auto& component : components) {
      component->update(deltaTime);
    }
  }

  Node::update(deltaTime);
}

void GameObject::shutdown() {
  if (enabled) {
    for (auto component : components) {
      component->shutdown();
    }
  }
}

void GameObject::addComponent(std::shared_ptr<Component> _component) {
  _component->setParent(this);
  components.push_back(_component);
}

template<typename T>
T* findComponent() {
  static_assert(
    std::is_base_of<Component, T>::value,
    "ERROR::GAMEOBJECT::FINDCOMPONENT::INVALIDTYPE");

  for (const auto& component : components) {
    T* result = dynamic_cast<T*>(component.get());
    if (result) {
      return result;
    }
  }
  
  return nullptr;
}

/*!****************************************************************************
 * \brief Mark component for deletion
 *
 *****************************************************************************/
void GameObject::markForDeletion() {
  markedForDeletion = true;
}

/*!****************************************************************************
 * \brief Is component marked for deletion
 *
 * \return \b bool true if marked for deletion.
 *****************************************************************************/
bool GameObject::isMarkedForDeletion() {
  return markedForDeletion;
}
