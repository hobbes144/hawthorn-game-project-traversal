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
#include "PhysicsBody.h"
#include "Render2D.h"
#include "Renderer.h"
#include "SceneGraph.h"

int main() {
  const std::string GameTitle = "SphereJump";

  /* Game Window setup */
  float windowWidth = 1280.0f;
  float windowHeight = 720.0f;
  GameWindow* mainWindow = new GameWindow;
  mainWindow->setTitle(GameTitle)->setHeight(windowHeight)->setWidth(windowWidth);
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
    (windowWidth / windowHeight),
    0.1f,
    1000.0f)->setLocalPosition(Vector3(0.0f, 0.0f, 10.0f));
  mainSceneGraph.addNode(camera);


  /* GameObject setup */
  auto protag = std::make_shared<GameObject>("protag");
  protag->addComponent<Render2D>()
    ->setRenderer(mainRenderer)->setCamera(camera)
    ->setMaterial(createSolidColorMaterial(Vector3(0.25f, 0.25f, 1.0f)))
    ->setMesh(createSquareMesh("protag"));
  protag->setLocalPosition(Vector3(1.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(protag);
  protag->addComponent<PhysicsBody>()
    ->setMass(10.0f)->setFriction(100.0f);

  auto enemy = std::make_shared<GameObject>("enemy1");
  enemy->addComponent<Render2D>()
    ->setRenderer(mainRenderer)->setCamera(camera)
    ->setMaterial(createSolidColorMaterial(Vector3(1.0f, 0.25f, 0.25f)))
    ->setMesh(createSquareMesh("enemy"));
  enemy->setLocalPosition(Vector3(-1.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(enemy);
  enemy->addComponent<PhysicsBody>()
    ->setMass(10.0f);

  /* Main loop */
  while (!mainWindow->getShouldClose()) {
    mainRenderer->clear();
    mainInput->update();
    mainFramerateController->startFrame();

    mainSceneGraph.update(0.0f);

    if (mainInput->isKeyDown(KEY_W)) {
      protag->findComponent<PhysicsBody>()
        ->applyForce(Vector3(0.0f, 1000.0f, 0.0f));
    }

    while (mainFramerateController->shouldUpdatePhysics()) {
      protag->findComponent<PhysicsBody>()->integrate(mainFramerateController->getPhysicsTimestep());
      mainFramerateController->consumePhysicsTime();
    }

    if (mainInput->isKeyDown(KEY_ESCAPE)) mainWindow->setShouldClose();

    mainFramerateController->endFrame();
    mainRenderer->swapBuffers();
    mainWindow->update();
  }

  mainInput->shutdown();
  mainRenderer->shutdown();
  mainWindow->shutdown();
}
