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
bool Component::isEnabled() const {
  return enabled;
}

/*!****************************************************************************
 * \brief Set component parent
 * 
 * \param _parent Parent of the component
 *****************************************************************************/
void Component::setParent(std::shared_ptr<GameObject> _parent) {
  parent = _parent;
}

std::shared_ptr<GameObject> Component::getParent() const {
  return parent;
}
