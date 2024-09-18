#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>

class Window {
private:
	GLFWwindow* window;

public:
	Window();
	GLFWwindow* getWindow();
	~Window();
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);