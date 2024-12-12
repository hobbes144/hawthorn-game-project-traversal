///*!****************************************************************************
// * \file   Renderer.cpp
// * \author Anish Murthy (anish.murthy.dev@gmail.com)
// * \par    **DigiPen Email**
// *    anish.murthy@digipen.edu
// * \par    **Course**
// *    CS529
// * \date   10-14-2024
// * 
// *****************************************************************************/
//#include "Renderer.h"
//
//const float pi = 3.14159f;
//
//// OpenGL Debugging function
//void APIENTRY openglCallbackFunction(
//  GLenum source, GLenum type, GLuint id, GLenum severity,
//  GLsizei length, const GLchar* message, const void* userParam)
//{
//  std::string sourceStr;
//  switch (source)
//  {
//  case GL_DEBUG_SOURCE_API:             sourceStr = "API"; break;
//  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceStr = "Window System"; break;
//  case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "Shader Compiler"; break;
//  case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceStr = "Third Party"; break;
//  case GL_DEBUG_SOURCE_APPLICATION:     sourceStr = "Application"; break;
//  case GL_DEBUG_SOURCE_OTHER:           sourceStr = "Other"; break;
//  }
//
//  std::string typeStr;
//  switch (type)
//  {
//  case GL_DEBUG_TYPE_ERROR:               typeStr = "Error"; break;
//  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Deprecated Behavior"; break;
//  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeStr = "Undefined Behavior"; break;
//  case GL_DEBUG_TYPE_PORTABILITY:         typeStr = "Portability"; break;
//  case GL_DEBUG_TYPE_PERFORMANCE:         typeStr = "Performance"; break;
//  case GL_DEBUG_TYPE_MARKER:              typeStr = "Marker"; break;
//  case GL_DEBUG_TYPE_PUSH_GROUP:          typeStr = "Push Group"; break;
//  case GL_DEBUG_TYPE_POP_GROUP:           typeStr = "Pop Group"; break;
//  case GL_DEBUG_TYPE_OTHER:               typeStr = "Other"; break;
//  }
//
//  std::string severityStr;
//  switch (severity)
//  {
//  case GL_DEBUG_SEVERITY_HIGH:         severityStr = "High"; break;
//  case GL_DEBUG_SEVERITY_MEDIUM:       severityStr = "Medium"; break;
//  case GL_DEBUG_SEVERITY_LOW:          severityStr = "Low"; break;
//  case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "Notification"; break;
//  }
//
//  std::cerr << "OpenGL Debug Message\n"
//    << "Source: " << sourceStr << "\n"
//    << "Type: " << typeStr << "\n"
//    << "ID: " << id << "\n"
//    << "Severity: " << severityStr << "\n"
//    << "Message: " << message << std::endl;
//}
//
///* Private functions */
//void Renderer::initialize() {
//  gameWindow.setWindowHints([]() {
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    /* Todo: What is this command? */
//    });
//  
//  glfwMakeContextCurrent(gameWindow.getNativeWindow());
//  setupCallbacks();
//
//
//  if (!loadGraphicsAPIFunctions()) {
//    throw std::runtime_error("Failed to load Graphics API Functions");
//  }
//
//  enableDepth(depthEnabled);
//}
//
//bool Renderer::loadGraphicsAPIFunctions() {
//  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//  {
//    return false;
//  }
//  // Enable debug
//  glEnable(GL_DEBUG_OUTPUT);
//  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Makes sure errors are reported immediately
//  //glEnable(GL_DEPTH_TEST);
//  glDebugMessageCallback(openglCallbackFunction, nullptr);
//  return true;
//}
//
//void Renderer::setupCallbacks() {
//  gameWindow.setResizeCallback([this](GLFWwindow* pWindow, int width, int height) {
//    this->framebufferSizeCallback(pWindow, width, height);
//    });
//}
//
//void Renderer::framebufferSizeCallback(GLFWwindow* pWindow, int width, int height) {
//  glViewport(0, 0, width, height);
//  // Additional rendering adjustments can be made here
//}
//
///* Public functions */
//Renderer::Renderer(GameWindow& gameWindow) : gameWindow(gameWindow), depthEnabled(false) {
//  initialize();
//}
//
//void Renderer::enableDepth(bool enable) {
//  depthEnabled = enable;
//  if (enable) {
//    glfwWindowHint(GLFW_DEPTH_BITS, 24);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//  }
//  else
//    glDisable(GL_DEPTH_TEST);
//}
//
//void Renderer::clear(float r, float g, float b, float a) {
//  glClearColor(r, g, b, a);
//  if (depthEnabled)
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//  else
//    glClear(GL_COLOR_BUFFER_BIT);
//}
//
//void Renderer::swapBuffers() {
//  glfwSwapBuffers(gameWindow.getNativeWindow());
//}
//
//void Renderer::draw(GLenum mode, GLint count, bool indexed) {
//  if (indexed) {
//    glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
//  }
//  else {
//    glDrawArrays(mode, 0, count);
//  }
//}
