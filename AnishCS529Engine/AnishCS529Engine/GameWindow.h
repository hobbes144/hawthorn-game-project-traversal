#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class GameWindow {
private:
	int width, height;
	std::string title;
	GLFWwindow* window;

    /* Initialization subfunctions */
    GLFWwindow* createWindow();

    /* Destuction subfunctions */
    void shutdownWindow();

    /* Initializer called by Constructor */
	void initialize() {
        window = createWindow();
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            throw std::runtime_error("Failed to create GLFW window");
        }        
	}

    /* Destroyer called by Destructor */
    void destroy() {
        if (window) {
            shutdownWindow();
        }
    }

public:
    /* Constructor */
	GameWindow(int width, int height, std::string title) : width(width), height(height), title(title) {
        initialize();
    };

    /* Public functions */
	GLFWwindow* getGLFWWindow();
    bool shouldClose() const;
    void swapBuffers();

    /* Destructor */
    ~GameWindow() {
        destroy();
    }
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);