#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>

#include <window.h>

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(void) {

	glfwInit();

	try {
		Window w;

		while (!glfwWindowShouldClose(w.getWindow()))
		{
			processInput(w.getWindow());

			glfwSwapBuffers(w.getWindow());
			glfwPollEvents();
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwTerminate();
	return 0;
}