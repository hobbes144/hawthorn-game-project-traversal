/*!****************************************************************************
 * \file   Input.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-22-2024
 * \brief  Input system to handle window inputs
 * 
 *****************************************************************************/
#ifndef INPUT_H
#define INPUT_H

#pragma once

#include "GameWindow.h"
#include "InputKeys.h"

/*!****************************************************************************
 * \brief KeyState struct holds the state of each key.
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
 *****************************************************************************/
struct KeyState {
  bool currentState  = GLFW_RELEASE;
  bool prevState     = GLFW_RELEASE;
};


/*!****************************************************************************
 * \brief Input class that handles storing and updating key press states
 * 
 * In the future, this will be expanded to also manage controller key states.
 * 
 *****************************************************************************/
class Input {

public:
  Input(GameWindow& window, std::vector<Key>& keysToMonitor);
  Input(GameWindow& window);

  void update();

  bool isKeyPressed(Key k);
  bool isKeyReleased(Key k);
  bool isKeyDown(Key k);
  bool isKeyUp(Key k);
  bool isKeyHeld(Key k);


private:
  /** GameWindow object to read keys from */
  GameWindow& window;
  /** Map of key states for each registered key */
  std::unordered_map<Key, KeyState> keyStates;

  void registerKey(Key k);

};

#endif // INPUT_H
