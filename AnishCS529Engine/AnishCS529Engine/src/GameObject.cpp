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


/*!****************************************************************************
 * \brief Enable the GameObject
 *
 *****************************************************************************/
void GameObject::enable() {
  enabled = true;
}

/*!****************************************************************************
 * \brief Disable the GameObject
 *
 *****************************************************************************/
void GameObject::disable() {
  enabled = false;
}

/*!****************************************************************************
 * \brief Is GameObject enabled
 *
 * \return \b bool true if GameObject enabled.
 *****************************************************************************/
bool GameObject::isEnabled() const {
  return enabled;
}

/*!****************************************************************************
 * \brief Mark component for deletion
 * 
 * ## Usage:
 * 
 * This function is intended to be used alongside a garbage collection system
 * that ensures that objects are cleaned up when there are resources available
 * to do so.
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
bool GameObject::isMarkedForDeletion() const {
  return markedForDeletion;
}

/*!****************************************************************************
 * \brief Initialize an object
 *
 * ## Usage:
 *
 * Ensure that all components are added and configured before running
 * initialize.
 *
 * ## Explanation:
 *
 * Calls Component::initialize() for each of the components added to the
 * GameObject.
 *
 *****************************************************************************/
void GameObject::initialize() {
  if (enabled) {
    for (auto component : components) {
      component->initialize();
    }
  }
}

/*!****************************************************************************
 * \brief Update the GameObject with all components
 *
 * ## Usage:
 *
 * Use in the main loop to run the Component::update(float deltaTime) function
 * for each of the components.
 *
 * ## Explanation:
 *
 * The update call is intended to execute all relevant time-based game
 * behaviour. Events are handled through the event system, and update calls may
 * invoke events.
 *
 * ## Note:
 *
 * Components are updated in the order they are added to the vector. If you
 * have any behaviour that is order dependent, ensure you have it correctly
 * ordered, or consider using a separate system to manage these components.
 *
 * \param deltaTime Time passed since last update.
 *****************************************************************************/
void GameObject::update(float deltaTime) {
  Node::update(deltaTime);

  if (enabled) {
    for (auto& component : components) {
      component->update(deltaTime);
    }
  }
}

/*!****************************************************************************
 * \brief Shutdown the GameObject along with all its components
 *
 * ## Usage:
 *
 * This is to be called at the end of the main loop, or whenever a GameObject
 * is no longer going to be used. Component::shutdown() will be called for all
 * components of the GameObject.
 *
 *****************************************************************************/
void GameObject::shutdown() {
  if (enabled) {
    for (auto component : components) {
      component->shutdown();
    }
  }
  components.clear();
}
