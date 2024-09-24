#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>

#include <GameWindow.h>

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

bool initializeLibraries() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	return true;
}

bool setupGraphicsContext(GLFWwindow* window) {
	glfwMakeContextCurrent(window);
	return true;
}

bool loadGraphicsAPIFunctions() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}
	return true;
}

void pollEvents() {
	glfwPollEvents();
}

void clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void shutdownLibraries() {
	glfwTerminate();
}

int main(void) {

	if (!initializeLibraries()) {
		std::cout << "Failed to initialize GLFW Libraries" << std::endl;
		throw std::runtime_error("Failed to initialize GLFW Libraries");
	}

	try {
		GameWindow window(800, 600, "Assignment 2");

		if (!setupGraphicsContext(window.getGLFWWindow())) {
			std::cout << "Failed to set graphics context" << std::endl;
			throw std::runtime_error("Failed to set graphics context");
		}

		if (!loadGraphicsAPIFunctions()) {
			std::cout << "Failed to load graphics API functions" << std::endl;
			throw std::runtime_error("Failed to load graphics API functions");
		}

		while (!window.shouldClose())
		{
			pollEvents();

			processInput(window.getGLFWWindow());
			
			clear(0.2f, 0.3f, 0.3f, 1.0f);
			window.swapBuffers();
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		glfwTerminate();
		return 1;
	}

	shutdownLibraries();
	return 0;
}