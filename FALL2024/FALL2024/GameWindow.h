// GameWindow - version 2

#pragma once

#include <glfw3.h>
#include <string>
#include <stdexcept>
#include <functional>
#include <iostream>

class GameWindow {
public:
    GameWindow(int width, int height, const std::string& title);

    ~GameWindow();

    bool shouldClose() const;

    void pollEvents();

    GLFWwindow* getNativeWindow() const;

    void setWindowHints(const std::function<void()>& hintSetter);

    int getWidth() const;
    int getHeight() const;

    void setResizeCallback(std::function<void(GLFWwindow*, int, int)> callback);

private:
    void initialize();

    void shutdown();

    static void resizeCallbackWrapper(GLFWwindow* window, int width, int height);

    int width;
    int height;
    std::string title;
    GLFWwindow* pWindow;
    std::function<void(GLFWwindow*, int, int)> resizeCallback;

};
