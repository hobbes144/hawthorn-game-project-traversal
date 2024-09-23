#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>

class GameWindow {
private:
	GLFWwindow* window;

public:
	GameWindow();
	GLFWwindow* getWindow();
	~GameWindow();
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);