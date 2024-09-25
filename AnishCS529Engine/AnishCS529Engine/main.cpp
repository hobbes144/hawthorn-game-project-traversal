#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>

#include "GameWindow.h"
#include "Renderer.h"

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void swapBuffers(GLFWwindow* window) {
	glfwSwapBuffers(window);
}

void shutdownLibraries() {
	glfwTerminate();
}

int main(void) {

	try {
		GameWindow window(800, 600, "Assignment 2");
		Renderer renderer(window);

		while (!window.shouldClose())
		{
			window.pollEvents();

			processInput(window.getNativeWindow());
			
			renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);
			renderer.swapBuffers();
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