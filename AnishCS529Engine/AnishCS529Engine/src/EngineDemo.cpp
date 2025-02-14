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

extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
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

    //mainRenderer->getRenderGraph()->addPass<BasicRenderPass>("DirectRenderPass");
    std::shared_ptr<TestPass> testPass = mainRenderer->getRenderGraph()->addPass<TestPass>("TestPass");

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
    AudioManager::instance().loadSound("music", "media/audio/backgroundMusic.mp3", true, true);
    AudioManager::instance().loadSound("radio", "media/audio/radio.wav", true, true);
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
        ->setLocalRotation(Vector3(-0.55f, 0.0f, 0.0f));
    mainSceneGraph.addNode(camera);

    auto cameraShape = std::make_shared<OBB>(
        Vector3(-0.5f, -0.5f, -0.5f),  // half width/height of 50 for 100x100 box
        Vector3(0.5f, 0.5f, 0.5f));
    camera->addComponent<PhysicsBody>()
        ->setMass(10.0f)->setDrag(100.0f)
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
#pragma region PlayerBox

    auto playerBox = std::make_shared<GameObject>("PlayerBox");
    playerBox->setLocalPosition(Vector3(2.0f, 1.0f, 0.0f))
        ->setLocalScaling(Vector3(1.0f, 1.f, 1.0f));
    // Todo: when z is set to 1.0f, the bounding box debug gets very messed up.

    //Render Component
    auto box1RenderComponent = playerBox->addComponent<Render2D>();
    box1RenderComponent
        ->setCamera(camera)
        ->setMesh(boxMesh)
        ->setMaterial(boxMaterial);

    //Create Shape
    auto shape1 = std::make_shared<OBB>(
    Vector3(-0.5f, -0.5f, -0.5f),  // half width/height of 50 for 100x100 box
    Vector3(0.5f, 0.5f, 0.5f));
    shape1->initializeDebugDraw(mainRenderer->getRenderGraph(), camera);

    // Create instances of bodies for boxes
    playerBox->addComponent<RigidBody>()
        //->usingGravity(true)
        ->setMass(10.0f)->setDrag(100.0f)
        ->setShape(shape1)
        ->setDebug(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());

    auto playerBoxInputComponent = playerBox->addComponent<Movement3D>()->setInputSystem(mainInput)
        ->setAction(Movement3D::Forward, KEY_I)
        ->setAction(Movement3D::Back, KEY_K)
        ->setAction(Movement3D::Left, KEY_J)
        ->setAction(Movement3D::Right, KEY_L);

    mainSceneGraph.addNode(playerBox);

#pragma endregion

#pragma region DynamicBox

    auto dynamicBox = std::make_shared<GameObject>("DynamicBox");
    dynamicBox->setLocalPosition(Vector3(-2.0f, 0.75f, 0.0f))
        ->setLocalScaling(Vector3(0.75f, 0.75f, 0.75f));
    // Todo: when z is set to 1.0f, the bounding box debug gets very messed up.

    //Render Component
    auto dynamicBoxRenderComponent = dynamicBox->addComponent<Render2D>();
    dynamicBoxRenderComponent
        ->setCamera(camera)
        ->setMesh(boxMesh)
        ->setMaterial(boxMaterial);

    //Create Shape
    auto dBoxShape = std::make_shared<OBB>(
    Vector3(-0.5f, -0.5f, -0.5f),  // half width/height of 50 for 100x100 box
    Vector3(0.5f, 0.5f, 0.5f));
    dBoxShape->initializeDebugDraw(mainRenderer->getRenderGraph(), camera);

    // Create instances of bodies for boxes
    dynamicBox->addComponent<RigidBody>()
        ->setMass(10.0f)->setDrag(100.0f)
        ->setShape(dBoxShape)
        ->setDebug(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());

    mainSceneGraph.addNode(dynamicBox);

#pragma endregion

#pragma region Floor

    auto floor = std::make_shared<GameObject>("Floor");
    floor->setLocalPosition(Vector3(0.0f, -1.0f, 0.0f))
        ->setLocalScaling(Vector3(10.0f, 0.05f, 10.0f));

    auto box2RenderComponent = floor->addComponent<Render2D>();
    box2RenderComponent
        ->setCamera(camera)
        ->setMesh(floorMesh)
        ->setMaterial(floorMaterial);

    auto shape2 = std::make_shared<OBB>(
    Vector3(-0.5f, -0.5f, -0.5f),  // half width/height of 50 for 100x100 box
    Vector3(0.5f, 0.5f, 0.5f));
    shape2->initializeDebugDraw(mainRenderer->getRenderGraph(), camera);

    floor->addComponent<RigidBody>()
        ->setMass(10.0f)->setDrag(100.0f)
        ->setShape(shape2)
        ->setDebug(true)
        ->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());

    mainSceneGraph.addNode(floor);

#pragma endregion

#pragma region Static Sound Box

    auto soundBox = std::make_shared<GameObject>("SoundBox");
    soundBox->setLocalPosition(Vector3(-10.0f, 0.75f, 10.0f))
        ->setLocalScaling(Vector3(0.5f, 0.5f, 0.5f));
    // Todo: when z is set to 1.0f, the bounding box debug gets very messed up.

    //Render Component
    auto soundBoxRenderComponent = soundBox->addComponent<Render2D>();
    soundBoxRenderComponent
        ->setCamera(camera)
        ->setMesh(boxMesh)
        ->setMaterial(boxMaterial);

    //Create Shape
    auto soundBoxShape = std::make_shared<OBB>(
    Vector3(-0.5f, -0.5f, -0.5f),  // half width/height of 50 for 100x100 box
    Vector3(0.5f, 0.5f, 0.5f));
    soundBoxShape->initializeDebugDraw(mainRenderer->getRenderGraph(), camera);

    // Create instances of bodies for boxes
    soundBox->addComponent<RigidBody>()
        ->setMass(10.0f)->setDrag(100.0f)
        ->setShape(soundBoxShape)
        ->setDebug(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());

    mainSceneGraph.addNode(soundBox);

    AudioManager::instance().playSound("music", soundBox.get()->getWorldTransform().getPosition(), 0.3f);

#pragma endregion


    CollisionListener boxTouch(dynamicBox);
    //boxTouch.setCallback();

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
    Vector3 affineRotEnd = Vector3(0.0, 2, 0.0);
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
        float t = 0.5f * (sin(affineCounter * affineSpeed) + 1.0);
        Vector3 affineCurrPos = affinePosStart + (affinePosEnd - affinePosStart) * t;
        soundBox.get()->setLocalPosition(affineCurrPos);
        Vector3 affineCurrRot = affineRotStart + (affineRotEnd - affineRotStart) * t;
        soundBox.get()->setLocalRotation(affineCurrRot);
        Vector3 affineCurrScl = affineSclStart + (affineSclEnd - affineSclStart) * t;
        soundBox.get()->setLocalScaling(affineCurrScl);

        //Audio Update
        AudioManager::instance().update();
        AudioManager::instance().setListenerPosition(playerBox.get()->getWorldTransform().getPosition());
        if (mainInput->isKeyPressed(KEY_SPACE)) {
            AudioManager::instance().playSound("pew");
        }
        if (mainInput->isKeyPressed(KEY_V)) {
            AudioManager::instance().togglePlaybackSpeed(0.7);
        }
        if (mainInput->isKeyPressed(KEY_M)) {
            AudioManager::instance().stopSound("radio");
        }

        //Light Manipulation
        if(mainInput->isKeyHeld(KEY_T)){
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
        mainRenderer->swapBuffers();
        mainWindow->update();

        //glfwSwapBuffers(window);

    }


    mainInput->shutdown();
    mainRenderer->shutdown();
    mainWindow->shutdown();
    AudioManager::instance().shutdown();

    delete mainInput;
    delete mainRenderer;
    delete mainWindow;

    return 0;
}
