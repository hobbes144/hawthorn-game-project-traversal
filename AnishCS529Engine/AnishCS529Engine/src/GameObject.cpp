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
#include "precompiled.h"

#include "GameObject.h"


/*!****************************************************************************
 * \brief Enable the GameObject
 * 
 * ## Usage:
 * 
 * This is to be used to "spawn" in an object that is already loaded in memory.
 * To reduce object init calls, ensure objects that aren't immediately needed
 * are initialized at the start of scene but disabled until in use.
 * 
 * ## Explanation:
 * 
 * This enables update calls for the GameObject, ensuring that all enabled
 * Component objects are run. If further control is needed, Component also
 * provides a Component::enable() call.
 *
 * \return \b std::shared_ptr<GameObject> Self shared pointer to allow chaining.
 *****************************************************************************/
std::shared_ptr<GameObject> GameObject::enable() {
  enabled = true;

  return std::static_pointer_cast<GameObject>(shared_from_this());
}

/*!****************************************************************************
 * \brief Disable the GameObject
 * 
 * ## Usage:
 * 
 * This is used to disable or "Kill" a game object. This will ensure that the
 * object is no longer processed even though it is still in memory.
 * 
 * ## Explanation:
 * 
 * This disables update calls for the GameObject, ensuring that all Component
 * objects are not run. If further control is needed, Component also provides a
 * Component::disable() call.
 *
 * \return \b std::shared_ptr<GameObject> Self shared pointer to allow chaining.
 *****************************************************************************/
std::shared_ptr<GameObject> GameObject::disable() {
  enabled = false;

  return std::static_pointer_cast<GameObject>(shared_from_this());
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
 * \return \b std::shared_ptr<GameObject> Self shared pointer to allow chaining.
 *****************************************************************************/
std::shared_ptr<GameObject> GameObject::markForDeletion() {
  markedForDeletion = true;

  return std::static_pointer_cast<GameObject>(shared_from_this());
}

/*!****************************************************************************
 * \brief Is component marked for deletion
 *
 * \return \b bool true if marked for deletion.
 *****************************************************************************/
bool GameObject::isMarkedForDeletion() const {
  return markedForDeletion;
}

void GameObject::updateComponents(float deltaTime)
{
  if (enabled) {
    for (auto& component : components) {
      component->update(deltaTime);
    }
  }
}

void GameObject::draw(std::shared_ptr<Shader> shader, uint32_t renderMask) {
  if (enabled && renderableComponent && 
    renderableComponent->getRenderMask() & renderMask )
    renderableComponent->draw(shader);
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

GameObject::~GameObject() {
  shutdown();
}
