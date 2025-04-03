#include "precompiled.h"

#include <windows.h>

#include "Audio.h"
#include "BasicRenderPass.h"
#include "Camera.h"
#include "CollisionListener.h"
#include "EventManager.h"
#include "FirstPersonControllerComponent.h"
#include "FramerateController.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Input.h"
#include "MainTestMaterial.h"
#include "MapLoader.h"
#include "Movement3D.h"
#include "OBB.h"
#include "PhysicsBody.h"
#include "PhysicsManager.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "RaycastManager.h"
#include "RectanglePrimitive.h"
#include "Render2D.h"
#include "RenderableNode.h"
#include "Renderer.h"
#include "SceneGraph.h"
#include "TestPass.h"
#include "TextureMaterial.h"
#include "TrianglePrimitive.h"
#include "InGameKey.h"
#include "KeyList.h"
#include "Door.h"
#include "GlobalVariables.h"

extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
void onBoxCollide(std::shared_ptr<GameObject> obj1, std::shared_ptr<GameObject> obj2, const Vector3& point) {

    //std::cout << "OnBoxCollision\n";

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
        //std::cout << "Neither is player Tank\n";
        return;
    }

    // Play audio from dynamic box
    AudioManager::instance().playSound("bang", Vector3(dynamic->getLocalPosition()));
    return;

}

void onMove(std::shared_ptr<GameObject> object, const Movement3D::Action action) {

    //std::cout << "onMove\n";

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
    Input* mainInput = new Input;
    std::vector<Key> keysToMonitor = {
      KEY_W, KEY_A, KEY_S, KEY_D, KEY_R, KEY_F,
      KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_ESCAPE
    };
    mainInput->setGameWindow(mainWindow);
    mainInput->initialize();

    /* XInput setup */
    GamePad* gamepad = new GamePad;
    gamepad->initialize();

    /* Framerate controller setup */
    FFramerateController* mainFramerateController =
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
    AudioManager::instance().setListenerPosition(Vector3(0, 0, 0));
    AudioManager::instance().playSound("music", Vector3(0, 0, 0));
    //AudioManager::instance().playSound("radio", Vector3(2.0f, 0.5f, 0.0f), 0.3f);

    /* Scenegraph setup */
    SceneGraph mainSceneGraph;

    /* Raycast Manager Setup */
    RaycastManager::Instance().setSceneGraph(&mainSceneGraph);

#pragma endregion

    // Drawable objects
    int isDebug = 0;
    std::vector<std::shared_ptr<GameObject>> gameObjects;


#pragma region Initalizations

    auto playerBox = std::make_shared<GameObject>("PlayerBox", GameObject::Tag::PLAYER);
    mainSceneGraph.addNode(playerBox);

    auto camera = std::make_shared<Camera>("mainCamera");
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

    /* Concrete */
    auto concreteMesh = Mesh::createMesh("box", Mesh::Cube);
    auto concreteMaterial = Material::getMaterial<MainTestMaterial>("concrete", mainRenderer->getRenderGraph());
    concreteMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
    concreteMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
    concreteMaterial->setProperty("shininess", 10.0f);
    concreteMaterial->setProperty("objectId", 5);
    concreteMaterial->addTexture("media/textures/Concrete.png", 20.0f, 20.0f);

    /* Light Blue Concrete */
    auto lightBlueConcreteMesh = Mesh::createMesh("box", Mesh::Cube);
    auto lightBlueConcreteMaterial = Material::getMaterial<MainTestMaterial>("lightBlueConcrete", mainRenderer->getRenderGraph());
    lightBlueConcreteMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
    lightBlueConcreteMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
    lightBlueConcreteMaterial->setProperty("shininess", 10.0f);
    lightBlueConcreteMaterial->setProperty("objectId", 5);
    lightBlueConcreteMaterial->addTexture("media/textures/LightBlueConcrete.png", 20.0f, 20.0f);

    /* Yellow Concrete */
    auto yellowConcreteMesh = Mesh::createMesh("box", Mesh::Cube);
    auto yellowConcreteMaterial = Material::getMaterial<MainTestMaterial>("yellowConcrete", mainRenderer->getRenderGraph());
    yellowConcreteMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
    yellowConcreteMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
    yellowConcreteMaterial->setProperty("shininess", 10.0f);
    yellowConcreteMaterial->setProperty("objectId", 5);
    yellowConcreteMaterial->addTexture("media/textures/YellowConcrete.png", 20.0f, 20.0f);

    /* BrownConcrete */
    auto BrownConcreteMesh = Mesh::createMesh("box", Mesh::Cube);
    auto BrownConcreteMaterial = Material::getMaterial<MainTestMaterial>("BrownConcrete", mainRenderer->getRenderGraph());
    BrownConcreteMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
    BrownConcreteMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
    BrownConcreteMaterial->setProperty("shininess", 10.0f);
    BrownConcreteMaterial->setProperty("objectId", 5);
    BrownConcreteMaterial->addTexture("media/textures/BrownConcrete.png", 1.0f, 1.0f);

    /* BlueConcrete */
    auto BlueConcreteMesh = Mesh::createMesh("box", Mesh::Cube);
    auto BlueConcreteMaterial = Material::getMaterial<MainTestMaterial>("BlueConcrete", mainRenderer->getRenderGraph());
    BlueConcreteMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
    BlueConcreteMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
    BlueConcreteMaterial->setProperty("shininess", 10.0f);
    BlueConcreteMaterial->setProperty("objectId", 5);
    BlueConcreteMaterial->addTexture("media/textures/BlueConcrete.png", 20.0f, 20.0f);

    /* WhiteFloorTiles */
    auto WhiteFloorTilesMesh = Mesh::createMesh("box", Mesh::Cube);
    auto WhiteFloorTilesMaterial = Material::getMaterial<MainTestMaterial>("WhiteFloorTiles", mainRenderer->getRenderGraph());
    WhiteFloorTilesMaterial->setProperty("diffuse", Vector3(87.0 / 255.0, 51.0 / 255.0, 35.0 / 255.0));
    WhiteFloorTilesMaterial->setProperty("specular", Vector3(0.009, 0.009, 0.009));
    WhiteFloorTilesMaterial->setProperty("shininess", 10.0f);
    WhiteFloorTilesMaterial->setProperty("objectId", 5);
    WhiteFloorTilesMaterial->addTexture("media/textures/WhiteFloorTiles.png", 20.0f, 20.0f);

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

#pragma region Map

    auto checkPoint = Vector3(0.0f, 7.0f, 0.0f);
    //auto checkPoint = Vector3(-131.0f, 7.0f, -130.0f);
    //auto checkPoint = Vector3(-110.5f, 25.0f, -40.0f); 
    //auto checkPoint = Vector3(-115.5f, 45.0f, 54.0f); //checkpoint 5
    //auto checkPoint = Vector3(130.0f, 72.0f, 130.0f); //checkpoint 6 or 7?
    std::shared_ptr<RenderGraph> rg = mainRenderer->getRenderGraph();
    MapLoader::instance().initializeResources(rg);
    MapLoader::instance().loadMap(1, 0, 0, 0, mainSceneGraph, camera);

#pragma endregion

#pragma region PlayerBox

    //Transform Values
    playerBox->setLocalPosition(checkPoint)
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
        ->setDebug(isDebug)
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
        ->setActionKey(FirstPersonControllerComponent::Freeze, KEY_F)
        ->setGPActionKey(FirstPersonControllerComponent::Debug, XINPUT_GAMEPAD_A)
        ->setGPActionKey(FirstPersonControllerComponent::Jump, XINPUT_GAMEPAD_Y)
        ->setGPActionKey(FirstPersonControllerComponent::Sprint, XINPUT_GAMEPAD_LEFT_THUMB)
        ->setGPActionKey(FirstPersonControllerComponent::Slide, XINPUT_GAMEPAD_B)
        ->setGPActionKey(FirstPersonControllerComponent::Respawn, XINPUT_GAMEPAD_X)
        ->setGPActionKey(FirstPersonControllerComponent::Creative, XINPUT_GAMEPAD_LEFT_SHOULDER);

    //On Move Callback 
    Movement3DListener playerMovementListener(playerBox);
    playerMovementListener.setCallback(onMove);
    EventManager::Instance().AddListener(&playerMovementListener);

    gameObjects.push_back(playerBox);
#pragma endregion

    /* Main Loop Variables */
    float angleX = 0.0f;
    float angleY = 0.0f;
    float angleZ = 0.0f;
    float speed = 10.0f;
    float deltaTime = 0.0f;
    int expectedFrameRate = 60; // 1000;
    mainFramerateController->setTargetFramerate(expectedFrameRate);
    mainSceneGraph.printSceneTree();

    /* Main Loop */
    while (!mainWindow->getShouldClose()) {
        //std::cout << "\nloop restart at time " << framerateController->getTime() << "\n\n";

        mainRenderer->clear();
        mainFramerateController->startFrame();              // record the time from frame start

        //Update the Input Manager
        mainInput->update();

        //Update the GamePad
        gamepad->update();

        //If Escape is Pressed Exit Loop
        if (mainInput->isKeyHeld(KEY_ESCAPE))
            break;

        // Physics update loop fixedStepTime
        /*while (mainFramerateController->shouldUpdatePhysics()) {
            PhysicsManager::Instance().update(mainFramerateController->getPhysicsTimestep());
            mainFramerateController->consumePhysicsTime();
        }*/

        for (int i = 0; i < 2; i++) {
            PhysicsManager::Instance().update(1.0f / 120.0f);
        }

        //Audio Update
        AudioManager::instance().update();
        AudioManager::instance().setListenerPosition(playerBox.get()->getWorldTransform().getPosition());
        if (mainInput->isKeyPressed(KEY_V)) {
            AudioManager::instance().togglePlaybackSpeed(0.7f);
        }
        if (mainInput->isKeyPressed(KEY_M)) {
            AudioManager::instance().stopSound("radio");
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
        // Check for WASD key events
        if (mainInput->isKeyPressed(KEY_W)) std::cout << "W pressed\n";
        if (mainInput->isKeyReleased(KEY_W)) std::cout << "W released\n";

        if (mainInput->isKeyPressed(KEY_A)) std::cout << "A pressed\n";
        if (mainInput->isKeyReleased(KEY_A)) std::cout << "A released\n";

        if (mainInput->isKeyPressed(KEY_S)) std::cout << "S pressed\n";
        if (mainInput->isKeyReleased(KEY_S)) std::cout << "S released\n";

        if (mainInput->isKeyPressed(KEY_D)) std::cout << "D pressed\n";
        if (mainInput->isKeyReleased(KEY_D)) std::cout << "D released\n";

        if (mainInput->isKeyPressed(KEY_LEFT_CONTROL)) std::cout << "LControl pressed\n";
        if (mainInput->isKeyReleased(KEY_LEFT_CONTROL)) std::cout << "FControl released\n";

        if (mainInput->isKeyPressed(KEY_LEFT_SHIFT)) std::cout << "LShift pressed\n";
        if (mainInput->isKeyReleased(KEY_LEFT_SHIFT)) std::cout << "LShift released\n";

        if (mainInput->isKeyPressed(KEY_SPACE)) std::cout << "Space pressed\n";
        if (mainInput->isKeyReleased(KEY_SPACE)) std::cout << "Space released\n";

        mainSceneGraph.update(1.0f / 60.0f);
        mainFramerateController->endFrame();

#pragma region IMGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (ImGui::BeginMainMenuBar()) {
            // This menu demonstrates how to provide the user a list of toggleable settings.
            if (ImGui::BeginMenu("Objects")) {
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
