/*!****************************************************************************
 * \file   SphereJump.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-15-2024
 * \brief  Test main for a simple game for final grade
 * 
 *****************************************************************************/

#include "Camera.h"
#include "FramerateController.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Input.h"
#include "Render2D.h"
#include "Renderer.h"
#include "SceneGraph.h"

int main() {
  const std::string GameTitle = "SphereJump";

  /* Game Window setup */
  GameWindow* mainWindow = new GameWindow;
  mainWindow->setTitle(GameTitle)->setHeight(720)->setWidth(1280);
  mainWindow->initialize();

  /* Renderer setup */
  Renderer* mainRenderer = new Renderer;
  mainRenderer->setGameWindow(mainWindow);
  mainRenderer->initialize();
  mainRenderer->setClearColor(0.0, 0.0, 0.0, 1.0)->setIs3D(true);

  mainWindow->setVsync(true);

  /* Input setup */
  Input* mainInput = new Input;
  std::vector<Key> keysToMonitor = { 
    KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE, KEY_ESCAPE };
  mainInput->setGameWindow(mainWindow);

  /* Framerate controller setup */
  FFramerateController* mainFramerateController = 
    FFramerateController::getController();
  
  /* Scenegraph setup */
  SceneGraph mainSceneGraph;

  /* Camera setup */
  auto camera = std::make_shared<Camera>("mainCamera");
  camera->setPerspectiveProjection(
    45.0f * 3.14159f / 180.0f,
    (800.0f / 600.0f),
    0.1f,
    1000.0f)->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(camera);

  /* Create required meshes and materials */
  auto protagMesh = createSquareMesh("protag");
  auto protagMaterial = createSolidColorMaterial(Vector3(0.5f,0.5f,0.5f));

  /* GameObject setup */
  auto protag = std::make_shared<GameObject>("protag");
  auto protagRender = protag->addComponent<Render2D>();
  protagRender->setRenderer(mainRenderer)->setCamera(camera);
  protag->setLocalPosition(Vector3(0.25f, 0.0f, 0.0f));

  mainSceneGraph.addNode(protag);

  while (!mainWindow->getShouldClose()) {
    mainRenderer->clear();
    mainInput->update();

    std::cout << camera->getViewMatrix();
    mainSceneGraph.update(0.0f);

    std::cout << "W: " << mainInput->isKeyDown(KEY_W) << std::endl;

    if (mainInput->isKeyDown(KEY_ESCAPE)) mainWindow->setShouldClose();

    mainRenderer->swapBuffers();
    mainWindow->update();
  }

  camera->update(0.0f);
  std::cout << camera->getViewMatrix() << camera->getProjectionMatrix();

  mainInput->shutdown();
  mainRenderer->shutdown();
  mainWindow->shutdown();
}
