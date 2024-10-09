/*!****************************************************************************
 * \file main.cpp
 * \author Anish Murthy
 * \par **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par **Course**
 *    CS529
 * \version 0.1
 * \date 10-05-2024
 * \brief Main logic controller for the Engine
 *
 *****************************************************************************/
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "GameWindow.h"
#include "Renderer.h"

/** Pi constant for maths */
const float pi = 3.14159f;

/*!****************************************************************************
 * \brief Process key inputs
 * 	Currently only closes the window on pressing the Esc key.
 *
 * \param window Window in which the commands are read.
 *****************************************************************************/
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

/*!****************************************************************************
 * \brief Swap window buffers
 *
 * \param window Window whose buffers should be swapped.
 *****************************************************************************/
void swapBuffers(GLFWwindow *window)
{
  glfwSwapBuffers(window);
}

/*!****************************************************************************
 * \brief Shutdown GLFW Library
 *
 *****************************************************************************/
void shutdownLibraries()
{
  glfwTerminate();
}

/*!****************************************************************************
 * \brief Main logic function
 *
 * \return \b int 0 on Success, 1 on failure.
 *****************************************************************************/
int main(void)
{

  try
  {
    GameWindow window(800, 600, "Assignment 2");
    Renderer renderer(window);
    unsigned int triangleVaoId;

    /*const char* vertexShaderSource = "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";*/

    const char *vertexShaderSource = 
      "#version 330 core\n"
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
      // "   gl_Position = orthographicMatrix * modelMatrix * "
      " vec4(aPos, 1.0);\n"
      " gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * "
      "  vec4(aPos, 1.0);\n"
      " ourColor = aColor;\n"
      "}\0";

    /*const char* fragmentShaderSource = "#version 330 core\n"
      "out vec4 FragColor;\n"
      "uniform vec4 ourColor;\n"
      "void main()\n"
      "{\n"
      "	FragColor = ourColor\n"
      "}\0";*/

    const char *fragmentShaderSource = 
      "#version 330 core\n"
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
      Vector3(0.5f, -0.5f, 0.0f), Vector3(1.0f, 0.0f, 0.0f),
      Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f),
      Vector3(0.0f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
    // int vertexColorLocation = glGetUniformLocation(
    //	renderer.getShaderProgramId(), "ourColor");

    /**
     * Main loop
     */
    while (!window.shouldClose())
    {

      window.pollEvents();
      processInput(window.getNativeWindow());

      renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);

      float timeValue = glfwGetTime();
      float rotation = (float)glfwGetTime() * 50.0f * pi / 180;
      /*float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
      glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); */

      renderer.UpdateTriangle(Matrix4::translation(0.0f, 0.0f, 0.0f) *
                              Matrix4::rotationZ(rotation) *
                              Matrix4::scale(1.0f, 1.0f, 1.0f));
      renderer.drawTriangle(triangleVaoId);

      /*renderer.drawTriangle(
        Vector3(-0.5f, -0.5f, 0.0f),
        Vector3(0.5f, -0.5f, 0.0f),
        Vector3(0.0f, 0.5f, 0.0f)
      );*/

      renderer.swapBuffers();
    }
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
    glfwTerminate();
    return 1;
  }

  shutdownLibraries();
  return 0;
}