#include "precompiled.h"
#include "LevelManager.h"

void onMove(std::shared_ptr<GameObject> object, const Movement3D::Action action) {

    //std::cout << "onMove\n";

    AudioManager::instance().playSound("footstep", Vector3(object->getLocalPosition()));

    return;

}

void LevelManager::SystemInitalization()
{

    /* Game Window setup */
    int windowWidth = 1280;
    int windowHeight = 720;
    mainWindow = new GameWindow;
    mainWindow->setTitle("EngineDemo")->setHeight(windowHeight)->setWidth(windowWidth);
    mainWindow->initialize();

    /* Renderer setup */
    mainRenderer = new Renderer;
    mainRenderer->setGameWindow(mainWindow);
    mainRenderer->initialize();
    mainRenderer->setClearColor(0.05f, 0.05f, 0.1f, 1.0f);

    /* IMGUI Init */
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
    mainInput = new Input;
    std::vector<Key> keysToMonitor = {
      KEY_W, KEY_A, KEY_S, KEY_D, KEY_R, KEY_F,
      KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_ESCAPE
    };
    mainInput->setGameWindow(mainWindow);
    mainInput->initialize();

    /* XInput setup */
    gamepad = new GamePad;
    gamepad->initialize();

    /* Framerate controller setup */
    mainFramerateController =
        FFramerateController::getController();

    /* Audio System Initalization */
    AudioManager::instance().initialize();
    AudioManager::instance().loadSound("pew", "media/audio/pew.mp3", true);
    AudioManager::instance().loadSound("music", "media/audio/BE21-Undertoe-Steele.mp3", true, true);
    AudioManager::instance().loadSound("radio", "media/audio/radio.wav", true, true);
    AudioManager::instance().loadSound("bang", "media/audio/bang.mp3", true);
    AudioManager::instance().loadSound("walk", "media/audio/walk.mp3", true);
    AudioManager::instance().loadSound("run", "media/audio/footstep.mp3", true);
    AudioManager::instance().loadSound("slide", "media/audio/slide.mp3", true);
    AudioManager::instance().loadSound("jump", "media/audio/jump.mp3", true);
    
    AudioManager::instance().playSound2D("music", 0.25f);
    //AudioManager::instance().playSound("radio", Vector3(2.0f, 0.5f, 0.0f), 0.3f);

    /* Scenegraph setup */
    //SceneGraph mainSceneGraph;

    /* Raycast Manager Setup */
    RaycastManager::Instance().setSceneGraph(&mainSceneGraph);

}

void LevelManager::MeshMatInitializations()
{

#pragma region Meshs/Materials
    // Create meshes
    boxMesh = Mesh::createMesh("box", Mesh::Cube);
    sphereMesh = Mesh::createSphereMesh("sphere", 32);

    // Box Material
    boxMaterial = Material::getMaterial<MainTestMaterial>("box", mainRenderer->getRenderGraph());
    boxMaterial->setProperty("diffuse", Vector3(87.0f / 255.0f, 51.0f / 255.0f, 35.0f / 255.0f));
    boxMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    boxMaterial->setProperty("shininess", 10.0f);
    boxMaterial->addTexture("media/textures/Brazilian_rosewood_pxr128.png");
    boxMaterial->addTexture("media/textures/Brazilian_rosewood_pxr128_normal.png");

    // Floor Material
    floorMaterial = Material::getMaterial<MainTestMaterial>("floor", mainRenderer->getRenderGraph());
    floorMaterial->setProperty("diffuse", Vector3(87.0f / 255.0f, 51.0f / 255.0f, 35.0f / 255.0f));
    floorMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    floorMaterial->setProperty("shininess", 10.0f);
    floorMaterial->addTexture("media/textures/6670-diffuse.jpg");
    floorMaterial->addTexture("media/textures/6670-normal.jpg");

    // Concrete Material
    concreteMaterial = Material::getMaterial<MainTestMaterial>("concrete", mainRenderer->getRenderGraph());
    concreteMaterial->setProperty("diffuse", Vector3(87.0f / 255.0f, 51.0f / 255.0f, 35.0f / 255.0f));
    concreteMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    concreteMaterial->setProperty("shininess", 10.0f);
    concreteMaterial->addTexture("media/textures/Concrete.png", 20.0f, 20.0f);

    // Grass Material
    grassMaterial = Material::getMaterial<MainTestMaterial>("grass", mainRenderer->getRenderGraph());
    grassMaterial->setProperty("diffuse", Vector3(87.0f / 255.0f, 51.0f / 255.0f, 35.0f / 255.0f));
    grassMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    grassMaterial->setProperty("shininess", 10.0f);
    grassMaterial->addTexture("media/textures/grass.jpg");

    // Cracks Material
    cracksMaterial = Material::getMaterial<MainTestMaterial>("cracks", mainRenderer->getRenderGraph());
    cracksMaterial->setProperty("diffuse", Vector3(87.0f / 255.0f, 51.0f / 255.0f, 35.0f / 255.0f));
    cracksMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    cracksMaterial->setProperty("shininess", 10.0f);
    cracksMaterial->addTexture("media/textures/cracks.png");

    // MyHouse Material
    myhouseMaterial = Material::getMaterial<MainTestMaterial>("myhouse", mainRenderer->getRenderGraph());
    myhouseMaterial->setProperty("diffuse", Vector3(87.0f / 255.0f, 51.0f / 255.0f, 35.0f / 255.0f));
    myhouseMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    myhouseMaterial->setProperty("shininess", 10.0f);
    myhouseMaterial->addTexture("media/textures/my-house-01.png");

    // Brick Material
    brickMaterial = Material::getMaterial<MainTestMaterial>("brick", mainRenderer->getRenderGraph());
    brickMaterial->setProperty("diffuse", Vector3(87.0f / 255.0f, 51.0f / 255.0f, 35.0f / 255.0f));
    brickMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    brickMaterial->setProperty("shininess", 10.0f);
    brickMaterial->addTexture("media/textures/Standard_red_pxr128.png");
    brickMaterial->addTexture("media/textures/Standard_red_pxr128_normal.png");

    // Sky Box Material
    sphereMesh = Mesh::createSphereMesh("sphere", 32);
    skyBoxMaterial = Material::getMaterial<MainTestMaterial>("skyBox", mainRenderer->getRenderGraph());
    skyBoxMaterial.get()->addTexture("media/beach.jpg");
    skyBoxMaterial.get()->setProperty("objectId", 1);

    // Additional Materials

    LightBlueConcrete = Material::getMaterial<MainTestMaterial>("LightBlueConcrete", mainRenderer->getRenderGraph());
    LightBlueConcrete->setProperty("diffuse", Vector3(87.0f / 255.0f, 51.0f / 255.0f, 35.0f / 255.0f));
    LightBlueConcrete->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    LightBlueConcrete->setProperty("shininess", 10.0f);
    LightBlueConcrete->addTexture("media/textures/LightBlueConcrete.png", 20.0f, 20.0f);

    YellowConcrete = Material::getMaterial<MainTestMaterial>("YellowConcrete", mainRenderer->getRenderGraph());
    YellowConcrete->setProperty("diffuse", Vector3(87.0f / 255.0f, 51.0f / 255.0f, 35.0f / 255.0f));
    YellowConcrete->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    YellowConcrete->setProperty("shininess", 10.0f);
    YellowConcrete->addTexture("media/textures/YellowConcrete.png", 20.0f, 20.0f);

    BrownConcrete = Material::getMaterial<MainTestMaterial>("BrownConcrete", mainRenderer->getRenderGraph());
    BrownConcrete->setProperty("diffuse", Vector3(87.0f / 255.0f, 51.0f / 255.0f, 35.0f / 255.0f));
    BrownConcrete->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    BrownConcrete->setProperty("shininess", 10.0f);
    BrownConcrete->addTexture("media/textures/BrownConcrete.png", 20.0f, 20.0f);

    BlueConcrete = Material::getMaterial<MainTestMaterial>("BlueConcrete", mainRenderer->getRenderGraph());
    BlueConcrete->setProperty("diffuse", Vector3(87.0f / 255.0f, 51.0f / 255.0f, 35.0f / 255.0f));
    BlueConcrete->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    BlueConcrete->setProperty("shininess", 10.0f);
    BlueConcrete->addTexture("media/textures/BlueConcrete.png", 20.0f, 20.0f);

    WhiteFloorTiles = Material::getMaterial<MainTestMaterial>("WhiteFloorTiles", mainRenderer->getRenderGraph());
    WhiteFloorTiles->setProperty("diffuse", Vector3(87.0f / 255.0f, 51.0f / 255.0f, 35.0f / 255.0f));
    WhiteFloorTiles->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    WhiteFloorTiles->setProperty("shininess", 10.0f);
    WhiteFloorTiles->addTexture("media/textures/WhiteFloorTiles.png", 20.0f, 20.0f);

    keyMaterial = Material::getMaterial<MainTestMaterial>("key", mainRenderer->getRenderGraph());
    keyMaterial->setProperty("diffuse", Vector3(87 / 255.0f, 51 / 255.0f, 35 / 255.0f));
    keyMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    keyMaterial->setProperty("shininess", 20.0f);
    keyMaterial->addTexture("media/textures/key.png", 1.0f, 1.0f);


#pragma endregion

    /*Map Loader*/
    std::shared_ptr<RenderGraph> rg = mainRenderer->getRenderGraph();
    MapLoader::instance().initializeResources(rg);

}

void LevelManager::RunLevels()
{

    levelSwapFlag = false;

    createPlayerObject();
    initalizePlayerInLevel();

    switch (currentLevel)
    {
    case 0:
        LoadLevel0();
        break;
    case 1:
        LoadLevel1();
        break;
    case 2:
        LoadLevel2();
        break;
    case 3:
        LoadLevel3();
        break;
    case 4:
        LoadLevel4();
        break;
    case 5:
        LoadLevel5();
        break;
    default:        
        break;
    }

    ExecuteMainLoop();

    ClearLevel();

}

void LevelManager::ExecuteMainLoop()
{

    /* Main Loop Variables */
    float angleX = 0.0f;
    float angleY = 0.0f;
    float angleZ = 0.0f;
    float speed = 10.0f;
    float deltaTime = 0.0f;
    int expectedFrameRate = 60; // 1000;
    mainFramerateController->setTargetFramerate(expectedFrameRate);
    mainSceneGraph.printSceneTree();

    while (!levelSwapFlag) {

        mainRenderer->clear();
        mainFramerateController->startFrame();              // record the time from frame start

        //Update the Input Manager
        mainInput->update();

        //Update the GamePad
        gamepad->update();

        //If Escape is Pressed Exit Loop
        if (mainInput->isKeyHeld(KEY_ESCAPE)) {
            currentLevel = numLevels + 1;
            break;
        }

        // Physics update loop fixedStepTime
        /*while (mainFramerateController->shouldUpdatePhysics()) {
            PhysicsManager::Instance().update(mainFramerateController->getPhysicsTimestep());
            mainFramerateController->consumePhysicsTime();
        }*/

        auto fpc = playerBox->findComponent<FirstPersonControllerComponent>();
        if (fpc && fpc->isCreativeMode()) {
            for (int level = 0; level < 10; ++level) {
                Key levelKey;
                switch (level) {
                case 0: levelKey = KEY_0; break;
                case 1: levelKey = KEY_1; break;
                case 2: levelKey = KEY_2; break;
                case 3: levelKey = KEY_3; break;
                case 4: levelKey = KEY_4; break;
                case 5: levelKey = KEY_5; break;
                case 6: levelKey = KEY_6; break;
                case 7: levelKey = KEY_7; break;
                case 8: levelKey = KEY_8; break;
                case 9: levelKey = KEY_9; break;
                default: continue;
                }
                if (mainInput->isKeyPressed(levelKey)) {
                    if (level < numLevels) {
                        currentLevel = level;
                        levelSwapFlag = true;
                    }
                    else {
                        std::cerr << "[MapLoader] Invalid level!\n";
                    }
                    break;
                }
            }
        }

        for (int i = 0; i < 2; i++) {
            PhysicsManager::Instance().update(1.0f / 120.0f);
        }

        //Audio Update
        AudioManager::instance().update();
        AudioManager::instance().setListenerPosition(playerBox.get()->getWorldTransform().getPosition());
        if (mainInput->isKeyPressed(KEY_V)) {
            AudioManager::instance().togglePlaybackSpeed(0.7f);
        }
        AudioManager::instance().setListenerPosition(playerBox->getLocalPosition());

        mainSceneGraph.update(1.0f / 60.0f);
        checkPlayerBoundaries();
        mainFramerateController->endFrame();

#pragma region IMGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

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

        Vector3 playerPos = playerBox->getWorldTransform().getPosition();
        ImGui::Text("x: %.2f  y: %.2f  z: %.2f", playerPos.x, playerPos.y, playerPos.z);
        ImGui::Text("Timer: %.2f seconds", mainFramerateController->getTime());

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#pragma endregion

        mainRenderer->swapBuffers();
        mainWindow->update();

        //glfwSwapBuffers(window);

    }
}

void LevelManager::checkPlayerBoundaries() {
    Vector3 playerPos = playerBox->getWorldTransform().getPosition();
    // Boundaries for each lvl
    float maxX, minX, maxY, minY, minZ, maxZ;
    switch (currentLevel) {
    case 0:
        maxX = 10.0f; minX = -400.0f;
        maxY = 100.0f; minY = -60.0f;
        maxZ = 11.0f; minZ = -11.0f;
        break;
    case 1:
        maxX = 10.0f; minX = -400.0f;
        maxY = 100.0f; minY = -40.0f;
        maxZ = 11.0f; minZ = -11.0f;
        break;
    case 3:
        maxX = 160.0f; minX = -160.0f;
        maxY = 200.0f; minY = 5.0f;
        maxZ = 200.0f; minZ = -160.0f;
        break;
    default:
        maxX = 1000.0f; minX = -1000.0f;
        maxY = 1000.0f; minY = -20.0f;
        maxZ = 1000.0f; minZ = -1000.0f;
        break;
    }

    if (playerPos.x > maxX || playerPos.x < minX || playerPos.y > maxY || playerPos.y < minY || playerPos.z > maxZ || playerPos.z < minZ) {
        std::cout << playerPos.x << " " << playerPos.y << " " << playerPos.z;
        auto fpc = playerBox->findComponent<FirstPersonControllerComponent>();
        if (fpc && !fpc->isCreativeMode()) {
            fpc->respawnPlayer();
        }
    }
}


void LevelManager::NextLevel()
{
    currentLevel++;
    levelSwapFlag = true;
}

void LevelManager::ClearLevel()
{

    //Clear Physics and Scenegraph
    PhysicsManager::Instance().clearPhysicsManager();
    mainSceneGraph.clear();

}

void LevelManager::ShutdownLevels()
{

    ImGui::DestroyContext();

    mainInput->shutdown();
    mainRenderer->shutdown();
    mainWindow->shutdown();
    AudioManager::instance().shutdown();

    delete mainInput;
    delete mainRenderer;
    delete mainWindow;

}

void LevelManager::LoadLevel0()
{
    MapLoader::instance().loadMap(0, 0, 0, 0, mainSceneGraph, camera);
}

void LevelManager::LoadLevel1()
{
    MapLoader::instance().loadMap(1, 0, 0, 0, mainSceneGraph, camera);
}

void LevelManager::LoadLevel2()
{
    MapLoader::instance().loadMap(2, 0, 0, 0, mainSceneGraph, camera);
}

void LevelManager::LoadLevel3()
{
    MapLoader::instance().loadMap(3, 0, 0, 0, mainSceneGraph, camera);
}

void LevelManager::LoadLevel4()
{
    MapLoader::instance().loadMap(4, 0, 0, 0, mainSceneGraph, camera);
}

void LevelManager::LoadLevel5()
{
    MapLoader::instance().loadMap(5, 0, 0, 0, mainSceneGraph, camera);
}

bool LevelManager::GameComplete()
{
    return currentLevel >= numLevels;
}

void LevelManager::createPlayerObject()
{
#pragma region Initalizations

    playerBox = std::make_shared<GameObject>("PlayerBox", GameObject::Tag::PLAYER);
    mainSceneGraph.addNode(playerBox);

    camera = std::make_shared<Camera>("mainCamera");
    playerBox->addChild(camera);

#pragma endregion

#pragma region Camera

    //Perspective
    camera->setPerspectiveProjection(
      45.0f * 3.14159f / 180.0f,
      mainWindow->getAspectRatio(),
      0.1f,
      5000.0f);

    //Transform
    camera->setLocalPosition(Vector3(0.0f, 2.5f, 0.0f));

    //auto cameraShape = std::make_shared<OBB>(
    //    Vector3(0.0f, 0.0f, 0.0f),  // half width/height of 50 for 100x100 box
    //    Vector3(0.5f, 0.5f, 0.5f));
    //camera->addComponent<PhysicsBody>()
    //    ->setMass(10.0f)->setDrag(1.0f)->setAngularDrag(1.0f)
    //    ->setShape(cameraShape)
    //    //->setDebug(true)
    //    ->registerToPhysicsManager(PhysicsManager::Instance());

#pragma endregion

#pragma region PlayerBox

//Transform Values
    playerBox->setLocalPosition(startingPos1)
        ->setLocalScaling(Vector3(1.0f, 1.0f, 1.0f));

    playerBox->addComponent<KeyList>();
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
    auto playerBoxPB = playerBox->addComponent<RigidBody>()
        ->usingGravity(true)
        ->setMass(10.0f)
        ->setDrag(1.5f)
        ->setShape(shape1)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    playerBoxPB->initialize();

    auto playerBoxInputComponent = playerBox->addComponent<FirstPersonControllerComponent>()
        ->setInputSystem(mainInput)
        ->setGamePad(gamepad)
        ->setPhysicsBody(playerBoxPB.get())
        ->setBody(playerBox.get())
        ->setSceneRoot(mainSceneGraph.getRootNode())
        ->setCamera(camera.get())
        ->setActionKey(FirstPersonControllerComponent::MoveForward, KEY_W)
        ->setActionKey(FirstPersonControllerComponent::MoveBackward, KEY_S)
        ->setActionKey(FirstPersonControllerComponent::MoveLeft, KEY_A)
        ->setActionKey(FirstPersonControllerComponent::MoveRight, KEY_D)
        ->setActionKey(FirstPersonControllerComponent::Jump, KEY_SPACE)
        ->setActionKey(FirstPersonControllerComponent::Sprint, KEY_LEFT_SHIFT)
        ->setActionKey(FirstPersonControllerComponent::Slide, KEY_LEFT_CONTROL)
        ->setActionKey(FirstPersonControllerComponent::Respawn, KEY_R)
        ->setActionKey(FirstPersonControllerComponent::Debug, KEY_9)
        ->setActionKey(FirstPersonControllerComponent::Creative, KEY_C)
        ->setActionKey(FirstPersonControllerComponent::Music, KEY_M)
        ->setActionKey(FirstPersonControllerComponent::Freeze, KEY_F)
        ->setGPActionKey(FirstPersonControllerComponent::Debug, XINPUT_GAMEPAD_A)
        ->setGPActionKey(FirstPersonControllerComponent::Jump, XINPUT_GAMEPAD_Y)
        ->setGPActionKey(FirstPersonControllerComponent::Sprint, XINPUT_GAMEPAD_LEFT_THUMB)
        ->setGPActionKey(FirstPersonControllerComponent::Slide, XINPUT_GAMEPAD_B)
        ->setGPActionKey(FirstPersonControllerComponent::Respawn, XINPUT_GAMEPAD_X)
        ->setGPActionKey(FirstPersonControllerComponent::Creative, XINPUT_GAMEPAD_LEFT_SHOULDER)
        ->setGPActionKey(FirstPersonControllerComponent::Music, XINPUT_GAMEPAD_RIGHT_SHOULDER);

    //On Move Callback 
    Movement3DListener playerMovementListener(playerBox);
    playerMovementListener.setCallback(onMove);
    EventManager::Instance().AddListener(&playerMovementListener);

#pragma endregion

    auto skyBox = std::make_shared<GameObject>("SkyBox");
    skyBox->setLocalPosition(Vector3(0.0f, 0.0f, 0.0f))
        ->setLocalScaling(Vector3(2000.0f, 2000.f, 2000.0f));
    auto skyBoxRenderComponent = skyBox->addComponent<Render2D>();
    skyBoxRenderComponent
        ->setCamera(camera)
        ->setMesh(sphereMesh)
        ->setMaterial(skyBoxMaterial);
    mainSceneGraph.addNode(skyBox);

}



void LevelManager::initalizePlayerInLevel()
{

    Vector3 activeSpawnPoint;
    Quaternion activeSpawnRotation;

    switch (currentLevel)
    {
    case 0:
        activeSpawnPoint = startingPos0;
        activeSpawnRotation = startingRot0;
        break;
    case 1:
        activeSpawnPoint = startingPos1;
        activeSpawnRotation = startingRot1;
        break;
    case 2:
        activeSpawnPoint = startingPos2;
        activeSpawnRotation = startingRot2;
        break;
    case 3:
        activeSpawnPoint = startingPos3;
        activeSpawnRotation = startingRot3;
        break;
    default:
        activeSpawnPoint = Vector3();
        break;
    }

    auto pbFPCController = playerBox->findComponent<FirstPersonControllerComponent>();
    pbFPCController->setRespawnCheckpoint(activeSpawnPoint, activeSpawnRotation);

}
