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
#include "SceneGraph.h"
#include "TrianglePrimitive.h"

/** Pi constant for maths */
const float pi = 3.14159f;

/*!****************************************************************************
 * \brief Process key inputs
 * 	Currently only closes the window on pressing the Esc key.
 *
 * \param window Window in which the commands are read.
 *****************************************************************************/
void processInput(GameWindow& window)
{
  if (glfwGetKey(window.getNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    window.setShouldClose();
}

/*!****************************************************************************
 * \brief Shutdown GLFW Library
 *
 *****************************************************************************/
void shutdownLibraries()
{
  glfwTerminate();
}

// All the functions above would be better to be part of an object with that responsibility
// It's fine for now, but consider that. Could be the renderer, input, gameengine, etc.

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

    SceneGraph scene = SceneGraph();

    auto triangle = std::make_shared<TrianglePrimitive>("triangle1", &renderer);
    auto triangle2 = std::make_shared<TrianglePrimitive>("triangle2", &renderer);
    auto triangle3 = std::make_shared<TrianglePrimitive>("triangle3", &renderer);

    triangle->setColor({ 1.0f, 0.0f, 0.0f });
    triangle2->setColor({ 0.0f, 1.0f, 0.0f });
    triangle3->setColor({ 0.0f, 0.0f, 1.0f });

    scene.addNode(triangle);
    triangle->addChild(triangle2);
    triangle2->addChild(triangle3);

    /**
     * Main loop
     */
    while (!window.getShouldClose())
    {

      window.pollEvents();
      processInput(window);

      renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);

      float timeValue = glfwGetTime();
      float rotation = (float)glfwGetTime() * 50.0f * pi / 180;
      Matrix4 perspectiveMatrix = 
        Matrix4::perspective(
          45.0f * pi / 180, 
          (float)window.getWidth() / (float)window.getHeight(), 
          0.1f, 
          100.0f);
      Matrix4 orthographicMatrix = Matrix4::orthographic(
        -window.getWidth() / 2000.0f, window.getWidth() / 2000.0f, 
        -window.getHeight() / 2000.0f, window.getHeight() / 2000.0f, 
        0.1f, 100.0f);
      Matrix4 viewMatrix = 
        Matrix4::lookAt(
          Vector3(0.0f, 0.0f, 3.0f), 
          Vector3(), 
          Vector3(0.0f, 1.0f, 0.0f));

      triangle->setLocalPosition(Vector3(0.0f, 1.0f, 0.0f));
      triangle->setLocalScaling(Vector3(0.25f, 0.25f, 0.25f));
      triangle->setLocalRotation(Vector3(0.0f, rotation, 0.0f));
      triangle2->setLocalScaling(Vector3(1.5f, 1.5f, 1.5f));
      triangle2->setLocalPosition(Vector3(0.0f, -1.5f, 0.0f));
      triangle3->setLocalPosition(Vector3(0.0f, -1.5f, 0.0f));
      triangle3->setLocalScaling(Vector3(1.5f, 1.5f, 1.5f));
      scene.update(0.0f);
      scene.draw(viewMatrix, perspectiveMatrix);

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