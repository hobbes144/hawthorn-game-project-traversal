/*!****************************************************************************
 * \file   Renderer.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-14-2024
 * \brief  Renderer implementation to initialize the OpenGL libraries
 * and libraries.
 *
 *****************************************************************************/
#ifndef RENDERER_H
#define RENDERER_H

#pragma once

/* OpenGL imports */
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

/* Base class */
#include "Component.h"

/* Used classes */
#include "GameWindow.h"

/*!****************************************************************************
 * \brief Class Renderer that implements an OpenGL renderer
 * 
 * ## Usage:
 * 
 * Renderer is needed to render objects onto the screen. This needs to be
 * initialized to work with a window, and the draw call must be made to draw
 * objects to the screen.
 * 
 * ## Pre-initialization calls:
 * - setGameWindow(GameWindow* _gameWindow)
 * - setIs3D(bool is3D)
 * - setClearColor(float r, float g, float b, float a)
 * 
 * ## General lifecycle of a Renderer:
 * 
 * - Init GameWindow object.
 * - Init Renderer
 * - Call clear() to empty the window buffer.
 * - Run all your game logic
 * - Run draw() calls for each of the objects to be rendered.
 * - Call swapBuffers() to render the window buffer to the screen.
 * 
 * ## Notes:
 * 
 * Renderer class is specific to a window. It is possible to have multiple
 * renderers, one for each window you have.
 * 
 *****************************************************************************/
class Renderer : public Component {
public:
  Renderer() = default;
  ~Renderer() = default;

  /* Component functions */
  void initialize();
  void update(); // Dummy
  void shutdown(); // Dummy

  /* Pre-initialization functions */
  void setGameWindow(GameWindow* _gameWindow);
  void setIs3D(bool is3D);
  void setClearColor(float r, float g, float b, float a);

  /* Utility functions */
  void clear();
  void swapBuffers();
  void draw(GLenum mode, GLint count, bool indexed);

private:
  /** Game Window object */
  GameWindow* gameWindow;
  /** Clear mask for glClear */
  GLbitfield glClearMask;

  bool loadGraphicsAPIFunctions();
  void setupCallbacks();
  void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height);

};

#endif // RENDERER_H
