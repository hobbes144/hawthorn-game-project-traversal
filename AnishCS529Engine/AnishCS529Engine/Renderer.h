#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "GameWindow.h"

class Renderer {
private:
	GameWindow& gameWindow;

	void initialize();
	bool loadGraphicsAPIFunctions();
	void setupCallbacks();
	void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height);

public:
	Renderer(GameWindow& gameWindow);

	void clear(float r, float g, float b, float a);
	void swapBuffers();
};