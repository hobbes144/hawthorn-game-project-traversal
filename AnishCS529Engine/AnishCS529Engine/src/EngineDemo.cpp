#include "precompiled.h"

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
#include "PhysicsBody.h"
#include "OBB.h"
#include "PhysicsManager.h"
#include "Movement3D.h"
#include "CollisionListener.h"
#include "Audio.h"
#include "TestPass.h"
#include "MainTestMaterial.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "RaycastManager.h"
#include "MapLoader.h"

extern "C"
{
  __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
void onBoxCollide(std::shared_ptr<GameObject> obj1, std::shared_ptr<GameObject> obj2, const Vector3& point) {

  std::cout << "OnBoxCollision\n";

  std::shared_ptr<GameObject> dynamic;
  std::shared_ptr<GameObject> player;

  if (obj1.get()->getName() == "PlayerBox") {
    dynamic = obj2;
    player = obj1;
  }
  else if (obj2.get()->getName() == "PlayerBox") {
    dynamic = obj1;
    player = obj2;
  }
  else {
    std::cout << "Neither is player Tank\n";
    return;
  }

  // Play audio from dynamic box
  AudioManager::instance().playSound("bang", Vector3(dynamic->getLocalPosition()));
  return;

}

void onMove(std::shared_ptr<GameObject> object, const Movement3D::Action action) {

  std::cout << "onMove\n";

  AudioManager::instance().playSound("footstep", Vector3(object->getLocalPosition()));

  return;

}


int main() {
  const float rad = PI / 180.0f;

#pragma region System Init

  /* Game Window setup */
  int windowWidth = 1280;
  int windowHeight = 720;
  GameWindow* mainWindow = new GameWindow;
  mainWindow->setTitle("EngineDemo")->setHeight(windowHeight)->setWidth(windowWidth);
  mainWindow->initialize();

  /* Renderer setup */
  Renderer* mainRenderer = new Renderer;
  mainRenderer->setGameWindow(mainWindow);
  mainRenderer->initialize();
  mainRenderer->setClearColor(0.05f, 0.05f, 0.1f, 1.0f);

  ImGui::CreateContext();

  ImGui_ImplGlfw_InitForOpenGL(mainWindow->getNativeWindow(), true);
  ImGui_ImplOpenGL3_Init();

  int textureMode = 1;
  //mainRenderer->getRenderGraph()->addPass<BasicRenderPass>("DirectRenderPass");
  std::shared_ptr<TestPass> testPass = mainRenderer->getRenderGraph()->addPass<TestPass>("TestPass");
  testPass->setProperty("textureMode", textureMode);

  /* Test stuff for lighting */
  double lightSpin = 150.0;
  double lightTilt = -45.0;
  double lightDist = 100.0;
  Vector3 lightPos = Vector3(lightDist * cos(lightSpin * rad) * sin(lightTilt * rad),
                             lightDist * cos(lightTilt * rad),
                             lightDist * sin(lightSpin * rad) * sin(lightTilt * rad));
  testPass->setProperty("lightPos", lightPos);
  testPass->setProperty("mode", 2);
  testPass->setProperty("mode", 2);

  Vector3 Light, Ambient;
  Light = Vector3(4.0, 4.0, 4.0);
  Ambient = Vector3(0.2, 0.2, 0.2);

  testPass->setProperty("Light", Light);
  testPass->setProperty("Ambient", Ambient);

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

#pragma endregion


  /* Audio System Initalization */
  AudioManager::instance().initialize();
  AudioManager::instance().loadSound("pew", "media/audio/pew.mp3", true);
  AudioManager::instance().loadSound("music", "media/audio/GuanShanYue.mp3", true, true);
  AudioManager::instance().loadSound("radio", "media/audio/radio.wav", true, true);
  AudioManager::instance().loadSound("bang", "media/audio/bang.mp3", true);
  AudioManager::instance().loadSound("footstep", "media/audio/footstep.mp3", true);
  AudioManager::instance().setListenerPosition(Vector3(0, 0, 0));
  //AudioManager::instance().playSound("music", Vector3(0, 0, 0));
  //AudioManager::instance().playSound("radio", Vector3(2.0f, 0.5f, 0.0f), 0.3f);

  /* Scenegraph setup */
  SceneGraph mainSceneGraph;

  /* Camera setup */
#pragma region Camera

  auto camera = std::make_shared<Camera>("mainCamera");
  camera->setPerspectiveProjection(
    45.0f * 3.14159f / 180.0f,
    mainWindow->getAspectRatio(),
    0.1f,
    5000.0f)
    ->setLocalPosition(Vector3(0.0f, 10.0f, 20.0f))
    ->setLocalRotation(Vector3(0.55f, 0.0f, 0.0f));
  mainSceneGraph.addNode(camera);

  auto cameraShape = std::make_shared<OBB>(
      Vector3(0.0f, 0.0f, 0.0f),  // half width/height of 50 for 100x100 box
      Vector3(0.5f, 0.5f, 0.5f));
  camera->addComponent<PhysicsBody>()
    ->setMass(10.0f)->setDrag(100.0f)->setAngularDrag(500.0f)
    ->setShape(cameraShape)
    //->setDebug(true)
    ->registerToPhysicsManager(PhysicsManager::Instance());

  auto cameraInputComponent = camera->addComponent<Movement3D>()->setInputSystem(mainInput)
    ->setAction(Movement3D::Forward, KEY_W)
    ->setAction(Movement3D::Back, KEY_S)
    ->setAction(Movement3D::Left, KEY_A)
    ->setAction(Movement3D::Right, KEY_D)
    ->setAction(Movement3D::Up, KEY_R)
    ->setAction(Movement3D::Down, KEY_F)
    ->setAction(Movement3D::RollClockwise, KEY_LEFT)
    ->setAction(Movement3D::RollAntiClockwise, KEY_RIGHT)
    ->setAction(Movement3D::PitchClockwise, KEY_UP)
    ->setAction(Movement3D::PitchAnticlockwise, KEY_DOWN)
    ->setAction(Movement3D::YawClockwise, KEY_Q)
    ->setAction(Movement3D::YawAntiClockwise, KEY_E);

#pragma endregion

#pragma region Meshs/Materials

  /* Boxes */
  auto boxMesh = Mesh::createMesh("box", Mesh::Cube);
  auto boxMaterial = Material::getMaterial<MainTestMaterial>("box", mainRenderer->getRenderGraph());
  boxMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
  boxMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
  boxMaterial->setProperty("shininess", 10.0f);
  boxMaterial->setProperty("objectId", 5);
  boxMaterial->addTexture("media/textures/Brazilian_rosewood_pxr128.png");
  boxMaterial->addTexture("media/textures/Brazilian_rosewood_pxr128_normal.png");

  /* Floor */
  auto floorMesh = Mesh::createMesh("box", Mesh::Cube);
  auto floorMaterial = Material::getMaterial<MainTestMaterial>("floor", mainRenderer->getRenderGraph());
  floorMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
  floorMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
  floorMaterial->setProperty("shininess", 10.0f);
  floorMaterial->setProperty("objectId", 5);
  floorMaterial->addTexture("media/textures/6670-diffuse.jpg");
  floorMaterial->addTexture("media/textures/6670-normal.jpg");

  /* Grass */
  auto grassMaterial = Material::getMaterial<MainTestMaterial>("grass", mainRenderer->getRenderGraph());
  grassMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
  grassMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
  grassMaterial->setProperty("shininess", 10.0f);
  grassMaterial->setProperty("objectId", 5);
  grassMaterial->addTexture("media/textures/grass.jpg");

  /* Cracks */
  auto cracksMaterial = Material::getMaterial<MainTestMaterial>("cracks", mainRenderer->getRenderGraph());
  cracksMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
  cracksMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
  cracksMaterial->setProperty("shininess", 10.0f);
  cracksMaterial->setProperty("objectId", 5);
  cracksMaterial->addTexture("media/textures/cracks.png");

  /* MyHouse */
  auto myhouseMaterial = Material::getMaterial<MainTestMaterial>("myhouse", mainRenderer->getRenderGraph());
  myhouseMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
  myhouseMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
  myhouseMaterial->setProperty("shininess", 10.0f);
  myhouseMaterial->setProperty("objectId", 5);
  myhouseMaterial->addTexture("media/textures/my-house-01.png");

  /* Brick */
  auto brickMaterial = Material::getMaterial<MainTestMaterial>("brick", mainRenderer->getRenderGraph());
  brickMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
  brickMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
  brickMaterial->setProperty("shininess", 10.0f);
  brickMaterial->setProperty("objectId", 5);
  brickMaterial->addTexture("media/textures/Standard_red_pxr128.png");
  brickMaterial->addTexture("media/textures/Standard_red_pxr128_normal.png");

  /*Sky Box*/
  auto sphereMesh = Mesh::createSphereMesh("sphere", 32);
  auto skyBoxMaterial = Material::getMaterial<MainTestMaterial>("skyBox", mainRenderer->getRenderGraph());
  skyBoxMaterial->addTexture("media/beach.jpg");
  skyBoxMaterial->setProperty("objectId", 1);

  auto skyBox = std::make_shared<GameObject>("SkyBox");
  skyBox->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f))
    ->setLocalScaling(Vector3(2000.0f, 2000.f, 2000.0f));
  auto skyBoxRenderComponent = skyBox->addComponent<Render2D>();
  skyBoxRenderComponent
    ->setCamera(camera)
    ->setMesh(sphereMesh)
    ->setMaterial(skyBoxMaterial);
  mainSceneGraph.addNode(skyBox);

#pragma endregion

  // Drawable objects
  int isDebug = 0;
  std::vector<std::shared_ptr<GameObject>> gameObjects;
  /*
#pragma region Map
  std::shared_ptr<Mesh> mapMesh = Mesh::loadMesh("media/Map/Map.fbx");
  auto mapObject = std::make_shared<GameObject>("Map");
  mapObject->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
  mapObject->setLocalScaling(Vector3(0.1f, 0.1f, 0.1f));
  auto mapRenderComponent = mapObject->addComponent<Render2D>();
  mapRenderComponent->setCamera(camera)
    ->setMesh(mapMesh)
    ->setMaterial(floorMaterial);
  mainSceneGraph.addNode(mapObject);

#pragma endregion
*/
    /*
#pragma region Environment 
    std::shared_ptr<Mesh> EnvironmentMesh = Mesh::loadMesh("media/Map/Environment.fbx");
    auto EnvironmentObject = std::make_shared<GameObject>("Environment");
    EnvironmentObject->setLocalPosition(Vector3(350.0f, -50.0f, -100.0f));
    EnvironmentObject->setLocalScaling(Vector3(0.1f, 0.1f, 0.1f));
    auto EnvironmentRenderComponent = EnvironmentObject->addComponent<Render2D>();
    EnvironmentRenderComponent->setCamera(camera)
        ->setMesh(EnvironmentMesh)
        ->setMaterial(floorMaterial);
    mainSceneGraph.addNode(EnvironmentObject);
    
#pragma endregion
*/
  /*
#pragma region jump

// Starting
{
    auto mainFloor = std::make_shared<GameObject>("MainFloor");
    mainFloor->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
    mainFloor->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto renderComp = mainFloor->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    mainSceneGraph.addNode(mainFloor);
}

// platforms
float platformSizes[] = { 4.0f, 3.5f, 3.0f, 3.2f, 3.6f, 3.1f, 3.4f, 3.7f, 4.2f };
float yVariation[] = { 0.3f, -0.2f, 0.5f, -0.4f, 0.2f, -0.3f, 0.4f, -0.2f, 0.1f };
float xSpacing = 6.0f;
float xOffset[] = { 2.0f, 2.0f, -3.0f, 3.0f, -4.0f, 4.0f, -5.0f, 5.0f, 8.0f };

for (int i = 0; i < 9; ++i) {
    auto platform = std::make_shared<GameObject>("Platform" + std::to_string(i + 1));
    float adjustedX = (i == 0) ? (xSpacing * 1.5f) : ((i + 1) * xSpacing + 5.0f);
    platform->setLocalPosition(Vector3(adjustedX, yVariation[i], xOffset[i]));
    platform->setLocalScaling(Vector3(platformSizes[i], 0.5f, platformSizes[i]));
    auto renderComp = platform->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    mainSceneGraph.addNode(platform);
}

// Exit
{
    auto upperFloor = std::make_shared<GameObject>("UpperFloor");
    upperFloor->setLocalPosition(Vector3(60.0f, 0.2f, 8.0f));
    upperFloor->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto renderComp = upperFloor->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    mainSceneGraph.addNode(upperFloor);
}

#pragma endregion
*/
#pragma region wallrun

  MapLoader::instance().loadMap(2, 0.0f, 0.0f, 0.0f, mainSceneGraph, camera, floorMesh, boxMaterial);

  MapLoader::instance().loadMap(1, 0.0f, 0.0f, 30.0f, mainSceneGraph, camera, floorMesh, floorMaterial);
#pragma endregion

 
  /*
#pragma region Turret
  std::shared_ptr<Mesh> turretMesh = Mesh::loadMesh("media/Map/Turret.fbx");
  auto turretObject = std::make_shared<GameObject>("turret");
  turretObject->setLocalPosition(Vector3(50.0f, 1.0f, 0.0f));
  turretObject->setLocalScaling(Vector3(0.1f, 0.1f, 0.1f));
  auto turretRenderComponent = turretObject->addComponent<Render2D>();
  turretRenderComponent->setCamera(camera)
    ->setMesh(turretMesh)
    ->setMaterial(brickMaterial);
  mainSceneGraph.addNode(turretObject);
#pragma endregion

#pragma region Cannon
  std::shared_ptr<Mesh> cannonMesh = Mesh::loadMesh("media/Map/Cannon.fbx");
  auto cannonObject = std::make_shared<GameObject>("Cannon");
  cannonObject->setLocalPosition(Vector3(-100.0f, 1.0f, 0.0f));
  cannonObject->setLocalScaling(Vector3(0.1f, 0.1f, 0.1f));
  cannonObject->setLocalRotation(Vector3(0.0f, 0.0f, 135.0f));
  auto cannonRenderComponent = cannonObject->addComponent<Render2D>();
  cannonRenderComponent->setCamera(camera)
    ->setMesh(cannonMesh)
    ->setMaterial(boxMaterial);
  mainSceneGraph.addNode(cannonObject);
#pragma endregion

#pragma region Cannonball
  std::shared_ptr<Mesh> cannonballMesh = Mesh::loadMesh("media/Map/Cannonball.fbx");
  auto cannonballObject = std::make_shared<GameObject>("Cannonball");
  cannonballObject->setLocalPosition(Vector3(-80.0f, 1.0f, 70.0f));
  cannonballObject->setLocalScaling(Vector3(0.1f, 0.1f, 0.1f));
  auto cannonballRenderComponent = cannonballObject->addComponent<Render2D>();
  cannonballRenderComponent->setCamera(camera)
    ->setMesh(cannonballMesh)
    ->setMaterial(floorMaterial);
  mainSceneGraph.addNode(cannonballObject);
#pragma endregion
*/
#pragma region PlayerBox

    auto playerBox = std::make_shared<GameObject>("PlayerBox", GameObject::Tag::PLAYER);
  playerBox->setLocalPosition(Vector3(-4.0f, 5.0f, -2.0f))
    ->setLocalScaling(Vector3(1.0f, 1.0f, 1.0f));
  // Todo: when z is set to 1.0f, the bounding box debug gets very messed up.

  //Render Component
  auto box1RenderComponent = playerBox->addComponent<Render2D>();
  box1RenderComponent
    ->setCamera(camera)
    ->setMesh(boxMesh)
    ->setMaterial(cracksMaterial);

  //Create Shape
  auto shape1 = std::make_shared<OBB>(
  Vector3(0.0f, 0.0f, 0.0f),  // half width/height of 50 for 100x100 box
  Vector3(0.5f, 0.5f, 0.5f));
  shape1->initializeDebugDraw(mainRenderer->getRenderGraph(), camera);

  // Create instances of bodies for boxes
  playerBox->addComponent<RigidBody>()
        ->usingGravity(false)
    ->setMass(10.0f)->setDrag(100.0f)
    ->setShape(shape1)
    ->setDebug(isDebug)
    ->registerToPhysicsManager(PhysicsManager::Instance())
    ->initialize();

  auto playerBoxInputComponent = playerBox->addComponent<Movement3D>()->setInputSystem(mainInput)
    ->setAction(Movement3D::Forward, KEY_I)
    ->setAction(Movement3D::Back, KEY_K)
    ->setAction(Movement3D::Left, KEY_J)
    ->setAction(Movement3D::Right, KEY_L);

  Movement3DListener playerMovementListener(playerBox);
  playerMovementListener.setCallback(onMove);

  EventManager::Instance().AddListener(&playerMovementListener);

  mainSceneGraph.addNode(playerBox);
  gameObjects.push_back(playerBox);
#pragma endregion

#pragma region DynamicBox

  auto dynamicBox = std::make_shared<GameObject>("DynamicBox");
  dynamicBox->setLocalPosition(Vector3(-2.0f, 5.0f, -2.0f))
        ->setLocalScaling(Vector3(1.0f, 1.0f, 1.0f))
        ->setLocalRotation(Vector3(0,1,0));
  // Todo: when z is set to 1.0f, the bounding box debug gets very messed up.

  //Render Component
  auto dynamicBoxRenderComponent = dynamicBox->addComponent<Render2D>();
  dynamicBoxRenderComponent
    ->setCamera(camera)
    ->setMesh(boxMesh)
    ->setMaterial(cracksMaterial);

  //Create Shape
  auto dBoxShape = std::make_shared<OBB>(
  Vector3(0.0f, 0.0f, 0.0f),  // half width/height of 50 for 100x100 box
  Vector3(0.5f, 0.5f, 0.5f));
  dBoxShape->initializeDebugDraw(mainRenderer->getRenderGraph(), camera);

  // Create instances of bodies for boxes
  dynamicBox->addComponent<RigidBody>()
    ->usingGravity(false)
    ->setMass(10.0f)->setDrag(100.0f)
    ->setShape(dBoxShape)
    ->setDebug(isDebug)
    ->registerToPhysicsManager(PhysicsManager::Instance())
    ->initialize();

  mainSceneGraph.addNode(dynamicBox);
  gameObjects.push_back(dynamicBox);

#pragma endregion

#pragma region Floor

  auto floor = std::make_shared<GameObject>("Floor");
  floor->setLocalPosition(Vector3(0.0f, -1.0f, 0.0f))
    ->setLocalScaling(Vector3(10.0f, 0.05f, 10.0f));

  auto box2RenderComponent = floor->addComponent<Render2D>();
  box2RenderComponent
    ->setCamera(camera)
    ->setMesh(floorMesh)
    ->setMaterial(cracksMaterial);

  auto shape2 = std::make_shared<OBB>(
  Vector3(0.0f, 0.0f, 0.0f),  // half width/height of 50 for 100x100 box
  Vector3(0.5f, 0.5f, 0.5f));
  shape2->initializeDebugDraw(mainRenderer->getRenderGraph(), camera);

  floor->addComponent<RigidBody>()
    ->setMass(10.0f)->setDrag(100.0f)
    ->setShape(shape2)
    ->setDebug(isDebug)
    ->setStatic(true)
    ->registerToPhysicsManager(PhysicsManager::Instance())
    ->initialize();

  mainSceneGraph.addNode(floor);
  gameObjects.push_back(floor);

#pragma endregion

#pragma region Static Sound Box

  auto soundBox = std::make_shared<GameObject>("SoundBox");
  soundBox->setLocalPosition(Vector3(0.0f, 1.0f, 0.0f))
    ->setLocalScaling(Vector3(0.5f, 0.5f, 0.5f));
  // Todo: when z is set to 1.0f, the bounding box debug gets very messed up.

  //Render Component
  auto soundBoxRenderComponent = soundBox->addComponent<Render2D>();
  soundBoxRenderComponent
    ->setCamera(camera)
    ->setMesh(boxMesh)
    ->setMaterial(cracksMaterial);

  //Create Shape
  auto soundBoxShape = std::make_shared<OBB>(
  Vector3(0.0f, 0.0f, 0.0f),  // half width/height of 50 for 100x100 box
  Vector3(0.5f, 0.5f, 0.5f));
  soundBoxShape->initializeDebugDraw(mainRenderer->getRenderGraph(), camera);

  // Create instances of bodies for boxes
  soundBox->addComponent<RigidBody>()
    ->setMass(10.0f)->setDrag(100.0f)
    ->setShape(soundBoxShape)
    ->setDebug(isDebug)
    ->registerToPhysicsManager(PhysicsManager::Instance())
    ->initialize();

  mainSceneGraph.addNode(soundBox);
  gameObjects.push_back(soundBox);

  AudioManager::instance().playSound("music", soundBox.get()->getWorldTransform().getPosition(), 0.7f);

#pragma endregion

  CollisionListener boxTouch(dynamicBox);
  boxTouch.setCallback(onBoxCollide);

  float angleX = 0.0f;
  float angleY = 0.0f;
  float angleZ = 0.0f;
  float speed = 10.0f;
  float deltaTime = 0.0f;
  int expectedFrameRate = 60; // 1000;
  mainFramerateController->setTargetFramerate(expectedFrameRate);
  mainSceneGraph.printSceneTree();

  float affineCounter = 0.0f;
  float affineSpeed = 0.5f;
  Vector3 affinePosStart = Vector3(-10.0f, 0.75f, 10.0f);
  Vector3 affinePosEnd = Vector3(-10.0f, 10.75f, 10.0f);
  Vector3 affineRotStart = Vector3(0.0, 0.0, 0.0);
  Vector3 affineRotEnd = Vector3(0.0, 2.0, 0.0);
  Vector3 affineSclStart = Vector3(0.5, 0.5, 0.5);
  Vector3 affineSclEnd = Vector3(0.6, 0.6, 0.6);

  while (!mainWindow->getShouldClose()) {
    //std::cout << "\nloop restart at time " << framerateController->getTime() << "\n\n";

    mainRenderer->clear();
    mainFramerateController->startFrame();              // record the time from frame start

    mainInput->update();
    if (mainInput->isKeyHeld(KEY_ESCAPE))
      break;

    // Physics update loop fixedStepTime
    while (mainFramerateController->shouldUpdatePhysics()) {
      PhysicsManager::Instance().update(mainFramerateController->getPhysicsTimestep());
      mainFramerateController->consumePhysicsTime();
    }

    //Affine Demonstration
    affineCounter += 0.1f;
    float t = 0.5f * (sinf(affineCounter * affineSpeed) + 1.0f);
    Vector3 affineCurrPos = affinePosStart + (affinePosEnd - affinePosStart) * t;
    soundBox.get()->setLocalPosition(affineCurrPos);
    Vector3 affineCurrRot = affineRotStart + (affineRotEnd - affineRotStart) * t;
    soundBox.get()->setLocalRotation(affineCurrRot);
    Vector3 affineCurrScl = affineSclStart + (affineSclEnd - affineSclStart) * t;
    soundBox.get()->setLocalScaling(affineCurrScl);

    //Audio Update
    AudioManager::instance().update();
    AudioManager::instance().setListenerPosition(playerBox.get()->getWorldTransform().getPosition());
    /*if (mainInput->isKeyPressed(KEY_SPACE)) {
      AudioManager::instance().playSound("pew");
    }*/
    if (mainInput->isKeyPressed(KEY_V)) {
      AudioManager::instance().togglePlaybackSpeed(0.7f);
    }
    if (mainInput->isKeyPressed(KEY_M)) {
      AudioManager::instance().stopSound("radio");
    }

        //Raycast Testing
        if (mainInput->isKeyPressed(KEY_SPACE)) {
            Vector3 rayOrigin = playerBox->getWorldTransform().getPosition();
            Vector3 rayDirection = Vector3(1,0,0);

            Ray testRay(rayOrigin, rayDirection);
            RaycastHit hit;

            if (RaycastManager::Raycast(testRay, &mainSceneGraph, hit, 100.0f, { GameObject::Tag::SYSTEM })) {
                std::cout << "Ray hit at: " << hit.point.x << ", " << hit.point.y << ", " << hit.point.z << std::endl;
            }
            else {
                std::cout << "Ray missed!\n";
            }
        }

    //Light Manipulation
    if (mainInput->isKeyHeld(KEY_T)) {
      std::cout << "Spinning Light\n";
      lightSpin += 2.0f;
      lightPos = Vector3(lightDist * cos(lightSpin * rad) * sin(lightTilt * rad),
                         lightDist * cos(lightTilt * rad),
                         lightDist * sin(lightSpin * rad) * sin(lightTilt * rad));
      testPass->setProperty("lightPos", lightPos);
    }
    else if (mainInput->isKeyHeld(KEY_G)) {
      lightSpin -= 2.0f;
      lightPos = Vector3(lightDist * cos(lightSpin * rad) * sin(lightTilt * rad),
                         lightDist * cos(lightTilt * rad),
                         lightDist * sin(lightSpin * rad) * sin(lightTilt * rad));
      testPass->setProperty("lightPos", lightPos);
    }

    mainSceneGraph.update(deltaTime);
    mainFramerateController->endFrame();

#pragma region IMGUI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar()) {
      // This menu demonstrates how to provide the user a list of toggleable settings.
      if (ImGui::BeginMenu("Objects")) {
        if (ImGui::MenuItem("Draw MovableBox", "", soundBox->isEnabled())) {
          if (soundBox->isEnabled())
            soundBox->disable();
          else
            soundBox->enable();
        }
        if (ImGui::MenuItem("Draw Textures", "", textureMode)) {
          if (textureMode) textureMode = 0;
          else textureMode = 1;
          testPass->setProperty("textureMode", textureMode);
        }
        if (ImGui::MenuItem("Draw debug lines", "", isDebug)) {
          if (isDebug) isDebug = 0;
          else isDebug = 1;
          for (const auto& object : gameObjects) {
            if (auto body = object->findComponent<RigidBody>()) {
              body->setDebug(isDebug);
            }
          }

        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }

    //ImGui::SetNextWindowPos(ImVec2(10, 10)); // Position at top-left
    //ImGui::SetNextWindowBgAlpha(0.35f); // Make it semi-transparent

    ImGui::Begin("Overlay", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoInputs);

    ImGui::Text("FPS: %.1f", mainFramerateController->getFPS());
    ImGui::Text("Frametime: %f", mainFramerateController->getFrameTime());
    ImGui::Text("RenderTime: %f", mainFramerateController->getRenderTime());

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#pragma endregion

    mainRenderer->swapBuffers();
    mainWindow->update();

    //glfwSwapBuffers(window);

  }


  ImGui::DestroyContext();

  mainInput->shutdown();
  mainRenderer->shutdown();
  mainWindow->shutdown();
  AudioManager::instance().shutdown();

  delete mainInput;
  delete mainRenderer;
  delete mainWindow;

  return 0;
}