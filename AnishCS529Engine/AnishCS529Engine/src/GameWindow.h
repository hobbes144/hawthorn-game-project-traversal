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
  bool getShouldClose() const;
  void setShouldClose() const;
  GLFWwindow* getNativeWindow() const;

private:
  /** Width of the window */
  int width;
  /** Height of the window */
  int height;
  /** Window title */
  std::string title;
  /** GLFW Window object */
  GLFWwindow* pWindow;
  /** Resize callback function pointer */
  std::function<void(GLFWwindow*, int, int)> resizeCallback;

  static void resizeCallbackWrapper(GLFWwindow* pWindow, int width,
                                    int height);

  /* Renderer functions */
  void setWindowHints(const std::function<void()>& hintSetter) const;
  void setResizeCallback(
      std::function<void(GLFWwindow*, int, int)> callback);

};

#endif // GAME_WINDOW_H
