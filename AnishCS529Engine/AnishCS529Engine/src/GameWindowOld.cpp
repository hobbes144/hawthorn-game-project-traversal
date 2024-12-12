///*!****************************************************************************
// * \file   GameWindow.cpp
// * \author Anish Murthy (anish.murthy.dev@gmail.com)
// * \par    **DigiPen Email**
// *    anish.murthy@digipen.edu
// * \par    **Course**
// *    CS529
// * \date   10-05-2024
// *
// *****************************************************************************/
//#include "GameWindow.h"
//
// /*!****************************************************************************
//  * \brief Construct a new Game Window object
//  *
//  * \param width Width of the window.
//  * \param height Height of the window.
//  * \param title Window title.
//  *****************************************************************************/
//GameWindow::GameWindow(int width, int height, std::string title) :
//  width(width), height(height), title(title), pWindow(nullptr)
//{
//  initialize();
//}
//
///* Private functions */
//
///* Initializer */
///*!****************************************************************************
// * \brief Initializer for GLFW and the GLFW window
// *
// *****************************************************************************/
//void GameWindow::initialize()
//{
//  if (!glfwInit())
//  {
//    throw std::runtime_error("Failed to initialize GLFW");
//  }
//  pWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
//  if (!pWindow)
//  {
//    std::cout << "Failed to create GLFW window" << std::endl;
//    glfwTerminate();
//    throw std::runtime_error("Failed to create GLFW window");
//  }
//}
//
///* Destroyer */
///*!****************************************************************************
// * \brief Shutdown function to terminate the window and GLFW
// *
// *****************************************************************************/
//void GameWindow::shutdown()
//{
//  if (pWindow)
//  {
//    glfwDestroyWindow(pWindow);
//    glfwTerminate();
//  }
//}
//
///*!****************************************************************************
// * \brief Wrapper for resize callback function that is sent to
// * glfwSetFramebufferSizeCallback
// *
// * \param pWindow GLFW window pointer.
// * \param width Width of the window.
// * \param height Height of the window.
// *****************************************************************************/
//void GameWindow::resizeCallbackWrapper(GLFWwindow* pWindow, int width,
//                                       int height)
//{
//  auto* gameWindow =
//    static_cast<GameWindow*>(glfwGetWindowUserPointer(pWindow));
//
//  if (gameWindow && gameWindow->resizeCallback)
//  {
//    gameWindow->resizeCallback(pWindow, width, height);
//    gameWindow->width = width;
//    gameWindow->height = height;
//  }
//}
//
///* Public functions */
///*!****************************************************************************
// * \brief Function to receive the window should close signal
// *
// * This is typically called in the main loop to check for end of loop or if
// * program shutdown procedures should be run.
// *
// * \return \b true Window is about to close.
// * \return \b false GLFW failure occured when closing the window.
// *****************************************************************************/
//bool GameWindow::getShouldClose() const
//{
//  return glfwWindowShouldClose(pWindow);
//}
//
///*!****************************************************************************
// * \brief Function to set the window should close signal
// *
// * This is typically called to close the window and end the rendering.
// *
// * \return \b true Window is about to close.
// * \return \b false GLFW failure occured when closing the window.
// *****************************************************************************/
//void GameWindow::setShouldClose() const
//{
//  glfwSetWindowShouldClose(pWindow, true);
//}
//
///*!****************************************************************************
// * \brief Function to poll window events
// *
// * Polled events include all mouse, keyboard and other input device signals
// * as long as the window is in focus.
// *
// *****************************************************************************/
//void GameWindow::pollEvents()
//{
//  glfwPollEvents();
//}
//
///*!****************************************************************************
// * \brief Getter for GLFW window object
// *
// * \return \b GLFWwindow* The GLFW window object represented by this class
// * object.
// *****************************************************************************/
//GLFWwindow* GameWindow::getNativeWindow() const
//{
//  return pWindow;
//}
//
///*!****************************************************************************
// * \brief Getter for the width of the window
// *
// * \return \b int Width of the window.
// *****************************************************************************/
//int GameWindow::getWidth()
//{
//  return width;
//}
//
///*!****************************************************************************
// * \brief Getter for the height of the window
// *
// * \return \b int Height of the window.
// *****************************************************************************/
//int GameWindow::getHeight()
//{
//  return height;
//}
//
///*!****************************************************************************
// * \brief Function that calls the provided hint setter function
// *
// * This is used to setup OpenGL window hints so that the renderer can properly
// * bind to the window.
// *
// * \param hintSetter Hint setter function that is called by this function.
// *****************************************************************************/
//void GameWindow::setWindowHints(const std::function<void()>& hintSetter)
//{
//  hintSetter();
//}
//
///*!****************************************************************************
// * \brief Function that sets the resize callback to the resize callback wrapper
// *
// * This is used to setup the callback function that performs the following when
// *  the user resizes the window:
// * - Update the window's width and height.
// * - Update the drawable width and height area in the Renderer class.
// *
// * \param callback The callback function sent by the Renderer, which needs to
// * be registered to glfwSetFramebufferSizeCallback.
// *****************************************************************************/
//void GameWindow::setResizeCallback(
//  std::function<void(GLFWwindow*, int, int)> callback)
//{
//  resizeCallback = std::move(callback);
//  glfwSetFramebufferSizeCallback(pWindow, resizeCallbackWrapper);
//  glfwSetWindowUserPointer(pWindow, this);
//}
//
//void GameWindow::setVsync(bool flag) {
//  if (flag)
//    glfwSwapInterval(1);
//  else
//    glfwSwapInterval(0);
//}