#include <windows.h>

#include "Renderer.h"
#include "GameWindow.h"
#include "Input.h"
#include "SceneGraph.h"
#include "RenderableNode.h"
#include "TrianglePrimitive.h"
#include "RectanglePrimitive.h"
#include "FramerateController.h"
#include "EventManager.h"
#include "GameObject.h"
#include "PhysicsBody.h"
#include "AABB.h"
#include "OBB.h"
#include "Sphere.h"
#include "PhysicsManager.h"

extern "C"
{
  __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main() {
  // Create window, renderer and input systems
  GameWindow window(800, 600, "2D Example");
  Renderer renderer(window);
  renderer.enableDepth(true);
  Input input(window);
  FFramerateController* framerateController = FFramerateController::getController();

  // Create scene graph
  SceneGraph sceneGraph;

  // Set up camera (view and projection matrices)
  Vector3 cameraPos(-20.0f, 20.0f, 500.0);
  Vector3 cameraTarget = cameraPos + Vector3(0.0f, 0.0f, -500.0f);
  Vector3 upVector(0.0f, 1.0f, 0.0f);
  Matrix4 viewMatrix = Matrix4::lookAt(cameraPos, cameraTarget, upVector);
  float aspectRatio = 
    static_cast<float>(window.getWidth()) / window.getHeight();
  float bottom = -window.getWidth() * 0.5f;
  float top = window.getHeight() * 0.5f;
  float left = -window.getWidth() * 0.5f;
  float right = window.getWidth() * 0.5f;
  Matrix4 projectionMatrix =
    Matrix4::perspective(45.0f * 3.14159f / 180.0f, (800.0f / 600.0f), 0.1f, 1000.0f);
    //Matrix4::orthographic(left, right, bottom, top, 0.1f, 1000.0f);

  // Drawable objects
  auto box1 = std::make_shared<GameObject>("Icon1", &renderer);
  box1->setLocalPosition(Vector3(0.25f, 0.0f, 0.0f));
  box1->setLocalScaling(Vector3(100.0f, 100.f, 100.0f));
  // Todo: when z is set to 1.0f, the bounding box debug gets very messed up.

  auto box2 = std::make_shared<GameObject>("Icon2", &renderer);
  box2->setLocalPosition(Vector3(0.75f, 0.0f, 0.0f));
  box2->setLocalScaling(Vector3(100.0f, 100.f, 100.0f));

  sceneGraph.addNode(box1);
  sceneGraph.addNode(box2);

  // Create instances of bodies for boxes
  auto body1 = std::make_unique<PhysicsBody>(box1.get());
  auto body2 = std::make_unique<PhysicsBody>(box2.get());

  // Create OBBs
  auto shape1 = std::make_shared<OBB>(
      Vector3(-0.0f, -0.0f, 0.0f),  // half width/height of 50 for 100x100 box
      Vector3(0.5f, 0.5f, 0.5f));
  // Todo: When Z scale is set to 0, the box no longer follows the object in
  // the Z axis.
  auto shape2 = std::make_shared<OBB>(
      Vector3(-0.0f, -0.0f, 0.0f),  // half width/height of 50 for 100x100 box
      Vector3(0.5f, 0.5f, 0.5f));
  //auto shape2 = std::make_shared<AABB>(
  //    Vector3(-0.5f, -0.5f, -0.5f),  // half width/height of 50 for 100x100 box
  //    Vector3(0.5f, 0.5f, 0.5f));
  shape1->initializeDebugDraw(&renderer);
  shape2->initializeDebugDraw(&renderer);

  // Create AABB shapes
  body1->setShape(shape1);
  body2->setShape(shape2);

  // Add bodies to physics system
  PhysicsManager::Instance().addBody(body1.get());
  PhysicsManager::Instance().addBody(body2.get());


  float angleX = 0.0f;
  float angleY = 0.0f;
  float angleZ = 0.0f;
  float speed = 10.0f;
  float deltaTime = 0.0f;
  int expectedFrameRate = 60; // 1000;
  framerateController->setTargetFramerate(expectedFrameRate);
  sceneGraph.printSceneTree();

  while (!window.getShouldClose()) {
    //std::cout << "\nloop restart at time " << framerateController->getTime() << "\n\n";

    renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);
    framerateController->startFrame();              // record the time from frame start


    // Input for box1
    Vector3 velocity(0.0f, 0.0f, 0.0f);
    if (input.isKeyHeld(KEY_D))
      velocity.x = speed;
    if (input.isKeyHeld(KEY_A))
      velocity.x = -speed;
    if (input.isKeyHeld(KEY_W))
      velocity.y = speed;
    if (input.isKeyHeld(KEY_S))
      velocity.y = -speed;
    if (input.isKeyHeld(KEY_UP))
      velocity.z = speed;
    if (input.isKeyHeld(KEY_DOWN))
      velocity.z = -speed;
    body1->setVelocity(velocity);

    if (input.isKeyHeld(KEY_LEFT))
      box1->setLocalRotation(Vector3(angleX, angleY, (angleZ -= 0.01f)));
    if (input.isKeyHeld(KEY_RIGHT))
      box1->setLocalRotation(Vector3(angleX, angleY, (angleZ += 0.01f)));
    if (input.isKeyHeld(KEY_Q))
      box1->setLocalRotation(Vector3((angleX -= 0.01f), angleY, angleZ));
    if (input.isKeyHeld(KEY_E))
      box1->setLocalRotation(Vector3((angleX += 0.01f), angleY, angleZ));
    if (input.isKeyHeld(KEY_R))
      box1->setLocalRotation(Vector3(angleX, (angleY -= 0.01f), angleZ));
    if (input.isKeyHeld(KEY_F))
      box1->setLocalRotation(Vector3(angleX, (angleY += 0.01f), angleZ));



    // Physics update deltaTime
    //objectDelta.Update(deltaTime);

    //// Physics update loop fixedStepTime
    //while (framerateController->ShouldUpdatePhysics()) {
    //    PhysicsManager::Instance().update(FramerateController::DEFAULT_FIXED_TIME_STEP);
    //    framerateController->ConsumePhysicsTime();
    //}
    PhysicsManager::Instance().update(deltaTime);

    input.update();
    if (input.isKeyHeld(KEY_ESCAPE))
      break;

    sceneGraph.update(deltaTime);

    // draw debug lines for all bodies
    // In your render loop, after sceneGraph.draw:
    //std::cout << "Number of physics bodies: " << PhysicsManager::Instance().getBodies().size() << "\n";
    for (auto body : PhysicsManager::Instance().getBodies()) {
      if (auto obb = dynamic_cast<OBB*>(body->getShape())) {
        //std::cout << "Drawing OBB at position: " << body->getOwner()->getLocalPosition().x
        //    << ", " << body->getOwner()->getLocalPosition().y << "\n";
        obb->drawDebugLines(viewMatrix, projectionMatrix);
      }
      if (auto aabb = dynamic_cast<AABB*>(body->getShape())) {
        //std::cout << "Drawing OBB at position: " << body->getOwner()->getLocalPosition().x
        //    << ", " << body->getOwner()->getLocalPosition().y << "\n";
        aabb->drawDebugLines(viewMatrix, projectionMatrix);
      }
    }


    sceneGraph.draw(viewMatrix, projectionMatrix);

    //std::cout << "Angle for box1: " << angle << std::endl;
    //std::cout << "========================" << std::endl;
    renderer.swapBuffers();
    window.pollEvents();

    framerateController->endFrame();
    deltaTime = framerateController->getFrameTime();

  }

  return 0;
}
