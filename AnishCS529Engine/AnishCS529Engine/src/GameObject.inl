/*!****************************************************************************
 * \file   GameObject.inl
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-14-2024
 * \brief
 *
 *****************************************************************************/
#ifndef GAME_OBJECT_INL
#define GAME_OBJECT_INL

#pragma once

//#include "GameObject.h"

 /*!****************************************************************************
  * \brief Add a component
  *
  * ## Usage:
  *
  * Game behaviour and properties are handled through components. This function
  * adds components to the GameObject.
  *
  * ## Explanation:
  *
  * Components that can be added include Render components (requiring Mesh and
  * Material components) and PhysicsBody components.
  *
  * ## Note:
  *
  * Adding duplicates of a Component type leads to undefined behaviour.
  *
  *****************************************************************************/
template<typename T>
std::shared_ptr<T> GameObject::addComponent() {
  auto component = std::make_shared<T>();
  component->setParent(shared_from_this());
  components.push_back(component);
  return component;
}

/*!****************************************************************************
 * \brief Remove a component
 *
 * ## Usage:
 *
 * This is to be used when a GameObject no longer needs a specific component.
 * Note that this is a heavy call so it is to be avoided as much as possible.
 * Prefer to use events to disable components.
 *
 * \param component Component to be removed.
 *****************************************************************************/
template<typename T>
void GameObject::removeComponent() {
  std::shared_ptr<T> found = nullptr;
  auto it = std::remove_if(
    components.begin(),
    components.end(),
    [&](const std::shared_ptr<Component>& c) {
      found = std::dynamic_pointer_cast<T>(c);
      return found != nullptr;
    });
  if (it != components.end()) {
    found->shutdown();
    components.erase(it);
  }
}

/*!****************************************************************************
 * \brief Find a component and return a pointer to it
 *
 * ## Usage:
 *
 * This can be used to get a specific component added to the GameObject.
 *
 * \return \b <Component derived class>* Component being searched for.
 *****************************************************************************/
template<typename T>
std::shared_ptr<T> GameObject::findComponent() {
  std::shared_ptr<T> found = nullptr;
  auto it = std::find_if(
    components.begin(),
    components.end(),
    [&](const std::shared_ptr<Component>& c) {
      found = std::dynamic_pointer_cast<T>(c);
      return found != nullptr;
    });

  return found;
}

#endif
