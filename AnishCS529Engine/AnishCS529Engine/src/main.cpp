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
#include "Node.h"
#include "Material.h"
#include "Mesh.h"
#include "RenderableNode.h"
#include "SceneGraph.h"

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

    auto shader = std::make_shared<Shader>("shaders/main_vertex_shader.glsl\nshaders/main_fragment_shader.glsl");

    auto material = std::make_shared<Material>(shader);

    SceneGraph scene = SceneGraph();

    Mesh::Attributes triangleMeshData;

    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    triangleMeshData[GeometryBuffer::AttributeType::Position] = {
      vertices,
      3
    };

    std::vector<float> colors = {
         1.0f,  0.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
         0.0f,  0.0f, 1.0f
    };
    triangleMeshData[GeometryBuffer::AttributeType::Color] = {
      colors,
      3
    };



    // auto buffer = GeometryBuffer::create(triangleBufferData, "triangle");
    // buffer->bind();

    auto mesh = std::make_shared<Mesh>(triangleMeshData, "Triangle");
    mesh->getGeometryBuffer()->bind();

    auto triangle = std::make_shared<RenderableNode>("triangle1", mesh, material, &renderer);
    auto triangle2 = std::make_shared<RenderableNode>("triangle2", mesh, material, &renderer);
    auto triangle3 = std::make_shared<RenderableNode>("triangle3", mesh, material, &renderer);
    auto triangle4 = std::make_shared<RenderableNode>("triangle4", mesh, material, &renderer);

    scene.addNode(triangle);
    triangle->addChild(triangle2);
    triangle2->addChild(triangle3);
    triangle3->addChild(triangle4);

    /*auto root = std::make_shared<Node>("root");
    auto node = std::make_shared<Node>("test");
    unsigned int nodeId = node->getID();

    std::cout << "Root node ID: " << root->getID() << std::endl;
    std::cout << "Child node ID: " << node->getID() << std::endl;

    root->addChild(node);
    auto foundNode = root->findNodeFast(nodeId);
    std::cout << "Found node ID: " << foundNode->getID() << std::endl;
    root->removeNode(node);*/

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

      /*Matrix4 modelMatrix = Matrix4::translation(0.0f, 0.0f, 0.0f) *
        Matrix4::rotationY(rotation) *
        Matrix4::scale(1.0f, 1.0f, 1.0f);
      Matrix4 modelMatrix2 = Matrix4::translation(1.0f, 0.0f, 0.0f) *
        Matrix4::rotationY(-rotation) *
        Matrix4::scale(1.0f, 1.0f, 1.0f);*/
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