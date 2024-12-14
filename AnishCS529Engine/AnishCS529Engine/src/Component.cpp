#include "Component.h"

/*!****************************************************************************
 * \brief Enable the component
 * 
 *****************************************************************************/
void Component::enable() {
  enabled = true;
}

/*!****************************************************************************
 * \brief Disable the component
 * 
 *****************************************************************************/
void Component::disable() {
  enabled = false;
}

/*!****************************************************************************
 * \brief Is component enabled
 * 
 * \return \b bool true if component enabled.
 *****************************************************************************/
bool Component::isEnabled() {
  return enabled;
}

/*!****************************************************************************
 * \brief Set component parent
 * 
 * \param _parent Parent of the component
 *****************************************************************************/
void Component::setParent(GameObject* _parent) {
  parent = _parent;
}

GameObject* Component::getParent() {
  return parent;
}

/*!****************************************************************************
 * \brief Mark component for deletion
 * 
 *****************************************************************************/
void Component::markForDeletion() {
  markedForDeletion = true;
}

/*!****************************************************************************
 * \brief Is component marked for deletion
 * 
 * \return \b bool true if marked for deletion.
 *****************************************************************************/
bool Component::isMarkedForDeletion() {
  return markedForDeletion;
}
