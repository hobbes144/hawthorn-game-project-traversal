/*!****************************************************************************
 * \file   main.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-05-2024
 * \brief  Main logic controller for the Engine
 * 
 *****************************************************************************/
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "GameWindow.h"
#include "Renderer.h"
#include "Shader.h"
#include "GeometryBuffer.h"

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

    Shader shader("shaders/main_vertex_shader.glsl\nshaders/main_fragment_shader.glsl");

    shader.use();

    std::unordered_map<GeometryBuffer::AttributeType, GeometryBuffer::AttributeInfo> triangleBufferData;

    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    triangleBufferData[GeometryBuffer::AttributeType::Position] = {
      vertices,
      3,
      GL_FLOAT,
      GL_FALSE
    };

    std::vector<float> colors = {
         1.0f,  0.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
         0.0f,  0.0f, 1.0f
    };
    triangleBufferData[GeometryBuffer::AttributeType::Color] = {
      colors,
      3,
      GL_FLOAT,
      GL_FALSE
    };


    auto buffer = GeometryBuffer::create(triangleBufferData, "triangle");
    buffer->bind();

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
      shader.setMat4("viewMatrix", Matrix4::lookAt(Vector3(0.0f, 0.0f, 3.0f), Vector3(), Vector3(0.0f, 1.0f, 0.0f)));
      shader.setMat4("perspectiveMatrix", Matrix4::perspective(45.0f * pi / 180, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f));
      shader.setMat4("modelMatrix", Matrix4::translation(0.0f, 0.0f, 0.0f) *
        Matrix4::rotationZ(rotation) *
        Matrix4::scale(1.0f, 1.0f, 1.0f));

      renderer.drawTriangle(buffer->getVAO());

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