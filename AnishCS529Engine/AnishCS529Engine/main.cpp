#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>

#include "GameWindow.h"
#include "Renderer.h"

const float pi = 3.14159f;

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

		/*const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";*/
		
		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec3 aColor;\n"
			"out vec3 ourColor;\n"
			"uniform mat4 modelMatrix;\n"
			"uniform mat4 viewMatrix;\n"
			"uniform mat4 perspectiveMatrix;\n"
			"uniform mat4 orthographicMatrix;\n"
			"void main()\n"
			"{\n"
			// "   gl_Position = vec4(aPos, 1.0);\n"
			// "   gl_Position = orthographicMatrix * modelMatrix * vec4(aPos, 1.0);\n"
			"	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
			"	ourColor = aColor;\n"
			"}\0";

		/*const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"uniform vec4 ourColor;\n"
			"void main()\n"
			"{\n"
			"	FragColor = ourColor\n"
			"}\0";*/

		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec3 ourColor;\n"
			"void main()\n"
			"{\n"
			"	FragColor = vec4(ourColor, 1.0);\n"
			"}\0";

		renderer.createVertexShader(vertexShaderSource);
		renderer.createFragmentShader(fragmentShaderSource);

		renderer.initializeShaders();
		triangleVaoId = renderer.addTriangle(
			Vector3(-0.5f, -0.5f, 0.0f), Vector3(1.0f, 0.0f, 0.0f),
			Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f),
			Vector3(0.0f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)
		);
		// int vertexColorLocation = glGetUniformLocation(renderer.getShaderProgramId(), "ourColor");

		while (!window.shouldClose())
		{

			window.pollEvents();
			processInput(window.getNativeWindow());
			
			renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);

			float timeValue = glfwGetTime();
			float rotation = (float)glfwGetTime() * 50.0f * pi / 180;
			/*float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
			glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); */

			renderer.UpdateTriangle(Matrix4::rotationY(rotation));
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