#include "GameWindow.h"


GameWindow::GameWindow(int width, int height, std::string title) : width(width), height(height), title(title), pWindow(nullptr) {
    initialize();
}

/* Private functions */

/* Initializer */
void GameWindow::initialize() {
    if (!glfwInit()) {
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

/* Destroyer */
void GameWindow::shutdown() {
    if (pWindow) {
        glfwDestroyWindow(pWindow);
        glfwTerminate();
    }
}

void GameWindow::resizeCallbackWrapper(GLFWwindow* pWindow, int width, int height) {
    auto* gameWindow = static_cast<GameWindow*>(glfwGetWindowUserPointer(pWindow));
    if (gameWindow && gameWindow->resizeCallback) {
        gameWindow->resizeCallback(pWindow, width, height);
        gameWindow->width = width;
        gameWindow->height = height;
        std::cout << "Window size : (" << width << ", " << height << ")" << std::endl;
    }
}


/* Public functions */

bool GameWindow::shouldClose() const {
    return glfwWindowShouldClose(pWindow);
}

void GameWindow::pollEvents() {
    glfwPollEvents(); /* Todo: Why is this a part of window? */
}

GLFWwindow* GameWindow::getNativeWindow() const {
    return pWindow;
}

int GameWindow::getWidth() {
    return width;
}

int GameWindow::getHeight() {
    return height;
}

void GameWindow::setWindowHints(const std::function<void()>& hintSetter) {
    hintSetter();
}

void GameWindow::setResizeCallback(std::function<void(GLFWwindow*, int, int)> callback) {
    resizeCallback = std::move(callback);
    glfwSetFramebufferSizeCallback(pWindow, resizeCallbackWrapper);
    glfwSetWindowUserPointer(pWindow, this);
}