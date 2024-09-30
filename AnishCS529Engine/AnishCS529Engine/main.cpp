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

int createTriangleVAO() {
	float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
	};

	unsigned int vaoId, vboId;
	glGenVertexArrays(1, &vaoId);
	glGenBuffers(1, &vboId);

	glBindVertexArray(vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vaoId;
}

void drawObject(int objectVaoID) {
	glBindVertexArray(objectVaoID);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(void) {

	try {
		GameWindow window(800, 600, "Assignment 2");
		Renderer renderer(window);
		unsigned int shaderProgramId;
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
		// triangleVaoId = createTriangleVAO();


		while (!window.shouldClose())
		{

			window.pollEvents();
			processInput(window.getNativeWindow());
			
			renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);

			/*glUseProgram(shaderProgramId);
			drawObject(triangleVaoId);*/

			renderer.drawTriangle(
				Vector3(-0.5f, -0.5f, 0.0f),
				Vector3(0.5f, -0.5f, 0.0f),
				Vector3(0.0f, 0.5f, 0.0f)
			);

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