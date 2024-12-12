/*!****************************************************************************
 * \file   Input.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-22-2024
 * 
 *****************************************************************************/
#include"Input.h"

/* Private functions */

/*!****************************************************************************
 * \brief Register a key to be in the list of keys being polled
 *
 * ## Explanation:
 * 
 * Keys must be registered before they can be used. This registers supported
 * keys so they are polled in the update() call.
 * 
 * InputKeys.h contains the list of all supported keys.
 * 
 * \param k Key code as defined in InputKeys.h
 *****************************************************************************/
void Input::registerKey(Key k) {
  if (keyStates.find(k) == keyStates.end())
    keyStates[k] = KeyState();
}



/* Public functions */

/*!****************************************************************************
 * \brief Seter GameWindow object that is being read from
 * 
 * ## Usage:
 * 
 * This function sets up the game window from which inputs should be read.
 * 
 * ## Explanation:
 * 
 * Inputs are read per window. The inputs are read every time the window calls
 * a Window::update() call, when it polls for events.
 * 
 * \param _window
 * \return \b Input* this
 *****************************************************************************/
Input* Input::setGameWindow(GameWindow* _window) {
  window = _window;
}

/*!****************************************************************************
 * \brief Setter for the keys to be monitored
 * 
 * ## Usage:
 * 
 * Sets all supported keys to be polled.
 * 
 * ## Explanation:
 * 
 * This is to be used only during testing, as checking every key can introduce
 * significant overhead.
 * 
 * For general use, make use of the function:
 * setKeysToMonitor(std::vector<Key>& keysToMonitor)
 * 
 * \return \b Input* this
 *****************************************************************************/
Input* Input::setKeysToMonitor() {
  for (Key& k : allKeys) {
    registerKey(k);
  }
}

/*!****************************************************************************
 * \brief Setter for the keys to be monitored
 *
 * ## Usage:
 *
 * Sets the list of provided keys to be polled.
 * 
 * ### Input example:
 * 
 * `std::vector<Key> keysToBeMonitored = { KEY_W, KEY_A, KEY_S, KEY_D };`
 * `input->setKeysToMonitor(keysToBeMonitored);`
 *
 * ## Explanation:
 *
 * This sets up the list of keys that will be polled on each update() call.
 * 
 * Ensure that only the needed keys are set.
 *
 * \param keysToMonitor vector of Key codes to be monitored.
 * \return \b Input* this
 *****************************************************************************/
Input* Input::setKeysToMonitor(std::vector<Key>& keysToMonitor) {
  for (Key& k : keysToMonitor) {
    registerKey(k);
  }
  std::vector<Key> monitored = { KEY_SPACE };
}

/*!****************************************************************************
 * \brief If key was pressed while previously not pressed
 * 
 * \param k Key to be checked.
 * \return \b bool True if pressed in this cycle.
 *****************************************************************************/
bool Input::isKeyPressed(Key k) {
  if (keyStates[k].currentState == GLFW_PRESS &&
    keyStates[k].prevState == GLFW_RELEASE)
    return true;
  return false;
}

/*!****************************************************************************
 * \brief If key was released while previously pressed
 * 
 * \param k Key to be checked.
 * \return \b bool True if released in this cycle.
 *****************************************************************************/
bool Input::isKeyReleased(Key k) {
  if (keyStates[k].currentState == GLFW_RELEASE &&
    keyStates[k].prevState == GLFW_PRESS)
    return true;
  return false;
}

/*!****************************************************************************
 * \brief If key is in pressed state
 *
 * \param k Key to be checked.
 * \return \b bool True if pressed.
 *****************************************************************************/
bool Input::isKeyDown(Key k) {
  if (keyStates[k].currentState == GLFW_PRESS)
    return true;
  return false;
}

/*!****************************************************************************
 * \brief If key is in released state
 *
 * \param k Key to be checked.
 * \return \b bool True if released.
 *****************************************************************************/
bool Input::isKeyUp(Key k) {
  if (keyStates[k].currentState == GLFW_RELEASE)
    return true;
  return false;
}

/*!****************************************************************************
 * \brief If key is held in pressed state
 *
 * \param k Key to be checked.
 * \return \b bool True if held.
 *****************************************************************************/
bool Input::isKeyHeld(Key k) {
  if (keyStates[k].currentState == GLFW_PRESS &&
    keyStates[k].prevState == GLFW_PRESS)
    return true;
  return false;
}

/*!****************************************************************************
 * \brief Input initialize is a dummy function
 * 
 *****************************************************************************/
void Input::initialize() {}

/*!****************************************************************************
 * \brief Update loop that polls the window for the state of each key
 *
 * ## Usage:
 *
 * Updates the previous state and stores the current state of the key.
 *
 * This should only be used after the GameWindow::update() call, as it relies
 * on the game window having polled for events.
 *
 *****************************************************************************/
void Input::update() {
  // Alternate way of doing this:
  // for (
  //  std::unordered_map<int, KeyState>::iterator it = keyStates.begin(); 
  //  it != keyStates.end(); 
  //  it++)
  for (auto& [k, state] : keyStates) {
    int newState = glfwGetKey(window->getNativeWindow(), k);
    state.prevState = state.currentState;
    state.currentState = newState;
  }
}

/*!****************************************************************************
 * \brief Input shutdown is a dummy function
 * 
 *****************************************************************************/
void Input::shutdown() {}
