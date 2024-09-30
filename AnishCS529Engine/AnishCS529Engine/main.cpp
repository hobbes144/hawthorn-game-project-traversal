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
		unsigned int triangleVaoId;

		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\0";

		renderer.createVertexShader(vertexShaderSource);
		renderer.createFragmentShader(fragmentShaderSource);
		renderer.initializeShaders();
		triangleVaoId = renderer.addTriangle(
			Vector3(-0.5f, -0.5f, 0.0f),
			Vector3(0.5f, -0.5f, 0.0f),
			Vector3(0.0f, 0.5f, 0.0f)
		);

		while (!window.shouldClose())
		{

			window.pollEvents();
			processInput(window.getNativeWindow());
			
			renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);

			renderer.drawTriangle(triangleVaoId);

			/*renderer.drawTriangle(
				Vector3(-0.5f, -0.5f, 0.0f),
				Vector3(0.5f, -0.5f, 0.0f),
				Vector3(0.0f, 0.5f, 0.0f)
			);*/

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