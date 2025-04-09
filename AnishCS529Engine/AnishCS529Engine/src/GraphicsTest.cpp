#include "precompiled.h"
//#include <windows.h>
//
//#include "Renderer.h"
//#include "GameWindow.h"
//#include "Input.h"
//#include "SceneGraph.h"
//#include "Camera.h"
//#include "RenderableNode.h"
//#include "TrianglePrimitive.h"
//#include "RectanglePrimitive.h"
//#include "FramerateController.h"
//#include "EventManager.h"
//#include "GameObject.h"
//#include "Render3D.h"
//#include "BasicRenderPass.h"
//#include "TextureMaterial.h"
//#include "PhysicsBody.h"
//#include "OBB.h"
//#include "PhysicsManager.h"
//#include "Movement3D.h"
//#include "CollisionListener.h"
//#include "TestPass.h"
//#include "MainTestMaterial.h"
//#include "FreeCamera.h"
//#include "SkydomePass.h"
//#include "LightingPass.h"
//
//
//extern "C"
//{
//  __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
//  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
//}
//
//
//int main() {
//  const float rad = PI / 180.0f;
//
//  /* Game Window setup */
//  int windowWidth = 1280;
//  int windowHeight = 720;
//  GameWindow* mainWindow = new GameWindow;
//  mainWindow->setTitle("RenderingTest")->setHeight(windowHeight)->setWidth(windowWidth);
//  mainWindow->initialize();
//
//  /* Renderer setup */
//  Renderer* mainRenderer = new Renderer;
//  mainRenderer->setGameWindow(mainWindow);
//  mainRenderer->initialize();
//  mainRenderer->setClearColor(0.05f, 0.05f, 0.1f, 1.0f);
//
//  //mainRenderer->getRenderGraph()->addPass<BasicRenderPass>("DirectRenderPass");
//  /*std::shared_ptr<TestPass> testPass = mainRenderer->getRenderGraph()->addPass<TestPass>("TestPass");*/
//
//  //mainWindow->setVsync(true);
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
//
//  /* Test stuff for lighting */
//  Vector3 LightDirection = Vector3(-0.2f, -1.0f, -0.3f).normalized();
//  /*testPass->setProperty("mode", 2);*/
//
//  //Vector3 Light, Ambient;
//  //Light = Vector3(4.0, 4.0, 4.0);
//  //Ambient = Vector3(0.2, 0.2, 0.2);
//  auto skydomePass = std::make_shared<SkydomePass>("media/beach.jpg");
//  mainRenderer->getRenderGraph()->addPass<SkydomePass>("skydome", skydomePass);
//
//  mainSceneGraph.addAmbientLight(
//    AmbientLight(Vector3(1, 1, 1), 0.0f));
//  mainSceneGraph.addDirectionalLight(
//    DirectionalLight(LightDirection, 4.0f, Vector3(1.0f, 1.0f, 1.0f)));
//
//  mainRenderer->getRenderGraph()->addPass<LightingPass>("lightingPass");
//
//  /* Camera setup */
//  Vector3 cameraPos(0.0f, 0.0f, 10.0f);
//  auto camera = std::make_shared<FreeCamera>("mainCamera");
//  camera->setPosition(cameraPos);
//  camera->setExposure(1.0f);
//  camera->setPerspectiveProjection(
//    45.0f * 3.14159f / 180.0f,
//    mainWindow->getAspectRatio(),
//    0.1f,
//    5000.0f);
//  mainSceneGraph.addCamera(camera);
//
//  /* Create relevant Meshes*/
//  auto boxMesh = Mesh::createMesh("box", Mesh::Cube);
//  auto boxMaterial = Material::getMaterial<TextureMaterial>("box");
//  boxMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
//  boxMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
//  boxMaterial->setProperty("shininess", 10.0f);
//  boxMaterial->addTexture("media/textures/Brazilian_rosewood_pxr128.png");
//  boxMaterial->addNormalMap("media/textures/Brazilian_rosewood_pxr128_normal.png");
//
//  /*auto testSphere = std::make_shared<GameObject>("TestSphere");
//  mainSceneGraph.addNode(testSphere);
//  testSphere->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f))
//    ->setLocalScaling(Vector3(2.0f, 2.0f, 2.0f));
//  auto testSphereRenderComponent = testSphere->addComponent<Render2D>();
//  testSphereRenderComponent
//    ->setMesh(sphereMesh)
//    ->setMaterial(skyBoxMaterial);*/
//
//// Drawable objects
//  auto box1 = std::make_shared<GameObject>("Box1");
//  box1->setLocalPosition(Vector3(4.0f, 0.0f, 0.0f))
//    ->setLocalScaling(Vector3(1.0f, 1.f, 1.0f));
//  // Todo: when z is set to 1.0f, the bounding box debug gets very messed up.
//
//  auto box1RenderComponent = box1->addComponent<Render3D>();
//  box1RenderComponent
//    ->setMesh(boxMesh)
//    ->setMaterial(boxMaterial);
//
//  mainSceneGraph.addNode(box1);
//
//  /*auto box2 = std::make_shared<GameObject>("Box2");
//  box1->setLocalPosition(Vector3(-4.0f, 0.0f, 0.0f))
//    ->setLocalScaling(Vector3(1.0f, 1.f, 1.0f));
//
//  auto box2RenderComponent = box2->addComponent<Render2D>();
//  box2RenderComponent
//    ->setMesh(boxMesh)
//    ->setMaterial(boxMaterial);*/
//
//  /*mainSceneGraph.addNode(box1);
//  mainSceneGraph.addNode(box2);*/
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
//  while (!mainWindow->getShouldClose()) {
//    //std::cout << "\nloop restart at time " << framerateController->getTime() << "\n\n";
//
//    mainRenderer->clear();
//    mainFramerateController->startFrame();              // record the time from frame start
//
//    mainInput->update();
//    if (mainInput->isKeyHeld(KEY_ESCAPE))
//      break;
//
//    if (mainInput->isKeyDown(KEY_UP))
//      camera->rotate(Quaternion::fromEuler(0.1f / 3.14159f, 0.0f, 0.0f));
//    if (mainInput->isKeyDown(KEY_DOWN))
//      camera->rotate(Quaternion::fromEuler(-0.1f / 3.14159f, 0.0f, 0.0f));
//
//    if (mainInput->isKeyDown(KEY_LEFT))
//      camera->rotate(Quaternion::fromEuler(0.0f, 0.1f / 3.14159f, 0.0f));
//    if (mainInput->isKeyDown(KEY_RIGHT))
//      camera->rotate(Quaternion::fromEuler(0.0f, -0.1f / 3.14159f, 0.0f));
//
//    if (mainInput->isKeyDown(KEY_Q))
//      camera->rotate(Quaternion::fromEuler(0.0f, 0.0f, 0.1f / 3.14159f));
//    if (mainInput->isKeyDown(KEY_E))
//      camera->rotate(Quaternion::fromEuler(0.0f, 0.0f, -0.1f / 3.14159f));
//
//    if (mainInput->isKeyDown(KEY_R))
//      camera->move(Vector3(0.0f, 1.0f, 0.0f), 0.2f);
//    if (mainInput->isKeyDown(KEY_F))
//      camera->move(Vector3(0.0f, 1.0f, 0.0f), -0.2f);
//
//    if (mainInput->isKeyDown(KEY_W))
//      camera->move(Vector3(0.0f, 0.0f, 1.0f), -0.2f);
//    if (mainInput->isKeyDown(KEY_S))
//      camera->move(Vector3(0.0f, 0.0f, 1.0f), 0.2f);
//
//    if (mainInput->isKeyDown(KEY_A))
//      camera->move(Vector3(1.0f, 0.0f, 0.0f), -0.2f);
//    if (mainInput->isKeyDown(KEY_D))
//      camera->move(Vector3(1.0f, 0.0f, 0.0f), 0.2f);
//
//    Lights* lights = mainSceneGraph.getLights();
//    if (mainInput->isKeyDown(KEY_I))
//      lights->sunLight.direction += Vector3(0.0f, 0.0f, -0.1f);
//    if (mainInput->isKeyDown(KEY_K))
//      lights->sunLight.direction += Vector3(0.0f, 0.0f, 0.1f);
//    if (mainInput->isKeyDown(KEY_J))
//      lights->sunLight.direction += Vector3(0.1f, 0.0f, 0.0f);
//    if (mainInput->isKeyDown(KEY_L))
//      lights->sunLight.direction += Vector3(-0.1f, 0.0f, 0.0f);
//
//    mainSceneGraph.update(deltaTime);
//
//    mainRenderer->getRenderGraph()->draw(&mainSceneGraph);
//
//    mainFramerateController->endFrame();
//    mainRenderer->swapBuffers();
//    mainWindow->update();
//
//    //glfwSwapBuffers(window);
//
//  }
//
// 
//  mainInput->shutdown();
//  mainRenderer->shutdown();
//  mainWindow->shutdown();
//
//  delete(mainInput);
//  delete(mainRenderer);
//  delete(mainWindow);
//
//  return 0;
//}
