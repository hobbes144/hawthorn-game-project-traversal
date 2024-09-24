#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <functional>



class GameWindow {
private:
    int width, height;
    std::string title;
    GLFWwindow* pWindow;
    std::function<void(GLFWwindow*, int, int)> resizeCallback;

    /* Initializer called by Constructor */
    void initialize();

    /* Destroyer called by Destructor */
    void shutdown();

    static void resizeCallbackWrapper(GLFWwindow* pWindow, int width, int height);

public:
    /* Constructor */
    GameWindow(int width, int height, std::string title);

    /* Public functions */
    GLFWwindow* getNativeWindow() const;
    int getWidth();
    int getHeight();

    bool shouldClose() const;
    void pollEvents();

    void setWindowHints(const std::function<void()>& hintSetter);

    void setResizeCallback(std::function<void(GLFWwindow*, int, int)> callback);

    /* Destructor */
    ~GameWindow() {
        shutdown();
    }
};