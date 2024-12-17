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

#include "AABB.h"
#include "Camera.h"
#include "CollisionListener.h"
#include "EventManager.h"
#include "FramerateController.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Input.h"
#include "PhysicsBody.h"
#include "PhysicsManager.h"
#include "Render2D.h"
#include "Renderer.h"
#include "SceneGraph.h"

#include "Bullet.h"
#include "Movement.h"
#include "Tank.h"
#include "Wall.h"

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
  mainRenderer->setClearColor(0.0f, 0.0f, 0.0f, 1.0f)->setIs3D(true);

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
  /* Protagonist */
  auto protag = createTank("protag", mainRenderer, camera, Vector3(0.25f, 0.25f, 1.0f));
  protag->setLocalPosition(Vector3(1.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(protag);

  /* Enemy */
  auto enemy = createTank("enemy", mainRenderer, camera, Vector3(1.0f, 0.25f, 0.25f));
  enemy->setLocalPosition(Vector3(-1.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(enemy);

  /* Bullets */

  /* Protag bullets */
  std::vector<std::shared_ptr<Bullet>> pBullets;

  auto pBullet1 = createBullet("pBullet1", mainRenderer, camera, Vector3(0.25f, 0.25f, 1.0f));
  pBullet1->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(pBullet1);
  pBullets.push_back(pBullet1);
  auto pBullet2 = createBullet("pBullet2", mainRenderer, camera, Vector3(0.25f, 0.25f, 1.0f));
  pBullet2->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(pBullet2);
  pBullets.push_back(pBullet2);
  auto pBullet3 = createBullet("pBullet3", mainRenderer, camera, Vector3(0.25f, 0.25f, 1.0f));
  pBullet3->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(pBullet3);
  pBullets.push_back(pBullet3);
  auto pBullet4 = createBullet("pBullet4", mainRenderer, camera, Vector3(0.25f, 0.25f, 1.0f));
  pBullet4->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(pBullet4);
  pBullets.push_back(pBullet4);
  auto pBullet5 = createBullet("pBullet5", mainRenderer, camera, Vector3(0.25f, 0.25f, 1.0f));
  pBullet5->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(pBullet5);
  pBullets.push_back(pBullet5);

  /* Walls */
  Vector3 wallColor = Vector3(188.0f / 255.0f, 74.0f / 255.0f, 60.0f / 255.0f);
  auto wallLeft = createWall("leftWall", mainRenderer, camera, wallColor);
  wallLeft->setLocalPosition(Vector3(-7.5f, 0.0f, 0.0f))
    ->setLocalScaling(Vector3(1.0f,10.0f,0.0f));
  mainSceneGraph.addNode(wallLeft);
  auto wallRight = createWall("rightWall", mainRenderer, camera, wallColor);
  wallRight->setLocalPosition(Vector3(7.5f, 0.0f, 0.0f))
    ->setLocalScaling(Vector3(1.0f, 10.0f, 0.0f));
  mainSceneGraph.addNode(wallRight);
  auto wallUp = createWall("upWall", mainRenderer, camera, wallColor);
  wallUp->setLocalPosition(Vector3(0.0f, 4.2f, 0.0f))
    ->setLocalScaling(Vector3(15.0f, 1.0f, 0.0f));
  mainSceneGraph.addNode(wallUp);
  auto wallDown = createWall("downWall", mainRenderer, camera, wallColor);
  wallDown->setLocalPosition(Vector3(0.0f, 4.2f, 0.0f))
    ->setLocalScaling(Vector3(15.0f, 1.0f, 0.0f));
  mainSceneGraph.addNode(wallDown);

  /* Enemy bullets */
  std::vector<std::shared_ptr<Bullet>> eBullets;

  auto eBullet1 = createBullet("eBullet1", mainRenderer, camera, Vector3(1.0f, 0.25f, 0.25f));
  eBullet1->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(eBullet1);
  eBullets.push_back(eBullet1);
  auto eBullet2 = createBullet("eBullet2", mainRenderer, camera, Vector3(1.0f, 0.25f, 0.25f));
  eBullet2->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(eBullet2);
  eBullets.push_back(eBullet2);
  auto eBullet3 = createBullet("eBullet3", mainRenderer, camera, Vector3(1.0f, 0.25f, 0.25f));
  eBullet3->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(eBullet3);
  eBullets.push_back(eBullet3);
  auto eBullet4 = createBullet("eBullet4", mainRenderer, camera, Vector3(1.0f, 0.25f, 0.25f));
  eBullet4->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(eBullet4);
  eBullets.push_back(eBullet4);
  auto eBullet5 = createBullet("eBullet5", mainRenderer, camera, Vector3(1.0f, 0.25f, 0.25f));
  eBullet5->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(eBullet5);
  eBullets.push_back(eBullet5);

  /* Events */
  CollisionListener protagHit(protag);
  CollisionListener enemyHit(enemy);
  EventManager::Instance().AddListener(&protagHit);

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
    
    if (mainInput->isKeyDown(KEY_S)) {
      protag->findComponent<PhysicsBody>()
        ->applyForce(Vector3(0.0f, -1000.0f, 0.0f));
    }

    if (mainInput->isKeyDown(KEY_A)) {
      protag->findComponent<PhysicsBody>()
        ->applyForce(Vector3(-1000.0f, 0.0f, 0.0f));
    }

    if (mainInput->isKeyDown(KEY_D)) {
      protag->findComponent<PhysicsBody>()
        ->applyForce(Vector3(1000.0f, 0.0f, 0.0f));
    }

    if (mainInput->isKeyDown(KEY_SPACE)) {

    }

    while (mainFramerateController->shouldUpdatePhysics()) {
      PhysicsManager::Instance().update(mainFramerateController->getPhysicsTimestep());
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
