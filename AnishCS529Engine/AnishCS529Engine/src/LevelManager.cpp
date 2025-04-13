#include "precompiled.h"
#include "LevelManager.h"

void LevelManager::SystemInitalization()
{

    /* Game Window setup */
    glfwInit();
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);


    int windowWidth = mode->width;
    int windowHeight = mode->height;

    mainWindow = new GameWindow;

    if (isFullscreen) {
        int windowWidth = mode->width;
        int windowHeight = mode->height;
        mainWindow->setTitle("Traversal")->setWidth(windowWidth)->setHeight(windowHeight)->setBorderlessFullscreen(true);
        mainWindow->initialize(monitor);
    }
    else {
        int windowWidth = 1280;
        int windowHeight = 720;
        mainWindow->setTitle("Traversal")->setWidth(windowWidth)->setHeight(windowHeight)->setBorderlessFullscreen(false);
        mainWindow->initialize(nullptr);
    }

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

    auto skydomePass = std::make_shared<SkydomePass>("media/beach.jpg");
    mainRenderer->getRenderGraph()->addPass<SkydomePass>(skydomePass);

    auto lightingPass = mainRenderer->getRenderGraph()->addPass<LightingPass>();

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
    AudioManager::instance().loadSound("music", "media/audio/FG15-SpyVsSpy-Pfrommer.mp3", false, true);
    AudioManager::instance().loadSound("walk", "media/audio/walk.mp3", true);
    AudioManager::instance().loadSound("run", "media/audio/footstep.mp3", true);
    AudioManager::instance().loadSound("slide", "media/audio/slide.mp3", true);
    AudioManager::instance().loadSound("jump", "media/audio/jump.mp3", true);
    AudioManager::instance().loadSound("key", "media/audio/key.ogg", true);
    AudioManager::instance().loadSound("hurt", "media/audio/hurt.mp3", true);
    
    AudioManager::instance().playSound("music", Vector3(0.0f, 0.0f, 0.0f), 0.15f);
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

    // Digi Material
    digiMaterial = Material::getMaterial<TextureMaterial>("digi");
    digiMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    digiMaterial->setProperty("shininess", 10.0f);
    digiMaterial->addTexture("media/textures/DigiPenLogo.jpg", 1.0f, 1.0f);

    // FMOD Material
    fmodMaterial = Material::getMaterial<TextureMaterial>("fmod");
    fmodMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    fmodMaterial->setProperty("shininess", 10.0f);
    fmodMaterial->addTexture("media/textures/FmodLogo.jpg", 1.0f, 1.0f);

    // Concrete Material
    concreteMaterial = Material::getMaterial<TextureMaterial>("concrete");
    concreteMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    concreteMaterial->setProperty("shininess", 10.0f);
    concreteMaterial->addTexture("media/textures/Concrete.png", 20.0f, 20.0f);

    // Cracks Material
    cracksMaterial = Material::getMaterial<TextureMaterial>("cracks");
    cracksMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    cracksMaterial->setProperty("shininess", 10.0f);
    cracksMaterial->addTexture("media/textures/cracks.png");

    // Sky Box Material
    sphereMesh = Mesh::createSphereMesh("sphere", 32);
    skyBoxMaterial = Material::getMaterial<TextureMaterial>("skyBox");
    skyBoxMaterial.get()->addTexture("media/beach.jpg");
    skyBoxMaterial.get()->setProperty("objectId", 1);

    // Additional Materials

    LightBlueConcrete = Material::getMaterial<TextureMaterial>("LightBlueConcrete");
    LightBlueConcrete->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    LightBlueConcrete->setProperty("shininess", 10.0f);
    LightBlueConcrete->addTexture("media/textures/LightBlueConcrete.png", 20.0f, 20.0f);

    YellowConcrete = Material::getMaterial<TextureMaterial>("YellowConcrete");
    YellowConcrete->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    YellowConcrete->setProperty("shininess", 10.0f);
    YellowConcrete->addTexture("media/textures/YellowConcrete.png", 20.0f, 20.0f);

    BrownConcrete = Material::getMaterial<TextureMaterial>("BrownConcrete");
    BrownConcrete->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    BrownConcrete->setProperty("shininess", 10.0f);
    BrownConcrete->addTexture("media/textures/BrownConcrete.png", 20.0f, 20.0f);

    BlueConcrete = Material::getMaterial<TextureMaterial>("BlueConcrete");
    BlueConcrete->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    BlueConcrete->setProperty("shininess", 10.0f);
    BlueConcrete->addTexture("media/textures/BlueConcrete.png", 20.0f, 20.0f);

    WhiteFloorTiles = Material::getMaterial<TextureMaterial>("WhiteFloorTiles");
    WhiteFloorTiles->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    WhiteFloorTiles->setProperty("shininess", 10.0f);
    WhiteFloorTiles->addTexture("media/textures/WhiteFloorTiles.png", 20.0f, 20.0f);

    keyMaterial = Material::getMaterial<TextureMaterial>("key");
    keyMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    keyMaterial->setProperty("shininess", 20.0f);
    keyMaterial->addTexture("media/textures/key.png", 1.0f, 1.0f);

    //doorMaterial = Material::getMaterial<MainTestMaterial>("door", mainRenderer->getRenderGraph());
    //doorMaterial->setProperty("diffuse", Vector3(87 / 255.0f, 51 / 255.0f, 35 / 255.0f));
    //doorMaterial->setProperty("specular", Vector3(0.009f, 0.009f, 0.009f));
    //doorMaterial->setProperty("shininess", 20.0f);
    //doorMaterial->addTexture("media/textures/door.png", 1.0f, 1.0f);

#pragma endregion

    /*Map Loader*/
    std::shared_ptr<RenderGraph> rg = mainRenderer->getRenderGraph();

    MapLoader::instance().initializeResources();

}

void LevelManager::DisplayLogos()
{
    SceneGraph sceneGraph;

    //Create Object
    auto Logo = std::make_shared<GameObject>("Logo");
    sceneGraph.addNode(Logo);
    Logo->setLocalPosition(Vector3(0.0f, 0.0f, -10.0f));
    Logo->setLocalScaling(Vector3(15.0f, 15.0f, 0.005f));
    auto renderComp = Logo->addComponent<Render3D>();
    renderComp->setMesh(boxMesh)->setMaterial(digiMaterial);
    
    //Create Camera
    auto cam = cameraGameObject = std::make_shared<GameObject>("logoCamera");
    sceneGraph.addNode(cam);
    auto cameraLogo = std::make_shared<AttachedCamera>("logoCamera");
    cameraLogo->attachToNode(cameraGameObject);
    sceneGraph.addCamera(cameraLogo);

    //Perspective
    cameraLogo->setPerspectiveProjection(
      45.0f * 3.14159f / 180.0f,
      mainWindow->getAspectRatio(),
      0.1f,
      5000.0f);

    //Light Direction
    Vector3 LightDirection = Vector3(-1.0f, 0.0f, 0.0f).normalized();
    sceneGraph.addAmbientLight(
      AmbientLight(Vector3(1, 1, 1), 1.0f));
    sceneGraph.addDirectionalLight(
      DirectionalLight(LightDirection, 4.0f, Vector3(1.0f, 1.0f, 1.0f)));

    //Count the Logos
    float logoTimer = 0.0f;
    float logoDuration = 5.0f;
    int currentLogo = 0;
    int numLogos = 2;

    int expectedFrameRate = 60;
    static int windowedPosX, windowedPosY, windowedWidth, windowedHeight;

    mainFramerateController->setTargetFramerate(expectedFrameRate);
    sceneGraph.printSceneTree();

    bool mouseClicked = false;
    bool prevMouseClicked = true;

    while (currentLogo < numLogos) {

        //Restart the Renderer
        mainRenderer->clear();
        mainFramerateController->startFrame();              // record the time from frame start

        //Update the Input Manager
        mainInput->update();

        //Update the GamePad
        gamepad->update();

        //Full Screen Toggle
        if (mainInput->isKeyPressed(GLFW_KEY_F11)) {
            GLFWwindow* nativeWindow = mainWindow->getNativeWindow();
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

            if (isFullscreen) {
                // Windowed mode
                int windowWidth = 1280;
                int windowHeight = 720;
                // Enable borders
                glfwSetWindowAttrib(nativeWindow, GLFW_DECORATED, GLFW_TRUE);
                // Reposition the window
                glfwSetWindowMonitor(nativeWindow, nullptr, 100, 100, windowWidth, windowHeight, 0);
                isFullscreen = false;
            }
            else {
                // Save current window attributes
                glfwGetWindowPos(nativeWindow, &windowedPosX, &windowedPosY);
                glfwGetWindowSize(nativeWindow, &windowedWidth, &windowedHeight);

                // Borderless fullscreen
                glfwSetWindowAttrib(nativeWindow, GLFW_DECORATED, GLFW_FALSE); // Hide borders
                glfwSetWindowMonitor(nativeWindow, nullptr, 0, 0, mode->width, mode->height, 0);
                isFullscreen = true;
            }

            // Adjust viewport and camera aspect ratio
            int fbWidth, fbHeight;
            glfwGetFramebufferSize(nativeWindow, &fbWidth, &fbHeight);
            glViewport(0, 0, fbWidth, fbHeight);
            float newAspect = static_cast<float>(fbWidth) / static_cast<float>(fbHeight);
            camera->setPerspectiveProjection(45.0f * 3.14159f / 180.0f, newAspect, 0.1f, 5000.0f);
        }

        //Update Physics
        while (mainFramerateController->shouldUpdatePhysics()) {
            PhysicsManager::Instance().update(mainFramerateController->getPhysicsTimestep());
            mainFramerateController->consumePhysicsTime();
        }

        //Update Logo Timer
        float deltaTime = 1.0f / expectedFrameRate;
        logoTimer += deltaTime;

        //Ambient Light
        float ambientIntensity = 1.0f;
        float fadeInTime = 0.5f;
        float fadeOutTime = 1.0f;
        if (logoTimer < fadeInTime) {
            ambientIntensity = logoTimer / fadeInTime;
        }
        else if (logoTimer > logoDuration - fadeOutTime) {
            ambientIntensity = std::max(0.0f, (logoDuration - logoTimer) / fadeOutTime);
        }
        sceneGraph.addAmbientLight(
            AmbientLight(Vector3(1, 1, 1), ambientIntensity));

        bool mouseClicked = mainInput->isMouseButtonDown(0) || mainInput->isMouseButtonDown(1);
        bool skipped = (!prevMouseClicked && mouseClicked) ||
                       (mainInput->isKeyPressed(KEY_SPACE))||
                       (mainInput->isKeyPressed(KEY_ENTER))||
                       (mainInput->isKeyPressed(KEY_ESCAPE));

        if ( skipped || logoTimer >= logoDuration) {
            logoTimer = 0.0f;
            currentLogo++;

            if (currentLogo < numLogos) {
                switch (currentLogo)
                {
                case 0:
                    renderComp->setMaterial(digiMaterial);
                    break;
                case 1:
                    renderComp->setMaterial(fmodMaterial);
                    break;
                default:
                    if (currentLogo >= numLogos) break;
                    break;
                }
            }
        }

        prevMouseClicked = mouseClicked;

        //Update Scenegraph
        mainFramerateController->endFrame();
        sceneGraph.update(1.0f / 60.0f);

        //Draw the Scene
        mainRenderer->getRenderGraph()->draw(&sceneGraph);

        //Swap Buffers and Update Window
        mainRenderer->swapBuffers();
        mainWindow->update();

    }

}

void LevelManager::RunLevels()
{

    levelSwapFlag = false;

    createPlayerObject();
    initalizePlayerInLevel();

    switch (currentLevel)
    {
    case -1:
        LoadLevelMenu();
        break;
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
    static int windowedPosX, windowedPosY, windowedWidth, windowedHeight;

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

        //Full Screen Toggle
        if (mainInput->isKeyPressed(GLFW_KEY_F11)) {
            GLFWwindow* nativeWindow = mainWindow->getNativeWindow();
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

            if (isFullscreen) {
                // Windowed mode
                int windowWidth = 1280;
                int windowHeight = 720;
                // Enable borders
                glfwSetWindowAttrib(nativeWindow, GLFW_DECORATED, GLFW_TRUE);
                // Reposition the window
                glfwSetWindowMonitor(nativeWindow, nullptr, 100, 100, windowWidth, windowHeight, 0);
                isFullscreen = false;
            }
            else {
                // Save current window attributes
                glfwGetWindowPos(nativeWindow, &windowedPosX, &windowedPosY);
                glfwGetWindowSize(nativeWindow, &windowedWidth, &windowedHeight);

                // Borderless fullscreen
                glfwSetWindowAttrib(nativeWindow, GLFW_DECORATED, GLFW_FALSE); // Hide borders
                glfwSetWindowMonitor(nativeWindow, nullptr, 0, 0, mode->width, mode->height, 0);
                isFullscreen = true;
            }

            // Adjust viewport and camera aspect ratio
            int fbWidth, fbHeight;
            glfwGetFramebufferSize(nativeWindow, &fbWidth, &fbHeight);
            glViewport(0, 0, fbWidth, fbHeight);
            float newAspect = static_cast<float>(fbWidth) / static_cast<float>(fbHeight);
            camera->setPerspectiveProjection(45.0f * 3.14159f / 180.0f, newAspect, 0.1f, 5000.0f);
        }

        //Cheating Level Select
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
                    if (level == 9) {
                        resetToMenu();
                    }
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

        //Update Physics
        while(mainFramerateController->shouldUpdatePhysics()) {
            PhysicsManager::Instance().update(mainFramerateController->getPhysicsTimestep());
            mainFramerateController->consumePhysicsTime();
        }

        //Audio Update
        AudioManager::instance().update();
        AudioManager::instance().setListenerPosition(playerBox.get()->getWorldTransform().getPosition());
        if (mainInput->isKeyPressed(KEY_V)) {
            AudioManager::instance().togglePlaybackSpeed(0.7f);
        }
        AudioManager::instance().setListenerPosition(playerBox->getWorldPosition());

        mainFramerateController->endFrame();
        mainSceneGraph.update(1.0f / 60.0f);

        checkPlayerBoundaries();
        mainRenderer->getRenderGraph()->draw(&mainSceneGraph);

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
        Vector3 listenerPos = AudioManager::instance().getListenerPosition();
        ImGui::Text("HP: %d", fpc->getHP());
        if (auto fpc = playerBox->findComponent<FirstPersonControllerComponent>()) {
            std::string diffStr;
            switch (fpc->getDifficulty()) {
            case FirstPersonControllerComponent::EASY:
                diffStr = "EASY";
                break;
            case FirstPersonControllerComponent::NORMAL:
                diffStr = "NORMAL";
                break;
            case FirstPersonControllerComponent::HARD:
                diffStr = "HARD";
                break;
            case FirstPersonControllerComponent::CHEATING:
                diffStr = "CHEATING";
                break;
            default:
                diffStr = "UNKNOWN";
                break;
            }
            ImGui::Text("Difficulty: %s", diffStr.c_str());
        }


        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#pragma endregion


        mainRenderer->swapBuffers();
        mainWindow->update();

    }
}

void LevelManager::checkPlayerBoundaries() {
    Vector3 playerPos = playerBox->getWorldTransform().getPosition();
    // Boundaries for each lvl
    float maxX, minX, maxY, minY, minZ, maxZ;
    switch (currentLevel) {
    case 0:
        maxX = 10.0f; minX = -400.0f;
        maxY = 100.0f; minY = -45.0f;
        maxZ = 11.0f; minZ = -11.0f;
        break;
    case 1:
        maxX = 150.0f; minX = -400.0f;
        maxY = 150.0f; minY = -45.0f;
        maxZ = 11.0f; minZ = -11.0f;
        break;
    case 2:
        maxX = 150.0f; minX = -400.0f;
        maxY = 150.0f; minY = -45.0f;
        maxZ = 11.0f; minZ = -11.0f;
        break;
    case 3:
        maxX = 1000.0; minX = -1000.0;
        maxY = 1000.0; minY = 5.0f;
        maxZ = 1000.0; minZ = -1000.0;
        break;
    default:
        maxX = 1000.0f; minX = -1000.0f;
        maxY = 1000.0f; minY = -20.0f;
        maxZ = 1000.0f; minZ = -1000.0f;
        break;
    }

    if (playerPos.x > maxX || playerPos.x < minX || playerPos.y > maxY || playerPos.y < minY || playerPos.z > maxZ || playerPos.z < minZ) {
        //std::cout << playerPos.x << " " << playerPos.y << " " << playerPos.z;
        auto fpc = playerBox->findComponent<FirstPersonControllerComponent>();
        if (fpc && !fpc->isCreativeMode()) {
            fpc->respawnPlayer(true);
            
        }
    }
}

void LevelManager::NextLevel()
{
    if (currentLevel == 4) {
        currentLevel = -1;
    }
    else {
        currentLevel++;
    }
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

#pragma region LevelLoaders

void LevelManager::LoadLevelMenu()
{
    MapLoader::instance().loadMap(-1, 0, 0, 0, mainSceneGraph);
}

void LevelManager::LoadLevel0()
{
    MapLoader::instance().loadMap(0, 0, 0, 0, mainSceneGraph);
}

void LevelManager::LoadLevel1()
{
    MapLoader::instance().loadMap(1, 0, 0, 0, mainSceneGraph);
}

void LevelManager::LoadLevel2()
{
    MapLoader::instance().loadMap(2, 0, 0, 0, mainSceneGraph);
}

void LevelManager::LoadLevel3()
{
    MapLoader::instance().loadMap(3, 0, 0, 0, mainSceneGraph);
}

void LevelManager::LoadLevel4()
{
    MapLoader::instance().loadMap(4, 0, 0, 0, mainSceneGraph);
}

void LevelManager::LoadLevel5()
{
    MapLoader::instance().loadMap(5, 0, 0, 0, mainSceneGraph);
}

#pragma endregion

bool LevelManager::GameComplete()
{
    return currentLevel >= numLevels;
}

void LevelManager::createPlayerObject()
{
#pragma region Initalizations

    playerBox = std::make_shared<GameObject>("PlayerBox", GameObject::Tag::PLAYER);
    mainSceneGraph.addNode(playerBox);

    cameraGameObject = std::make_shared<GameObject>("mainCamera");
    playerBox->addChild(cameraGameObject);

    camera = std::make_shared<AttachedCamera>("mainCamera");
    camera->attachToNode(cameraGameObject);
    mainSceneGraph.addCamera(camera);

#pragma endregion

#pragma region Camera

    //Perspective
    camera->setPerspectiveProjection(
      45.0f * 3.14159f / 180.0f,
      mainWindow->getAspectRatio(),
      0.1f,
      5000.0f);

    //Transform
    cameraGameObject->setLocalPosition(Vector3(0.0f, 2.5f, 0.0f));

    //auto cameraShape = std::make_shared<OBB>(
    //    Vector3(0.0f, 0.0f, 0.0f),  // half width/height of 50 for 100x100 box
    //    Vector3(0.5f, 0.5f, 0.5f));
    //camera->addComponent<PhysicsBody>()
    //    ->setMass(10.0f)->setDrag(1.0f)->setAngularDrag(1.0f)
    //    ->setShape(cameraShape)
    //    //->setDebug(true)
    //    ->registerToPhysicsManager(PhysicsManager::Instance());

#pragma endregion

    Vector3 LightDirection = Vector3(0.75f, -1.0f, 0.75f).normalized();

    mainSceneGraph.addAmbientLight(
      AmbientLight(Vector3(1, 1, 1), 0.3f));
    mainSceneGraph.addDirectionalLight(
      DirectionalLight(LightDirection, 4.0f, Vector3(1.0f, 1.0f, 1.0f)));

#pragma region PlayerBox

//Transform Values
    playerBox->setLocalPosition(startingPos1)
        ->setLocalScaling(Vector3(1.0f, 1.0f, 1.0f));

    playerBox->addComponent<KeyList>();
    //Render Component
    auto box1RenderComponent = playerBox->addComponent<Render3D>();
    box1RenderComponent
        ->setMesh(boxMesh)
        ->setMaterial(cracksMaterial);

    //Create Shape
    auto shape1 = std::make_shared<OBB>(
    Vector3(0.0f, 0.0f, 0.0f),  // half width/height of 50 for 100x100 box
    Vector3(0.5f, 0.5f, 0.5f));

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
        ->setCamera(cameraGameObject.get())
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

    playerBoxInputComponent->setDifficulty(playerDifficulty);
#pragma endregion

}

void LevelManager::initalizePlayerInLevel()
{

    Vector3 activeSpawnPoint;
    Quaternion activeSpawnRotation;

    switch (currentLevel)
    {
    case -1:
        activeSpawnPoint = startingPos0;
        activeSpawnRotation = startingRot0;
        break;
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
    case 4:
        activeSpawnPoint = startingPos4;
        activeSpawnRotation = startingRot4;
        break;
    default:
        activeSpawnPoint = Vector3();
        activeSpawnRotation = Quaternion();
        break;
    }

    auto pbFPCController = playerBox->findComponent<FirstPersonControllerComponent>();
    pbFPCController->setRespawnCheckpoint(activeSpawnPoint, activeSpawnRotation);
    pbFPCController->respawnPlayer(true, true);

}

void LevelManager::SetPlayerDifficulty(FirstPersonControllerComponent::Difficulty diff) {
    playerDifficulty = diff;
}

FirstPersonControllerComponent::Difficulty LevelManager::getDifficulty() const {
    return playerDifficulty;
}

void LevelManager::resetToMenu()
{
    currentLevel = -1;
    levelSwapFlag = true;

}
