/*!****************************************************************************
 * \file   Input.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \author Mariojulio Osmin Zaldivar Alvarez (ex-Adjunct Professor)
 *   (zaldivaralvarez@gmail.com) (Advising and Base Code)
 * \par    **Course**
 *    CS529
 * \date   10-22-2024
 * \brief  Input system to handle window inputs
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#ifndef INPUT_H
#define INPUT_H

#pragma once

/* Used classes */
#include "GameWindow.h"
#include "InputKeys.h"

/*!****************************************************************************
 * \brief KeyState struct holds the state of each key.
 * 
 * ## Explanation:
 * 
 * The key's current state is handled by storing the previous and current key
 * state
 * 
 * The key can be:
 * - pressed (was released, now pressed)
 * - released (was pressed, now released)
 * - down (is pressed)
 * - up (is released)
 * - held (was pressed, still pressed)
 * 
 * These states help determine when the state has a shift but also if it's 
 * held.
 * 
 * The held keystate is managed by the Input class and isn't an OpenGL feature.
 * 
 * Refer to InputKeys.h for key reference.
 * 
 *****************************************************************************/
struct KeyState {
  bool currentState  = GLFW_RELEASE;
  bool prevState     = GLFW_RELEASE;
};


struct MouseState {
	//Mouse Position
	double xPos = 0.0f;
	double yPos = 0.0f;
	//Mouse Delta
	double deltaX = 0.0f;
	double deltaY = 0.0f;
	//Buttons
	bool leftMouseDown = false;
	bool rightMouseDown = false;
	bool middleMouseDown = false;
};

/*!****************************************************************************
 * \brief Input class that handles storing and updating key press states
 * 
 * ## Usage:
 * 
 * The Input class is needed to read and manage user inputs to the game.
 * 
 * ## Pre-initialization calls:
 * 
 * - setGameWindow(GameWindow* _gameWindow)
 * - setKeysToMonitor(std::vector<Key>& keysToMonitor)
 * 
 * ## General lifecycle of Input:
 * 
 * - Initialize GameWindow object.
 * - Initialize Input.
 * - Call update() to poll for input events (after GameWindow::update()).
 * - Call the isKey_ functions to check if the required inputs were pressed.
 * 
 * ## Notes:
 * 
 * initialize() and shutdown() are not necessary to call.
 * 
 * ## Future:
 * 
 * In the future, this will be expanded to also manage controller key states.
 * 
 *****************************************************************************/
class Input : public Component {

public:
  Input() = default;
  ~Input() = default;

  /*Input Frame*/
  void beginFrame();
  void endFrame();

  /* Component functions */
  void initialize();
  void update();
  void shutdown();

  /* Pre-initialization functions */
  Input* setGameWindow(GameWindow* _gameWindow);
  Input* setKeysToMonitor();
  Input* setKeysToMonitor(std::vector<Key>& keysToMonitor);

  void setupCallbacks();

  /* Utility functions */
  bool isKeyPressed(Key k);
  bool isKeyReleased(Key k);
  bool isKeyDown(Key k);
  bool isKeyUp(Key k);
  bool isKeyHeld(Key k);

  //Mouse Functions
  MouseState getMouseState() const { return mouseState; }
  void getMousePosition(double& x, double& y) const;
  void getMouseDelta(double& dx, double& dy) const;
  bool isMouseButtonDown(int button) const;
  bool isMouseButtonPressed(int button) const;
  bool isMouseButtonReleased(int button) const;
  void resetMouseDelta();

  void controlMouse(bool capture);

private:
  /** GameWindow object to read keys from */
  GameWindow* gameWindow;
  /** Map of key states for each registered key */
  std::unordered_map<Key, KeyState> keyStates;
  /** State of the Mouse */
  MouseState prevMouseState;
  MouseState mouseState;

  void registerKey(Key k);

  // Mouse Functions
  void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
  void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

};

#endif // INPUT_H
