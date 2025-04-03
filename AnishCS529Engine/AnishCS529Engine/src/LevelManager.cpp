#include "precompiled.h"
//#include "LevelManager.h"
//
//#include <windows.h>
//
//#include "Audio.h"
//#include "BasicRenderPass.h"
//#include "Camera.h"
//#include "CollisionListener.h"
//#include "EventManager.h"
//#include "FirstPersonControllerComponent.h"
//#include "FramerateController.h"
//#include "GameObject.h"
//#include "GameWindow.h"
//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"
//#include "Input.h"
//#include "MainTestMaterial.h"
//#include "MapLoader.h"
//#include "Movement3D.h"
//#include "OBB.h"
//#include "PhysicsBody.h"
//#include "PhysicsManager.h"
//#include "Ray.h"
//#include "RaycastHit.h"
//#include "RaycastManager.h"
//#include "RectanglePrimitive.h"
//#include "Render2D.h"
//#include "RenderableNode.h"
//#include "Renderer.h"
//#include "SceneGraph.h"
//#include "TestPass.h"
//#include "TextureMaterial.h"
//#include "TrianglePrimitive.h"
//
//#include "GlobalVariables.h"
//
//void onMove(std::shared_ptr<GameObject> object, const Movement3D::Action action) {
//
//    //std::cout << "onMove\n";
//
//    AudioManager::instance().playSound("footstep", Vector3(object->getLocalPosition()));
//
//    return;
//
//}
//
//void LevelManager::SystemInitalization()
//{
//
//    /* Game Window setup */
//    int windowWidth = 1280;
//    int windowHeight = 720;
//    mainWindow = new GameWindow;
//    mainWindow->setTitle("EngineDemo")->setHeight(windowHeight)->setWidth(windowWidth);
//    mainWindow->initialize();
//
//    /* Renderer setup */
//    mainRenderer = new Renderer;
//    mainRenderer->setGameWindow(mainWindow);
//    mainRenderer->initialize();
//    mainRenderer->setClearColor(0.05f, 0.05f, 0.1f, 1.0f);
//
//    /* IMGUI Init */
//    ImGui::CreateContext();
//    ImGui_ImplGlfw_InitForOpenGL(mainWindow->getNativeWindow(), true);
//    ImGui_ImplOpenGL3_Init();
//
//    int textureMode = 1;
//    //mainRenderer->getRenderGraph()->addPass<BasicRenderPass>("DirectRenderPass");
//    std::shared_ptr<TestPass> testPass = mainRenderer->getRenderGraph()->addPass<TestPass>("TestPass");
//    testPass->setProperty("textureMode", textureMode);
//
//    /* Test stuff for lighting */
//    double lightSpin = 150.0;
//    double lightTilt = -45.0;
//    double lightDist = 100.0;
//    Vector3 lightPos = Vector3(lightDist * cos(lightSpin * rad) * sin(lightTilt * rad),
//                               lightDist * cos(lightTilt * rad),
//                               lightDist * sin(lightSpin * rad) * sin(lightTilt * rad));
//    testPass->setProperty("lightPos", lightPos);
//    testPass->setProperty("mode", 2);
//    testPass->setProperty("mode", 2);
//
//    Vector3 Light, Ambient;
//    Light = Vector3(4.0, 4.0, 4.0);
//    Ambient = Vector3(0.2, 0.2, 0.2);
//
//    testPass->setProperty("Light", Light);
//    testPass->setProperty("Ambient", Ambient);
//
//    //mainWindow->setVsync(true);
//
//    /* Input setup */
//    Input* mainInput = new Input;
//    std::vector<Key> keysToMonitor = {
//      KEY_W, KEY_A, KEY_S, KEY_D, KEY_R, KEY_F,
//      KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_ESCAPE
//    };
//    mainInput->setGameWindow(mainWindow);
//    mainInput->initialize();
//
//    /* XInput setup */
//    GamePad* gamepad = new GamePad;
//    gamepad->initialize();
//
//    /* Framerate controller setup */
//    FFramerateController* mainFramerateController =
//        FFramerateController::getController();
//
//    /* Audio System Initalization */
//    AudioManager::instance().initialize();
//    AudioManager::instance().loadSound("pew", "media/audio/pew.mp3", true);
//    AudioManager::instance().loadSound("music", "media/audio/BE21-Undertoe-Steele.mp3", true, true);
//    AudioManager::instance().loadSound("radio", "media/audio/radio.wav", true, true);
//    AudioManager::instance().loadSound("bang", "media/audio/bang.mp3", true);
//    AudioManager::instance().loadSound("walk", "media/audio/walk.mp3", true);
//    AudioManager::instance().loadSound("run", "media/audio/footstep.mp3", true);
//    AudioManager::instance().loadSound("slide", "media/audio/slide.mp3", true);
//    AudioManager::instance().loadSound("jump", "media/audio/jump.mp3", true);
//    AudioManager::instance().setListenerPosition(Vector3(0, 0, 0));
//    AudioManager::instance().playSound("music", Vector3(0, 0, 0));
//    //AudioManager::instance().playSound("radio", Vector3(2.0f, 0.5f, 0.0f), 0.3f);
//
//    /* Scenegraph setup */
//    SceneGraph mainSceneGraph;
//
//    /* Raycast Manager Setup */
//    RaycastManager::Instance().setSceneGraph(&mainSceneGraph);
//
//}
//
//void LevelManager::MeshMatInitializations()
//{
//
//#pragma region Meshs/Materials
//
//    /* Boxes */
//    boxMesh = Mesh::createMesh("box", Mesh::Cube);
//    boxMaterial = Material::getMaterial<MainTestMaterial>("box", mainRenderer->getRenderGraph());
//    boxMaterial.get()->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
//    boxMaterial.get()->setProperty("specular", Vector3(0.009, 0.009, 0.009));
//    boxMaterial.get()->setProperty("shininess", 10.0f);
//    boxMaterial.get()->setProperty("objectId", 5);
//    boxMaterial.get()->addTexture("media/textures/Brazilian_rosewood_pxr128.png");
//    boxMaterial.get()->addTexture("media/textures/Brazilian_rosewood_pxr128_normal.png");
//
//    /* Floor */
//    floorMesh = Mesh::createMesh("box", Mesh::Cube);
//    floorMaterial = Material::getMaterial<MainTestMaterial>("floor", mainRenderer->getRenderGraph());
//    floorMaterial.get()->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
//    floorMaterial.get()->setProperty("specular", Vector3(0.009, 0.009, 0.009));
//    floorMaterial.get()->setProperty("shininess", 10.0f);
//    floorMaterial.get()->setProperty("objectId", 5);
//    floorMaterial.get()->addTexture("media/textures/6670-diffuse.jpg");
//    floorMaterial.get()->addTexture("media/textures/6670-normal.jpg");
//
//    /* Concrete */
//    concreteMesh = Mesh::createMesh("box", Mesh::Cube);
//    concreteMaterial = Material::getMaterial<MainTestMaterial>("concrete", mainRenderer->getRenderGraph());
//    concreteMaterial.get()->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
//    concreteMaterial.get()->setProperty("specular", Vector3(0.009, 0.009, 0.009));
//    concreteMaterial.get()->setProperty("shininess", 10.0f);
//    concreteMaterial.get()->setProperty("objectId", 5);
//    concreteMaterial.get()->addTexture("media/textures/Concrete.png", 20.0f, 20.0f);
//
//    /* Grass 
//    auto grassMaterial = Material::getMaterial<MainTestMaterial>("grass", mainRenderer->getRenderGraph());
//    grassMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
//    grassMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
//    grassMaterial->setProperty("shininess", 10.0f);
//    grassMaterial->setProperty("objectId", 5);
//    grassMaterial->addTexture("media/textures/grass.jpg");
//    */
//
//    /* Cracks */
//    cracksMaterial = Material::getMaterial<MainTestMaterial>("cracks", mainRenderer->getRenderGraph());
//    cracksMaterial.get()->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
//    cracksMaterial.get()->setProperty("specular", Vector3(0.009, 0.009, 0.009));
//    cracksMaterial.get()->setProperty("shininess", 10.0f);
//    cracksMaterial.get()->setProperty("objectId", 5);
//    cracksMaterial.get()->addTexture("media/textures/cracks.png");
//
//    /* MyHouse 
//    auto myhouseMaterial = Material::getMaterial<MainTestMaterial>("myhouse", mainRenderer->getRenderGraph());
//    myhouseMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
//    myhouseMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
//    myhouseMaterial->setProperty("shininess", 10.0f);
//    myhouseMaterial->setProperty("objectId", 5);
//    myhouseMaterial->addTexture("media/textures/my-house-01.png");
//    */
//
//    /* Brick 
//    auto brickMaterial = Material::getMaterial<MainTestMaterial>("brick", mainRenderer->getRenderGraph());
//    brickMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
//    brickMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
//    brickMaterial->setProperty("shininess", 10.0f);
//    brickMaterial->setProperty("objectId", 5);
//    brickMaterial->addTexture("media/textures/Standard_red_pxr128.png");
//    brickMaterial->addTexture("media/textures/Standard_red_pxr128_normal.png");
//    */
//
//    /*Sky Box*/
//    sphereMesh = Mesh::createSphereMesh("sphere", 32);
//    skyBoxMaterial = Material::getMaterial<MainTestMaterial>("skyBox", mainRenderer->getRenderGraph());
//    skyBoxMaterial.get()->addTexture("media/beach.jpg");
//    skyBoxMaterial.get()->setProperty("objectId", 1);
//
//    auto skyBox = std::make_shared<GameObject>("SkyBox");
//    skyBox->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f))
//        ->setLocalScaling(Vector3(2000.0f, 2000.f, 2000.0f));
//    auto skyBoxRenderComponent = skyBox->addComponent<Render2D>();
//    skyBoxRenderComponent
//        ->setCamera(camera)
//        ->setMesh(sphereMesh)
//        ->setMaterial(skyBoxMaterial);
//    mainSceneGraph.addNode(skyBox);
//
//#pragma endregion
//
//}
//
//void LevelManager::RunLevels()
//{
//    switch (currentLevel)
//    {
//    case 0:
//
//        break;
//    case 1:
//        break;
//    case 2:
//        break;
//    default:
//        break;
//    }
//}
//
//void LevelManager::ExecuteMainLoop()
//{
//
//}
//
//void LevelManager::NextLevel()
//{
//    currentLevel++;
//}
//
//void LevelManager::LoadLevel1()
//{
//
//}
//
//void LevelManager::LoadLevel2()
//{
//
//}
//
//void LevelManager::LoadLevel3()
//{
//
//}
//
//void LevelManager::createPlayerObject()
//{
//#pragma region Initalizations
//
//    auto playerBox = std::make_shared<GameObject>("PlayerBox", GameObject::Tag::PLAYER);
//    mainSceneGraph.addNode(playerBox);
//
//    auto camera = std::make_shared<Camera>("mainCamera");
//    playerBox->addChild(camera);
//
//#pragma endregion
//
//#pragma region Camera
//
//    //Perspective
//    camera->setPerspectiveProjection(
//      45.0f * 3.14159f / 180.0f,
//      mainWindow->getAspectRatio(),
//      0.1f,
//      5000.0f);
//
//    //Transform
//    camera->setLocalPosition(Vector3(0.0f, 2.5f, 0.0f));
//
//    //auto cameraShape = std::make_shared<OBB>(
//    //    Vector3(0.0f, 0.0f, 0.0f),  // half width/height of 50 for 100x100 box
//    //    Vector3(0.5f, 0.5f, 0.5f));
//    //camera->addComponent<PhysicsBody>()
//    //    ->setMass(10.0f)->setDrag(1.0f)->setAngularDrag(1.0f)
//    //    ->setShape(cameraShape)
//    //    //->setDebug(true)
//    //    ->registerToPhysicsManager(PhysicsManager::Instance());
//
//#pragma endregion
//
//#pragma region PlayerBox
//
////Transform Values
//    playerBox->setLocalPosition(startingPos1)
//        ->setLocalScaling(Vector3(1.0f, 1.0f, 1.0f));
//
//
//    //Render Component
//    auto box1RenderComponent = playerBox->addComponent<Render2D>();
//    box1RenderComponent
//        ->setCamera(camera)
//        ->setMesh(boxMesh)
//        ->setMaterial(cracksMaterial);
//
//    //Create Shape
//    auto shape1 = std::make_shared<OBB>(
//    Vector3(0.0f, 0.0f, 0.0f),  // half width/height of 50 for 100x100 box
//    Vector3(0.5f, 0.5f, 0.5f));
//    shape1->initializeDebugDraw(mainRenderer->getRenderGraph(), camera);
//
//    // Create instances of bodies for boxes
//    auto playerBoxPB = playerBox->addComponent<RigidBody>()
//        ->usingGravity(true)
//        ->setMass(10.0f)
//        ->setDrag(1.5f)
//        ->setShape(shape1)
//        ->registerToPhysicsManager(PhysicsManager::Instance());
//    playerBoxPB->initialize();
//
//    auto playerBoxInputComponent = playerBox->addComponent<FirstPersonControllerComponent>()
//        ->setInputSystem(mainInput)
//        ->setGamePad(gamepad)
//        ->setPhysicsBody(playerBoxPB.get())
//        ->setBody(playerBox.get())
//        ->setSceneRoot(mainSceneGraph.getRootNode())
//        ->setCamera(camera.get())
//        ->setActionKey(FirstPersonControllerComponent::MoveForward, KEY_W)
//        ->setActionKey(FirstPersonControllerComponent::MoveBackward, KEY_S)
//        ->setActionKey(FirstPersonControllerComponent::MoveLeft, KEY_A)
//        ->setActionKey(FirstPersonControllerComponent::MoveRight, KEY_D)
//        ->setActionKey(FirstPersonControllerComponent::Jump, KEY_SPACE)
//        ->setActionKey(FirstPersonControllerComponent::Sprint, KEY_LEFT_SHIFT)
//        ->setActionKey(FirstPersonControllerComponent::Slide, KEY_LEFT_CONTROL)
//        ->setActionKey(FirstPersonControllerComponent::Respawn, KEY_R)
//        ->setActionKey(FirstPersonControllerComponent::Debug, KEY_9)
//        ->setActionKey(FirstPersonControllerComponent::Creative, KEY_C)
//        ->setActionKey(FirstPersonControllerComponent::Freeze, KEY_F)
//        ->setGPActionKey(FirstPersonControllerComponent::Debug, XINPUT_GAMEPAD_A)
//        ->setGPActionKey(FirstPersonControllerComponent::Jump, XINPUT_GAMEPAD_Y)
//        ->setGPActionKey(FirstPersonControllerComponent::Sprint, XINPUT_GAMEPAD_LEFT_THUMB)
//        ->setGPActionKey(FirstPersonControllerComponent::Slide, XINPUT_GAMEPAD_B)
//        ->setGPActionKey(FirstPersonControllerComponent::Respawn, XINPUT_GAMEPAD_X)
//        ->setGPActionKey(FirstPersonControllerComponent::Creative, XINPUT_GAMEPAD_LEFT_SHOULDER);
//
//    //On Move Callback 
//    Movement3DListener playerMovementListener(playerBox);
//    playerMovementListener.setCallback(onMove);
//    EventManager::Instance().AddListener(&playerMovementListener);
//
//#pragma endregion
//}
