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
#include "BasicRenderPass.h"
#include "TextureMaterial.h"

extern "C"
{
  __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main() {
  /* Game Window setup */
  int windowWidth = 1280;
  int windowHeight = 720;
  GameWindow* mainWindow = new GameWindow;
  mainWindow->setTitle("RenderingTest")->setHeight(windowHeight)->setWidth(windowWidth);
  mainWindow->initialize();

  /* Renderer setup */
  Renderer* mainRenderer = new Renderer;
  mainRenderer->setGameWindow(mainWindow);
  mainRenderer->initialize();
  mainRenderer->setClearColor(0.05f, 0.05f, 0.1f, 1.0f);

  mainRenderer->getRenderGraph()->addPass<BasicRenderPass>("DirectRenderPass");

  //mainWindow->setVsync(true);

  /* Input setup */
  Input* mainInput = new Input;
  std::vector<Key> keysToMonitor = { 
    KEY_W, KEY_A, KEY_S, KEY_D, KEY_R, KEY_F,
    KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_ESCAPE
  };
  mainInput->setGameWindow(mainWindow);

  /* Framerate controller setup */
  FFramerateController* mainFramerateController = 
    FFramerateController::getController();
  
  /* Scenegraph setup */
  SceneGraph mainSceneGraph;

  /* Camera setup */
  Vector3 cameraPos(0.0f, 0.0f, 10.0f);
  auto camera = std::make_shared<Camera>("mainCamera");
  camera->setPerspectiveProjection(
    45.0f * 3.14159f / 180.0f,
    mainWindow->getAspectRatio(),
    0.1f,
    1000.0f)->setLocalPosition(Vector3(0.0f, 0.0f, 10.0f));
  mainSceneGraph.addNode(camera);

  /* Create relevant Meshes*/
  auto boxMesh = Mesh::createMesh("box", Mesh::Square);
  auto boxMaterial = Material::getMaterial<TextureMaterial>("box", mainRenderer->getRenderGraph());

// Drawable objects
  auto box1 = std::make_shared<GameObject>("Box1");
  box1->setLocalPosition(Vector3(2.0f, 0.0f, 0.0f))
    ->setLocalScaling(Vector3(1.0f, 1.f, 1.0f));
  // Todo: when z is set to 1.0f, the bounding box debug gets very messed up.

  auto box1RenderComponent = box1->addComponent<Render2D>();
  box1RenderComponent
    ->setCamera(camera)
    ->setMesh(boxMesh)
    ->setMaterial(boxMaterial);

  auto box2 = std::make_shared<GameObject>("Box2");
  box1->setLocalPosition(Vector3(-2.0f, 0.0f, 0.0f))
    ->setLocalScaling(Vector3(1.0f, 1.f, 1.0f));

  auto box2RenderComponent = box2->addComponent<Render2D>();
  box2RenderComponent
    ->setCamera(camera)
    ->setMesh(boxMesh)
    ->setMaterial(boxMaterial);

  mainSceneGraph.addNode(box1);
  mainSceneGraph.addNode(box2);

  float angleX = 0.0f;
  float angleY = 0.0f;
  float angleZ = 0.0f;
  float speed = 10.0f;
  float deltaTime = 0.0f;
  int expectedFrameRate = 60; // 1000;
  mainFramerateController->setTargetFramerate(expectedFrameRate);
  mainSceneGraph.printSceneTree();

  while (!mainWindow->getShouldClose()) {
    //std::cout << "\nloop restart at time " << framerateController->getTime() << "\n\n";

    mainRenderer->clear();
    mainFramerateController->startFrame();              // record the time from frame start

    if (mainInput->isKeyHeld(KEY_LEFT))
      box1->setLocalRotation(Vector3(angleX, angleY, (angleZ -= 0.01f)));
    if (mainInput->isKeyHeld(KEY_RIGHT))
      box1->setLocalRotation(Vector3(angleX, angleY, (angleZ += 0.01f)));
    if (mainInput->isKeyHeld(KEY_Q))
      box1->setLocalRotation(Vector3((angleX -= 0.01f), angleY, angleZ));
    if (mainInput->isKeyHeld(KEY_E))
      box1->setLocalRotation(Vector3((angleX += 0.01f), angleY, angleZ));
    if (mainInput->isKeyHeld(KEY_R))
      box1->setLocalRotation(Vector3(angleX, (angleY -= 0.01f), angleZ));
    if (mainInput->isKeyHeld(KEY_F))
      box1->setLocalRotation(Vector3(angleX, (angleY += 0.01f), angleZ));
    if (mainInput->isKeyHeld(KEY_W))
      box1->setLocalPosition(box1->getLocalPosition() + Vector3(0.0f, deltaTime * 10.0f, 0.0f));
    if (mainInput->isKeyHeld(KEY_A))
      box1->setLocalPosition(box1->getLocalPosition() - Vector3(deltaTime * 10.0f, 0.0f, 0.0f));
    if (mainInput->isKeyHeld(KEY_S))
      box1->setLocalPosition(box1->getLocalPosition() - Vector3(0.0f, deltaTime * 10.0f, 0.0f));
    if (mainInput->isKeyHeld(KEY_D))
      box1->setLocalPosition(box1->getLocalPosition() + Vector3(deltaTime * 10.0f, 0.0f, 0.0f));
    if (mainInput->isKeyHeld(KEY_UP))
      box1->setLocalPosition(box1->getLocalPosition() + Vector3(0.0f, 0.0f, deltaTime * 10.0f));
    if (mainInput->isKeyHeld(KEY_DOWN))
      box1->setLocalPosition(box1->getLocalPosition() - Vector3(0.0f, 0.0f, deltaTime * 10.0f));



    // Physics update deltaTime
    //objectDelta.Update(deltaTime);

    //// Physics update loop fixedStepTime
    //while (framerateController->ShouldUpdatePhysics()) {
    //    PhysicsManager::Instance().update(FramerateController::DEFAULT_FIXED_TIME_STEP);
    //    framerateController->ConsumePhysicsTime();
    //}
    //PhysicsManager::Instance().update(deltaTime);

    mainInput->update();
    if (mainInput->isKeyHeld(KEY_ESCAPE))
      break;

    mainSceneGraph.update(deltaTime);

    // draw debug lines for all bodies
    // In your render loop, after sceneGraph.draw:
    //std::cout << "Number of physics bodies: " << PhysicsManager::Instance().getBodies().size() << "\n";
    //for (auto body : PhysicsManager::Instance().getBodies()) {
    //  if (auto obb = dynamic_cast<OBB*>(body->getShape())) {
    //    //std::cout << "Drawing OBB at position: " << body->getOwner()->getLocalPosition().x
    //    //    << ", " << body->getOwner()->getLocalPosition().y << "\n";
    //    obb->drawDebugLines(viewMatrix, projectionMatrix);
    //  }
    //  if (auto aabb = dynamic_cast<AABB*>(body->getShape())) {
    //    //std::cout << "Drawing OBB at position: " << body->getOwner()->getLocalPosition().x
    //    //    << ", " << body->getOwner()->getLocalPosition().y << "\n";
    //    aabb->drawDebugLines(viewMatrix, projectionMatrix);
    //  }
    //}

    //std::cout << "Angle for box1: " << angle << std::endl;
    //std::cout << "========================" << std::endl;
    deltaTime = mainFramerateController->getFrameTime();

    mainFramerateController->endFrame();
    mainRenderer->swapBuffers();
    mainWindow->update();

    //glfwSwapBuffers(window);

  }

  
  mainInput->shutdown();
  mainRenderer->shutdown();
  mainWindow->shutdown();

  return 0;
}
