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

/*!****************************************************************************
 * \brief Constructor to enable specific keys
 * 
 * \param window GameWindow object to poll for key states.
 * \param keysToMonitor Vector of all keys to be enabled.
 *****************************************************************************/
Input::Input(GameWindow& window, std::vector<Key>& keysToMonitor) : 
  window(window), keyStates{} {
  for (Key& k : keysToMonitor) {
    registerKey(k);
  }
}

/*!****************************************************************************
 * \brief Constructor to enable all supported keys
 * 
 * \param window GameWindow object to poll for key states.
 *****************************************************************************/
Input::Input(GameWindow& window) : window(window), keyStates{} {
  for (Key& k : allKeys) {
    registerKey(k);
  }
}

/*!****************************************************************************
 * \brief Register a key to be in the list of keys being polled
 * 
 * \param k Key code as defined in InputKeys.h
 *****************************************************************************/
void Input::registerKey(Key k) {
  if (keyStates.find(k) == keyStates.end())
    keyStates[k] = KeyState();
}

/*!****************************************************************************
 * \brief Update loop that polls the window for the state of each key
 * 
 * Updates the previous state and stores the current state of the key.
 * 
 *****************************************************************************/
void Input::update() {
  // Alternate way of doing this:
  // for (
  //  std::unordered_map<int, KeyState>::iterator it = keyStates.begin(); 
  //  it != keyStates.end(); 
  //  it++)
  for (auto& [k, state] : keyStates) {
    int newState = glfwGetKey(window.getNativeWindow(), k);
    state.prevState = state.currentState;
    state.currentState = newState;
  }
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
