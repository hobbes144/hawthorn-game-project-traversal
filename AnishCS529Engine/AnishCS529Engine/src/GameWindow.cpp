/*!****************************************************************************
 * \file   GameWindow.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-05-2024
 *
 *****************************************************************************/
#include "GameWindow.h"


 /* Private functions */

 /*!****************************************************************************
  * \brief Wrapper for resize callback function that is sent to
  * glfwSetFramebufferSizeCallback
  *
  * ## Explanation:
  *
  * The resize callback wrapper and the callback function that comes from the
  * renderer is called automatically when the window undergoes a resize event.
  *
  * This function is used in GameWindow::setResizeCallback(
  *   std::function<void(GLFWwindow*, int, int)> callback).
  *
  * We use this function to ensure that when the resize event occurs, the
  * following happens:
  * - The width and height variables of the window are updated.
  * - The Renderer viewport is modified to use the new width and height.
  *   > The renderer viewport modification is done by using the renderer's
  *     given callback function. This is why the renderer must call
  *     Renderer::setupCallbacks().
  *
  * \param pWindow GLFW window pointer.
  * \param width Width of the window.
  * \param height Height of the window.
  *****************************************************************************/
void GameWindow::resizeCallbackWrapper(GLFWwindow* pWindow, int width,
                                       int height)
{
  auto* gameWindow =
    static_cast<GameWindow*>(glfwGetWindowUserPointer(pWindow));

  if (gameWindow && gameWindow->resizeCallback)
  {
    gameWindow->resizeCallback(pWindow, width, height);
    gameWindow->width = width;
    gameWindow->height = height;
  }
}

/*!****************************************************************************
 * \brief Function that calls the provided hint setter function
 *
 * ## Explanation:
 *
 * This is used to setup OpenGL window hints so that the renderer can properly
 * bind to the window.
 *
 * \param hintSetter Hint setter function that is called by this function.
 *****************************************************************************/
void GameWindow::setWindowHints(const std::function<void()>& hintSetter)
{
  hintSetter();
}

/*!****************************************************************************
 * \brief Function that sets the resize callback to the resize callback wrapper
 *
 * ## Explanation:
 *
 * This is used to register the resize callback wrapper function to the event.
 * Refer to the notes in:
 * GameWindow::resizeCallbackWrapper(GLFWwindow *pWindow, int width,
 *                                   int height)
 *
 * \param callback The callback function sent by the Renderer, which needs to
 * be registered to glfwSetFramebufferSizeCallback.
 *****************************************************************************/
void GameWindow::setResizeCallback(
  std::function<void(GLFWwindow*, int, int)> callback)
{
  resizeCallback = std::move(callback);
  glfwSetFramebufferSizeCallback(pWindow, resizeCallbackWrapper);
  glfwSetWindowUserPointer(pWindow, this);
}

/* Public functions */

/*!****************************************************************************
 * \brief Setter for the window title
 *
 * ## Usage:
 *
 * This is used to label and identify windows. Multiple windows must have
 * different titles.
 *
 * \param _title Title of the window.
 *****************************************************************************/
void GameWindow::setTitle(std::string _title) {
  title = _title;
}

/*!****************************************************************************
 * \brief Setter for the width of the window
 *
 * \param _width Width of the window
 *****************************************************************************/
void GameWindow::setWidth(int _width)
{
  width = _width;
}

/*!****************************************************************************
 * \brief Setter for the height of the window
 *
 * \param _height Height of the window.
 *****************************************************************************/
void GameWindow::setHeight(int _height)
{
  height = _height;
}

/*!****************************************************************************
 * \brief Setter for if Vsync should be used
 *
 * ## Usage:
 *
 * THIS FUNCTION MUST ONLY BE CALLED AFTER `Renderer::init()`!
 * Calling this function before initializing the renderer will lead to a
 * `GLFW_NO_CURRENT_CONTEXT` error.
 *
 * This sets up OpenGL to wait for the screen to fully update before swapping
 * the buffers.
 *
 * ## Explanation:
 *
 * Default behaviour for buffer swapping varies by device, so setting this
 * ensures vsync behaviour.
 * If set to false, buffer swapping occurs acyncronouosly as soon as
 * the frame is ready.
 * If set to true, buffer will wait for screen update before swapping.
 *
 * \param flag
 *****************************************************************************/
void GameWindow::setVsync(bool flag) {
  if (flag)
    glfwSwapInterval(1);
  else
    glfwSwapInterval(0);
}

/*!****************************************************************************
 * \brief Function to set the window should close signal
 *
 * ## Usage:
 *
 * Use this at the end of game loop to close the window and end the rendering.
 *
 * \return \b true Window is about to close.
 * \return \b false GLFW failure occured when closing the window.
 *****************************************************************************/
void GameWindow::setShouldClose() const
{
  glfwSetWindowShouldClose(pWindow, true);
}

/*!****************************************************************************
 * \brief Function to receive the window should close signal
 *
 * Usage:
 *
 * This is typically called in the main loop to check for end of loop or if
 * program shutdown procedures should be run.
 *
 * \return \b true Window is about to close.
 * \return \b false GLFW failure occured when closing the window.
 *****************************************************************************/
bool GameWindow::getShouldClose() const
{
  return glfwWindowShouldClose(pWindow);
}

/*!****************************************************************************
 * \brief Getter for GLFW window object
 *
 * \return \b GLFWwindow* The GLFW window object represented by this class
 * object.
 *****************************************************************************/
GLFWwindow* GameWindow::getNativeWindow() const
{
  return pWindow;
}

/*!****************************************************************************
 * \brief Getter for the width of the window
 *
 * \return \b int Width of the window.
 *****************************************************************************/
int GameWindow::getWidth()
{
  return width;
}

/*!****************************************************************************
 * \brief Getter for the height of the window
 *
 * \return \b int Height of the window.
 *****************************************************************************/
int GameWindow::getHeight()
{
  return height;
}

/*!****************************************************************************
 * \brief Initializer for GLFW and the GLFW window
 *
 * ## Required calls before init:
 * - setTitle(std::string _title)
 * - setWidth(int _width)
 * - setHeight(int _height)
 *
 * ## Usage:
 *
 * This must be called at the start of the program to create the game window.
 *
 *****************************************************************************/
void GameWindow::initialize()
{
  if (!glfwInit())
  {
    throw std::runtime_error("Failed to initialize GLFW");
  }
  pWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (!pWindow)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }
}

/*!****************************************************************************
 * \brief Update function
 *
 * ## Usage:
 *
 * This function must be called at the end/beginning of the game loop to read
 * window events. This includes all mouse, keyboard and other input device
 * signals as long as the window is in focus.
 *
 *****************************************************************************/
void GameWindow::update() {
  glfwPollEvents();
}

/*!****************************************************************************
 * \brief Shutdown function to terminate the window and GLFW
 *
 * ## Usage:
 *
 * This function destroys the game window and terminates OpenGL.
 *
 *****************************************************************************/
void GameWindow::shutdown()
{
  if (pWindow)
  {
    glfwDestroyWindow(pWindow);
    glfwTerminate();
  }
}
