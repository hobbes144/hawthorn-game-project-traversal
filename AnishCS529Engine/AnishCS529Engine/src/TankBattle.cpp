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
#include "Shoot.h"

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
    KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE, KEY_ESCAPE,
    KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_ENTER,
    KEY_R
  };
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
  auto protag = createTank("protag", mainRenderer, camera, "media/TankPlayer1.png");
  protag->setLocalPosition(Vector3(-2.0f, 0.0f, 0.0f))->setLocalScaling(Vector3(1.0f,0.7f,1.0f));
  protag->addComponent<Movement>()->setInputSystem(mainInput);
  mainSceneGraph.addNode(protag);

  /* Enemy */
  auto enemy = createTank("enemy", mainRenderer, camera, "media/TankPlayer2.png");
  enemy->setLocalPosition(Vector3(2.0f, 0.0f, 0.0f))->setLocalScaling(Vector3(1.0f, 0.7f, 1.0f));
  enemy->addComponent<Movement>()->setInputSystem(mainInput)
    ->setUpKey(KEY_UP)->setDownKey(KEY_DOWN)
    ->setLeftKey(KEY_LEFT)->setRightKey(KEY_RIGHT);
  mainSceneGraph.addNode(enemy);

  /* Walls */
  Vector3 wallColor = Vector3(188.0f / 255.0f, 74.0f / 255.0f, 60.0f / 255.0f);
  auto wallLeft = createWall("leftWall", mainRenderer, camera, wallColor);
  wallLeft->setLocalPosition(Vector3(-7.5f, 0.0f, 0.0f))
    ->setLocalScaling(Vector3(1.0f, 10.0f, 0.0f));
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
  wallDown->setLocalPosition(Vector3(0.0f, -4.2f, 0.0f))
    ->setLocalScaling(Vector3(15.0f, 1.0f, 0.0f));
  mainSceneGraph.addNode(wallDown);

  /* Bullets */

  /* Protag bullets */
  std::vector<std::shared_ptr<Bullet>> pBullets;

  auto pBullet1 = createBullet("pBullet1", mainRenderer, camera, Vector3(0.25f, 0.25f, 1.0f));
  pBullet1->setOwner(protag)->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(pBullet1);
  pBullets.push_back(pBullet1);
  auto pBullet2 = createBullet("pBullet2", mainRenderer, camera, Vector3(0.25f, 0.25f, 1.0f));
  pBullet2->setOwner(protag)->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(pBullet2);
  pBullets.push_back(pBullet2);
  auto pBullet3 = createBullet("pBullet3", mainRenderer, camera, Vector3(0.25f, 0.25f, 1.0f));
  pBullet3->setOwner(protag)->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(pBullet3);
  pBullets.push_back(pBullet3);
  auto pBullet4 = createBullet("pBullet4", mainRenderer, camera, Vector3(0.25f, 0.25f, 1.0f));
  pBullet4->setOwner(protag)->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(pBullet4);
  pBullets.push_back(pBullet4);
  auto pBullet5 = createBullet("pBullet5", mainRenderer, camera, Vector3(0.25f, 0.25f, 1.0f));
  pBullet5->setOwner(protag)->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(pBullet5);
  pBullets.push_back(pBullet5);

  /* Enemy bullets */
  std::vector<std::shared_ptr<Bullet>> eBullets;

  auto eBullet1 = createBullet("eBullet1", mainRenderer, camera, Vector3(1.0f, 0.25f, 0.25f));
  eBullet1->setOwner(enemy)->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(eBullet1);
  eBullets.push_back(eBullet1);
  auto eBullet2 = createBullet("eBullet2", mainRenderer, camera, Vector3(1.0f, 0.25f, 0.25f));
  eBullet2->setOwner(enemy)->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(eBullet2);
  eBullets.push_back(eBullet2);
  auto eBullet3 = createBullet("eBullet3", mainRenderer, camera, Vector3(1.0f, 0.25f, 0.25f));
  eBullet3->setOwner(enemy)->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(eBullet3);
  eBullets.push_back(eBullet3);
  auto eBullet4 = createBullet("eBullet4", mainRenderer, camera, Vector3(1.0f, 0.25f, 0.25f));
  eBullet4->setOwner(enemy)->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(eBullet4);
  eBullets.push_back(eBullet4);
  auto eBullet5 = createBullet("eBullet5", mainRenderer, camera, Vector3(1.0f, 0.25f, 0.25f));
  eBullet5->setOwner(enemy)->setLocalPosition(Vector3(-100.0f, 0.0f, 0.0f));
  mainSceneGraph.addNode(eBullet5);
  eBullets.push_back(eBullet5);

  /* Setting up ability to shoot */
  protag->addComponent<Shoot>()
    ->setInputSystem(mainInput)->setBulletPool(pBullets);
  enemy->addComponent<Shoot>()
    ->setInputSystem(mainInput)->setBulletPool(eBullets)->setShootKey(KEY_ENTER);

  /* Events */
  // Todo: Convert CollisionListener to a component and move this to the
  // createBullet function.
  CollisionListener pBullet1Hit(pBullet1);
  pBullet1Hit.setCallback(onBulletHit);
  CollisionListener pBullet2Hit(pBullet2);
  pBullet2Hit.setCallback(onBulletHit);
  CollisionListener pBullet3Hit(pBullet3);
  pBullet3Hit.setCallback(onBulletHit);
  CollisionListener pBullet4Hit(pBullet4);
  pBullet4Hit.setCallback(onBulletHit);
  CollisionListener pBullet5Hit(pBullet5);
  pBullet5Hit.setCallback(onBulletHit);

  CollisionListener eBullet1Hit(eBullet1);
  eBullet1Hit.setCallback(onBulletHit);
  CollisionListener eBullet2Hit(eBullet2);
  eBullet2Hit.setCallback(onBulletHit);
  CollisionListener eBullet3Hit(eBullet3);
  eBullet3Hit.setCallback(onBulletHit);
  CollisionListener eBullet4Hit(eBullet4);
  eBullet4Hit.setCallback(onBulletHit);
  CollisionListener eBullet5Hit(eBullet5);
  eBullet5Hit.setCallback(onBulletHit);

  CollisionListener protagHit(protag);
  protagHit.setCallback(onTankHit);
  CollisionListener enemyHit(enemy);
  enemyHit.setCallback(onTankHit);

  /* End state */
  bool endStateReached = false;
  auto p1WinScreen = std::make_shared<GameObject>("p1Win");
  p1WinScreen->addComponent<Render2D>()
    ->setRenderer(mainRenderer)->setCamera(camera)
    ->setMaterial(createTextureMaterial("media/Player2Died.png"))
    ->setMesh(createSquareMesh("p1Win"));
  p1WinScreen->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f))
    ->setLocalScaling(Vector3(12.0f, 8.0f, 1.0f));
  p1WinScreen->disable();
  mainSceneGraph.addNode(p1WinScreen);

  auto p2WinScreen = std::make_shared<GameObject>("p2Win");
  p2WinScreen->addComponent<Render2D>()
    ->setRenderer(mainRenderer)->setCamera(camera)
    ->setMaterial(createTextureMaterial("media/Player1Died.png"))
    ->setMesh(createSquareMesh("p2Win"));
  p2WinScreen->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f))
    ->setLocalScaling(Vector3(12.0f, 8.0f, 1.0f));
  p2WinScreen->disable();
  mainSceneGraph.addNode(p2WinScreen);

  auto playerDrawScreen = std::make_shared<GameObject>("playerDraw");
  playerDrawScreen->addComponent<Render2D>()
    ->setRenderer(mainRenderer)->setCamera(camera)
    ->setMaterial(createTextureMaterial("media/Draw.png"))
    ->setMesh(createSquareMesh("playerDraw"));
  playerDrawScreen->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f))
    ->setLocalScaling(Vector3(12.0f, 8.0f, 1.0f));
  playerDrawScreen->disable();
  mainSceneGraph.addNode(playerDrawScreen);

  /* Main loop */
  while (!mainWindow->getShouldClose()) {
    mainRenderer->clear();
    mainInput->update();
    mainFramerateController->startFrame();

    mainSceneGraph.update(0.0f);

    while (mainFramerateController->shouldUpdatePhysics()) {
      PhysicsManager::Instance().update(mainFramerateController->getPhysicsTimestep());
      mainFramerateController->consumePhysicsTime();
    }

    if (mainInput->isKeyDown(KEY_ESCAPE)) mainWindow->setShouldClose();

    if (!endStateReached) {
      if (!protag->isEnabled() && !enemy->isEnabled()) {
        std::cout << "Draw!";
        playerDrawScreen->enable();
        endStateReached = true;
      }
      else if (!enemy->isEnabled()) {
        std::cout << "Player 1 wins!";
        p1WinScreen->enable();
        endStateReached = true;
      }
      else if (!protag->isEnabled()) {
        std::cout << "Player 2 wins!";
        p2WinScreen->enable();
        endStateReached = true;
      }
    }
    else {
      if (mainInput->isKeyPressed(KEY_R)) {
        playerDrawScreen->disable();
        p1WinScreen->disable();
        p2WinScreen->disable();

        protag->setLocalPosition(Vector3(-2.0f, 0.0f, 0.0f));
        protag->findComponent<PhysicsBody>()->reset();
        protag->enable();

        enemy->setLocalPosition(Vector3(2.0f, 0.0f, 0.0f));
        enemy->findComponent<PhysicsBody>()->reset();
        enemy->enable();
        endStateReached = false;
      }
    }

    mainFramerateController->endFrame();
    mainRenderer->swapBuffers();
    mainWindow->update();
  }

  mainInput->shutdown();
  mainRenderer->shutdown();
  mainWindow->shutdown();
}
