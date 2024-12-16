/*!****************************************************************************
 * \file   Renderer.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-14-2024
 *
 *****************************************************************************/
#include "Renderer.h"

const float pi = 3.14159f;

/* Private functions */

// OpenGL Debugging function
/*!****************************************************************************
 * \brief OpenGL debug callback function to print OpenGL renderer errors
 * 
 * ## Explanation:
 * 
 * Assume that this is a black box. OpenGL automatically provides the arguments
 * for this, we just need to setup the callback and we can customize the
 * prints if needed.
 * 
 *****************************************************************************/
void APIENTRY openglCallbackFunction(
  GLenum source, GLenum type, GLuint id, GLenum severity,
  GLsizei length, const GLchar* message, const void* userParam)
{
  std::string sourceStr;
  switch (source)
  {
  case GL_DEBUG_SOURCE_API:             sourceStr = "API"; break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceStr = "Window System"; break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "Shader Compiler"; break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceStr = "Third Party"; break;
  case GL_DEBUG_SOURCE_APPLICATION:     sourceStr = "Application"; break;
  case GL_DEBUG_SOURCE_OTHER:           sourceStr = "Other"; break;
  }

  std::string typeStr;
  switch (type)
  {
  case GL_DEBUG_TYPE_ERROR:               typeStr = "Error"; break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Deprecated Behavior"; break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeStr = "Undefined Behavior"; break;
  case GL_DEBUG_TYPE_PORTABILITY:         typeStr = "Portability"; break;
  case GL_DEBUG_TYPE_PERFORMANCE:         typeStr = "Performance"; break;
  case GL_DEBUG_TYPE_MARKER:              typeStr = "Marker"; break;
  case GL_DEBUG_TYPE_PUSH_GROUP:          typeStr = "Push Group"; break;
  case GL_DEBUG_TYPE_POP_GROUP:           typeStr = "Pop Group"; break;
  case GL_DEBUG_TYPE_OTHER:               typeStr = "Other"; break;
  }

  std::string severityStr;
  switch (severity)
  {
  case GL_DEBUG_SEVERITY_HIGH:         severityStr = "High"; break;
  case GL_DEBUG_SEVERITY_MEDIUM:       severityStr = "Medium"; break;
  case GL_DEBUG_SEVERITY_LOW:          severityStr = "Low"; break;
  case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "Notification"; break;
  }

  std::cerr << "OpenGL Debug Message\n"
    << "Source: " << sourceStr << "\n"
    << "Type: " << typeStr << "\n"
    << "ID: " << id << "\n"
    << "Severity: " << severityStr << "\n"
    << "Message: " << message << std::endl;
}

/*!****************************************************************************
 * \brief Load OpenGL API
 * 
 * ## Explanation:
 * 
 * This function initializes OpenGL and sets up basic config so we can start
 * using it. 
 * 
 * \return \b 
 *****************************************************************************/
bool Renderer::loadGraphicsAPIFunctions() const {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    return false;
  }
  // Enable debug
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Makes sure errors are reported immediately
  //glEnable(GL_DEPTH_TEST);
  glDebugMessageCallback(openglCallbackFunction, nullptr);
  return true;
}

/*!****************************************************************************
 * \brief Setup Window resize callback
 * 
 * ## Explanation:
 * 
 * This function registers the callback function to the window so that changes
 * to the width and height of the window can be read and used to resize the
 * rendering viewport.
 * 
 *****************************************************************************/
void Renderer::setupCallbacks() const {
  gameWindow->setResizeCallback([this](GLFWwindow* pWindow, int width, int height) {
    this->framebufferSizeCallback(pWindow, width, height);
    });
}

/*!****************************************************************************
 * \brief Set up viewport based on window size
 * 
 * ## Explanation:
 * 
 * This is the callback function that is called by the window when there is a
 * change in the window's width and height. This allows users to manually
 * modify the window dimensions and have the rendering match the window size.
 * 
 * \param pWindow
 * \param width
 * \param height
 *****************************************************************************/
void Renderer::framebufferSizeCallback(
  GLFWwindow* pWindow, int width, int height) const {

  glViewport(0, 0, width, height);
  // Additional rendering adjustments can be made here
}



/* Public functions */

/*!****************************************************************************
 * \brief Setter for game window
 *
 * ## Usage:
 *
 * This funciton is to be called to set up the game window that the renderer
 * will output to.
 *
 * ## Explanation:
 *
 * Renderer will always output to a specific window. We can have multiple
 * instances of renderer for multiple windows if needed.
 *
 * \param _gameWindow
 * \return \b Renderer* this
 *****************************************************************************/
Renderer* Renderer::setGameWindow(GameWindow* _gameWindow) {
  gameWindow = _gameWindow;

  return this;
}

/*!****************************************************************************
 * \brief Set if the renderer should render in 3D
 * 
 * ## Usage:
 * 
 * Sets OpenGL config to enable 3D rendering.
 * 
 * ## Explanation:
 * 
 * The renderer will perform optimizations specific to 2D rendering if not set
 * to `true`.
 * 
 * It enables depth in the rendering if set to `true`.
 * 
 * \param is3D True if rendering should be in 3D space
 * \return \b Renderer* this
 *****************************************************************************/
Renderer* Renderer::setIs3D(bool is3D) {
  if (is3D) {
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    clearMask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
  }
  else {
    glDisable(GL_DEPTH_TEST);
    clearMask = GL_COLOR_BUFFER_BIT;
  }

  return this;
}

/*!****************************************************************************
 * \brief Set the clear color of the screen
 * 
 * ## Usage:
 * 
 * Sets the clear color for each screen clear.
 * 
 * \param r Red
 * \param g Green
 * \param b Blue
 * \param a Alpha
 * \return \b Renderer* this
 *****************************************************************************/
Renderer* Renderer::setClearColor(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);

  return this;
}

/*!****************************************************************************
 * \brief Clear the window
 * 
 * ## Usage:
 * 
 * This is to be called at the start of each frame.
 * 
 * ## Explanation:
 * 
 * The window must be cleared after each draw to ensure we are starting with a
 * clean window.
 * 
 *****************************************************************************/
void Renderer::clear() const {
  glClear(clearMask);
}

/*!****************************************************************************
 * \brief Swap window buffers
 * 
 * ## Usage:
 * 
 * This is to be called at the end of each frame.
 * 
 * ## Explanation:
 * 
 * Until this is called, the frame will not appear on screen. Ensure this is
 * called at the end of your rendering logic.
 * 
 *****************************************************************************/
void Renderer::swapBuffers() const {
  glfwSwapBuffers(gameWindow->getNativeWindow());
}

/*!****************************************************************************
 * \brief Draw objects in buffers
 * 
 * ## Usage:
 * 
 * Calls the appropriate draw call to draw the objects in the buffers.
 * 
 * \param mode OpenGL Draw mode (eg. GL_TRIANGLES)
 * \param count Number of vertices to be drawn
 * \param indexed If true, EBO will be used. Defaults to `true`.
 *****************************************************************************/
void Renderer::draw(GLenum mode, GLint count, bool indexed = true) const {
  if (indexed) {
    glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
  }
  else {
    glDrawArrays(mode, 0, count);
  }
}

/*!****************************************************************************
 * \brief Initialize the renderer
 * 
 * ## Required calls before init:
 * - setGameWindow(GameWindow* _gameWindow)
 * - setIs3D(bool is3D)
 * - setClearColor(float r, float g, float b, float a)
 * 
 * ## Usage:
 * 
 * Initializes the renderer to load OpenGL.
 * 
 *****************************************************************************/
void Renderer::initialize() {
  gameWindow->setWindowHints([]() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    /* Todo: What is this command? */
    });

  glfwMakeContextCurrent(gameWindow->getNativeWindow());
  setupCallbacks();


  if (!loadGraphicsAPIFunctions()) {
    throw std::runtime_error("Failed to load Graphics API Functions");
  }
}

/*!****************************************************************************
 * \brief Renderer Update is a dummy call.
 * 
 * Use Renderer.clear and Renderer.swapBuffers separately as needed.
 * 
 *****************************************************************************/
void Renderer::update() {}

/*!****************************************************************************
 * \brief Renderer Shutdown is a dummy call.
 * 
 * Renderer does not have any shutdown logic.
 * 
 *****************************************************************************/
void Renderer::shutdown() {}
