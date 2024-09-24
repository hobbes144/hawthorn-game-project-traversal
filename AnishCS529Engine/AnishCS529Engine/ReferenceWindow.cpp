#define GLFW_INCLUDE_NONE
#include <glew.h>
#include <glfw3.h>

#include <iostream>



// First version of a simple render on the screen
// Step-by-step window configuration
bool initializeLibraries();
GLFWwindow* createWindow();
bool setupGraphicsContext(GLFWwindow* window);
bool loadGraphicsAPIFunctions();
void pollEvents();
void updateWindow(GLFWwindow* window);
void shutdownWindow(GLFWwindow* window);
void shutdownLibraries();

//int main() {
//    // Step 1: Setup the libraries in project
//    // Note: This step is typically done in the build system (e.g., Makefile, CMakeLists.txt, or IDE project settings)
//    // For this example, we assume the libraries are already set up correctly
//
//    // Step 2: Initialize the libraries
//    if (!initializeLibraries()) {
//        return -1;
//    }
//
//    // Step 3: Create window
//    GLFWwindow* window = createWindow();
//    if (!window) {
//        shutdownLibraries();
//        return -1;
//    }
//
//    // Step 4: Setup the graphics context
//    if (!setupGraphicsContext(window)) {
//        shutdownWindow(window);
//        shutdownLibraries();
//        return -1;
//    }
//
//    // Step 5: Load Graphics API functions
//    if (!loadGraphicsAPIFunctions()) {
//        shutdownWindow(window);
//        shutdownLibraries();
//        return -1;
//    }
//
//    // Step 6: Handle window state (Open/Closed)
//    while (!glfwWindowShouldClose(window)) {
//        // Step 7: Poll input events during the render loop
//        pollEvents();
//
//        // Render here (in this example, just clear the screen)
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Step 8: Update the window
//        updateWindow(window);
//    }
//
//    // Step 9: Shutdown the window
//    shutdownWindow(window);
//
//    // Step 10: Shutdown libraries
//    shutdownLibraries();
//
//    return 0;
//}

bool initializeLibraries() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    return true;
}

GLFWwindow* createWindow() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return nullptr;
    }
    return window;
}

bool setupGraphicsContext(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
    return true;
}

bool loadGraphicsAPIFunctions() {
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }
    return true;
}

void pollEvents() {
    glfwPollEvents();
}

void updateWindow(GLFWwindow* window) {
    glfwSwapBuffers(window);
}

void shutdownWindow(GLFWwindow* window) {
    glfwDestroyWindow(window);
}

void shutdownLibraries() {
    glfwTerminate();
}