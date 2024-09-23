#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>

#include <GameWindow.h>

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(void) {

	glfwInit();

	try {
		GameWindow window;

		while (!glfwWindowShouldClose(window.getWindow()))
		{
			processInput(window.getWindow());
			

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window.getWindow());
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