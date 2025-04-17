/*!****************************************************************************
 * \file   GameWindow.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-05-2024
 * \brief  File containing GameWindow Object and associated logic
 *
 *****************************************************************************/
#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#pragma once

/* OpenGL imports */
#include <glad/glad.h>

#ifndef ENGINE_GLFW_H
#define ENGINE_GLFW_H
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#endif // ENGINE_GLFW_H

/* Base class */
#include "Component.h"

/* Standard libraries */
#include <string>
#include <iostream>
#include <functional>

/* Forward declaration of class Renderer for friend */
class Renderer;
class Input;

/*!****************************************************************************
 * \brief Class that sets up the GLFW window and associated
 * logic
 *
 * ## Usage:
 *
 * The Game Window is the window where all game related functions run. It is
 * where render calls are drawn, and where inputs are read from.
 *
 * ## Pre-initialization calls:
 * 
 * - setTitle(std::string _title)
 * - setWidth(int _width)
 * - setHeight(int _height)
 *
 * ## General lifecycle of a GameWindow:
 *
 * - Init GameWindow object.
 * - Run game loop logic
 * - Call update() to poll events for the next loop iteration.
 * - On exiting the game loop, run shutdown() to destroy the window.
 *
 *****************************************************************************/
class GameWindow : public Component
{
  /* Friend classes */
  friend class Renderer;
  friend class Input;

public:
  /* Constructor */
  GameWindow() = default;
  ~GameWindow() = default;

  /* Component functions */
  void initialize();
  void update();
  void shutdown();

  /* Pre-initialization functions */
  GameWindow* setTitle(std::string _title);
  GameWindow* setWidth(int _width);
  GameWindow* setHeight(int _height);

  /* Post-initialization functions */
  GameWindow* setVsync(bool flag);

  /* Utility functions */
  int getWidth();
  int getHeight();
  float getAspectRatio();
  bool isFullscreen = false;
  bool getShouldClose() const;
  void setShouldClose() const;
  GLFWwindow* getNativeWindow() const;
  GameWindow* setInitialFullscreen(bool flag);
  GameWindow* setFullscreen(bool flag);

  // See note under resizeCallback2 variable. This needs to be removed.
  void setResizeCallback2(
      std::function<void(GLFWwindow*, int, int)> callback2);

private:
  /** Width of the window */
  int width;
  /** Height of the window */
  int height;
  /** Windowed width */
  int windowedWidth = 1280;
  /** Windowed height */
  int windowedHeight = 720;
  /** Windowed X position */
  int windowedX = 100;
  /** Windowed Y position */
  int windowedY = 100;


  /** Window title */
  std::string title;
  /** GLFW Window object */
  GLFWwindow* pWindow;
  /** Resize callback function pointer */
  std::function<void(GLFWwindow*, int, int)> resizeCallback;
  /** TEMPORARY SECONDARY RESIZE CALLBACK FOR PAUSE MENU */
  std::function<void(GLFWwindow*, int, int)> resizeCallback2;
  /* This should be reworked in the future to use an Event
  * Broadcast specifically for Engine Events.
  * 
  * Ideally we have an Engine State Manager that can handle Engine
  * events like this. We can have the Engine handle the Event broadcast
  * and all the related systems can register themselves to the Engine
  * Event Broadcast List.
  * 
  * Note: We also need to split the Event Manager Broadcast listeners
  * to have multiple lists per type. This will reduce processing times
  * for physics too.
  */


  std::function<void(GLFWwindow*, double, double)> cursorPosCallback;
  std::function<void(GLFWwindow*, int, int, int)> mouseButtonCallback;

  static void resizeCallbackWrapper(
    GLFWwindow* pWindow, int width, int height);
  static void cursorPosCallbackWrapper(
    GLFWwindow* pWindow, double xpos, double ypos);
  static void mouseButtonCallbackWrapper(
    GLFWwindow* pWindow, int button, int action, int mods);

  /* Renderer functions */
  void setWindowHints(const std::function<void()>& hintSetter) const;
  void setResizeCallback(
      std::function<void(GLFWwindow*, int, int)> callback);
  void setCursorPosCallback(
      std::function<void(GLFWwindow*, double, double)> callback);
  void setMouseButtonCallback(
      std::function<void(GLFWwindow*, int, int, int)> callback);

};

#endif // GAME_WINDOW_H
