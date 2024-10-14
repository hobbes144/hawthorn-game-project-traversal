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
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <functional>

/*!****************************************************************************
 * \brief Class that sets up the GLFW window and associated
 * logic
 *
 *****************************************************************************/
class GameWindow
{
private:
  /** Width of the window */
  int width;
  /** Height of the window */
  int height;
  /** Window title */
  std::string title;
  /** GLFW Window object */
  GLFWwindow *pWindow;
  /** Resize callback function pointer */
  std::function<void(GLFWwindow *, int, int)> resizeCallback;

  /* Initializer called by Constructor */
  void initialize();

  /* Destroyer called by Destructor */
  void shutdown();

  static void resizeCallbackWrapper(GLFWwindow *pWindow, int width,
                                    int height);

public:
  /* Constructor */
  GameWindow(int width, int height, std::string title);

  /* Public functions */
  GLFWwindow *getNativeWindow() const;
  int getWidth();
  int getHeight();

  bool shouldClose() const;
  void pollEvents();

  void setWindowHints(const std::function<void()> &hintSetter);

  void setResizeCallback(
      std::function<void(GLFWwindow *, int, int)> callback);

  /* Destructor */
  ~GameWindow()
  {
    shutdown();
  }
};

#endif // GAME_WINDOW_H
