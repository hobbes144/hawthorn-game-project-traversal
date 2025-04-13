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
#include "precompiled.h"
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

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

    Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
    if (!input) return;

    bool pressed = (action == GLFW_PRESS);

    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:   input->mouseState.leftMouseDown = pressed; break;
    case GLFW_MOUSE_BUTTON_RIGHT:  input->mouseState.rightMouseDown = pressed; break;
    case GLFW_MOUSE_BUTTON_MIDDLE: input->mouseState.middleMouseDown = pressed; break;
    }

}

void Input::MouseMotionCallback(GLFWwindow* window, double xpos, double ypos) {

    Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
    if (!input) return;

    input->mouseState.deltaX = xpos - input->mouseState.xPos;
    input->mouseState.deltaY = ypos - input->mouseState.yPos;

    input->mouseState.xPos = xpos;
    input->mouseState.yPos = ypos;

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

  return this;
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

  return this;
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

  return this;
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

void Input::beginFrame()
{
}

void Input::endFrame()
{
    prevMouseState = mouseState;
}

/*!****************************************************************************
 * \brief Input initialize is a dummy function
 * 
 *****************************************************************************/
void Input::initialize() {
    controlMouse(true);

    glfwSetWindowUserPointer(window->getNativeWindow(), this);
    glfwSetMouseButtonCallback(window->getNativeWindow(), MouseButtonCallback);
    glfwSetCursorPosCallback(window->getNativeWindow(), MouseMotionCallback);
}

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

  prevMouseState = mouseState;

}

/*!****************************************************************************
 * \brief Input shutdown is a dummy function
 * 
 *****************************************************************************/
void Input::shutdown() {}

void Input::getMousePosition(double& x, double& y) const {
    x = mouseState.xPos;
    y = mouseState.yPos;
}

void Input::getMouseDelta(double& dx, double& dy) const {
    dx = mouseState.deltaX;
    dy = mouseState.deltaY;
}

bool Input::isMouseButtonDown(int button) const {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT: return mouseState.leftMouseDown;
    case GLFW_MOUSE_BUTTON_RIGHT: return mouseState.rightMouseDown;
    case GLFW_MOUSE_BUTTON_MIDDLE: return mouseState.middleMouseDown;
    default: return false;
    }
}

bool Input::isMouseButtonPressed(int button) const
{
    bool result = false;
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        result = mouseState.leftMouseDown && !prevMouseState.leftMouseDown;
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        result = mouseState.rightMouseDown && !prevMouseState.rightMouseDown;
        break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        result = mouseState.middleMouseDown && !prevMouseState.middleMouseDown;
        break;
    default:
        return false;
    }
    if (result) {
        std::cout << "True";
    }
    return result;
}

bool Input::isMouseButtonReleased(int button) const
{
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        return !mouseState.leftMouseDown && prevMouseState.leftMouseDown;
    case GLFW_MOUSE_BUTTON_RIGHT:
        return !mouseState.rightMouseDown && prevMouseState.rightMouseDown;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        return !mouseState.middleMouseDown && prevMouseState.middleMouseDown;
    default:
        return false;
    }
}

void Input::resetMouseDelta() {
    mouseState.deltaX = 0.0f;
    mouseState.deltaY = 0.0f;
}

void Input::controlMouse(bool capture)
{
    if (capture) {
        glfwSetInputMode(window->getNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else {
        glfwSetInputMode(window->getNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}
