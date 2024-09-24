#include "GameWindow.h"


//GameWindow::GameWindow(int width, int height, std::string& title) : width(width), height(height), title(title) {
//    initialize();
//}

/* Private functions */

/* Initialization subfunctions */
GLFWwindow* GameWindow::createWindow() {
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        return nullptr;
    }
    return window;
}


/* Destruction subfunctions */

void GameWindow::shutdownWindow() {
    glfwDestroyWindow(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


/* Public functions */

GLFWwindow* GameWindow::getGLFWWindow() {
    return window;
}

bool GameWindow::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void GameWindow::swapBuffers() {
    glfwSwapBuffers(window);
}

