#include <windows.h>

#include "Renderer.h"
#include "GameWindow.h"
#include "Input.h"
#include "SceneGraph.h"
#include "Camera.h"
#include "RenderableNode.h"
#include "TrianglePrimitive.h"
#include "RectanglePrimitive.h"
#include "FramerateController.h"
#include "EventManager.h"
#include "GameObject.h"
#include "Render2D.h"

extern "C"
{
  __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main() {
//  /* Game Window setup */
//  float windowWidth = 1280.0f;
//  float windowHeight = 720.0f;
//  GameWindow* mainWindow = new GameWindow;
//  mainWindow->setTitle("RenderingTest")->setHeight(windowHeight)->setWidth(windowWidth);
//  mainWindow->initialize();
//
//  /* Renderer setup */
//  Renderer* mainRenderer = new Renderer;
//  mainRenderer->setGameWindow(mainWindow);
//  mainRenderer->initialize();
//  mainRenderer->setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//  mainWindow->setVsync(true);
//
//  /* Input setup */
//  Input* mainInput = new Input;
//  std::vector<Key> keysToMonitor = { 
//    KEY_W, KEY_A, KEY_S, KEY_D, KEY_R, KEY_F,
//    KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_ESCAPE
//  };
//  mainInput->setGameWindow(mainWindow);
//
//  /* Framerate controller setup */
//  FFramerateController* mainFramerateController = 
//    FFramerateController::getController();
//  
//  /* Scenegraph setup */
//  SceneGraph mainSceneGraph;
//
//  /* Camera setup */
//  Vector3 cameraPos(-20.0f, 20.0f, 500.0);
//  Vector3 cameraTarget = cameraPos + Vector3(0.0f, 0.0f, -500.0f);
//  Vector3 upVector(0.0f, 1.0f, 0.0f);
//  auto camera = std::make_shared<Camera>("mainCamera");
//  camera->setLocalPosition(Vector3(cameraPos));
//  camera
//    ->setPerspectiveProjection(
//      45.0f * 3.14159f / 180.0f,
//      mainWindow->getAspectRatio(),
//      0.1f,
//      1000.0f)
//    ->lookAt(cameraTarget, upVector);
//  mainSceneGraph.addNode(camera);
//
//  /* Create relevant Meshes*/
//  auto boxMesh = createCubeMesh("box");
//  auto boxMaterial = createSolidColorMaterial(Vector3(1.0f,0.8f,0.8f));
//
//// Drawable objects
//  auto box1 = std::make_shared<GameObject>("Box1");
//  box1->setLocalPosition(Vector3(0.25f, 0.0f, 0.0f))
//    ->setLocalScaling(Vector3(100.0f, 100.f, 100.0f));
//  // Todo: when z is set to 1.0f, the bounding box debug gets very messed up.
//
//  auto box1RenderComponent = box1->addComponent<Render2D>();
//  box1RenderComponent
//    ->setRenderer(mainRenderer)
//    ->setCamera(camera)
//    ->setMesh(boxMesh)
//    ->setMaterial(boxMaterial);
//
//  auto box2 = std::make_shared<GameObject>("Box2");
//  box1->setLocalPosition(Vector3(-0.25f, 0.0f, 0.0f))
//    ->setLocalScaling(Vector3(100.0f, 100.f, 100.0f));
//
//  auto box2RenderComponent = box2->addComponent<Render2D>();
//  box2RenderComponent
//    ->setRenderer(mainRenderer)
//    ->setCamera(camera)
//    ->setMesh(boxMesh)
//    ->setMaterial(boxMaterial);
//
//  mainSceneGraph.addNode(box1);
//  mainSceneGraph.addNode(box2);
//
//  float angleX = 0.0f;
//  float angleY = 0.0f;
//  float angleZ = 0.0f;
//  float speed = 10.0f;
//  float deltaTime = 0.0f;
//  int expectedFrameRate = 60; // 1000;
//  mainFramerateController->setTargetFramerate(expectedFrameRate);
//  mainSceneGraph.printSceneTree();
//
//  while (!window.getShouldClose()) {
//    //std::cout << "\nloop restart at time " << framerateController->getTime() << "\n\n";
//
//    mainRenderer->clear();
//    mainFramerateController->startFrame();              // record the time from frame start
//
//
//    // Input for box1
//    Vector3 velocity(0.0f, 0.0f, 0.0f);
//    if (mainInput->isKeyHeld(KEY_D))
//      camera->setLocalPosition(
//        camera->getLocalPosition() + Vector3(0.0f,0.1f,00.0f));
//    if (mainInput->isKeyHeld(KEY_A))
//      camera->setLocalPosition(
//        camera->getLocalPosition() + 0.1f);
//    if (mainInput->isKeyHeld(KEY_W))
//      velocity.y = speed;
//    if (mainInput->isKeyHeld(KEY_S))
//      velocity.y = -speed;
//    if (mainInput->isKeyHeld(KEY_UP))
//      velocity.z = speed;
//    if (mainInput->isKeyHeld(KEY_DOWN))
//      velocity.z = -speed;
//    body1->setVelocity(velocity);
//
//    if (input.isKeyHeld(KEY_LEFT))
//      box1->setLocalRotation(Vector3(angleX, angleY, (angleZ -= 0.01f)));
//    if (input.isKeyHeld(KEY_RIGHT))
//      box1->setLocalRotation(Vector3(angleX, angleY, (angleZ += 0.01f)));
//    if (input.isKeyHeld(KEY_Q))
//      box1->setLocalRotation(Vector3((angleX -= 0.01f), angleY, angleZ));
//    if (input.isKeyHeld(KEY_E))
//      box1->setLocalRotation(Vector3((angleX += 0.01f), angleY, angleZ));
//    if (input.isKeyHeld(KEY_R))
//      box1->setLocalRotation(Vector3(angleX, (angleY -= 0.01f), angleZ));
//    if (input.isKeyHeld(KEY_F))
//      box1->setLocalRotation(Vector3(angleX, (angleY += 0.01f), angleZ));
//
//
//
//    // Physics update deltaTime
//    //objectDelta.Update(deltaTime);
//
//    //// Physics update loop fixedStepTime
//    //while (framerateController->ShouldUpdatePhysics()) {
//    //    PhysicsManager::Instance().update(FramerateController::DEFAULT_FIXED_TIME_STEP);
//    //    framerateController->ConsumePhysicsTime();
//    //}
//    PhysicsManager::Instance().update(deltaTime);
//
//    input.update();
//    if (input.isKeyHeld(KEY_ESCAPE))
//      break;
//
//    sceneGraph.update(deltaTime);
//
//    // draw debug lines for all bodies
//    // In your render loop, after sceneGraph.draw:
//    //std::cout << "Number of physics bodies: " << PhysicsManager::Instance().getBodies().size() << "\n";
//    for (auto body : PhysicsManager::Instance().getBodies()) {
//      if (auto obb = dynamic_cast<OBB*>(body->getShape())) {
//        //std::cout << "Drawing OBB at position: " << body->getOwner()->getLocalPosition().x
//        //    << ", " << body->getOwner()->getLocalPosition().y << "\n";
//        obb->drawDebugLines(viewMatrix, projectionMatrix);
//      }
//      if (auto aabb = dynamic_cast<AABB*>(body->getShape())) {
//        //std::cout << "Drawing OBB at position: " << body->getOwner()->getLocalPosition().x
//        //    << ", " << body->getOwner()->getLocalPosition().y << "\n";
//        aabb->drawDebugLines(viewMatrix, projectionMatrix);
//      }
//    }
//
//
//    sceneGraph.draw(viewMatrix, projectionMatrix);
//
//    //std::cout << "Angle for box1: " << angle << std::endl;
//    //std::cout << "========================" << std::endl;
//    renderer.swapBuffers();
//    window.pollEvents();
//
//    framerateController->endFrame();
//    deltaTime = framerateController->getFrameTime();
//
//  }

  return 0;
}
