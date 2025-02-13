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
    mainWindow->setTitle("EngineDemo")->setHeight(windowHeight)->setWidth(windowWidth);
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

    /* Audio System Initalization */
    AudioManager::instance().initialize();
    AudioManager::instance().loadSound("pew", "media/audio/pew.mp3", true);
    AudioManager::instance().loadSound("music", "media/audio/1234.mp3", true, true);
    AudioManager::instance().setListenerPosition(Vector3(0, 0, 0));
    AudioManager::instance().playSound("music", Vector3(0, 0, 0));

    /* Scenegraph setup */
    SceneGraph mainSceneGraph;

    /* Camera setup */
    auto camera = std::make_shared<Camera>("mainCamera");
    camera->setPerspectiveProjection(
      45.0f * 3.14159f / 180.0f,
      mainWindow->getAspectRatio(),
      0.1f,
      1000.0f)
        ->setLocalPosition(Vector3(0.0f, 5.0f, 10.0f))
        ->setLocalRotation(Vector3(-0.55f, 0.0f, 0.0f));
    mainSceneGraph.addNode(camera);

    auto cameraShape = std::make_shared<OBB>(
        Vector3(-0.5f, -0.5f, -0.5f),  // half width/height of 50 for 100x100 box
        Vector3(0.5f, 0.5f, 0.5f));
    auto cameraPhysicsBodyComponent = camera->addComponent<PhysicsBody>()
        ->setMass(1.0f)->setFriction(1.0f)
        ->setShape(cameraShape)
        ->registerToPhysicsManager(PhysicsManager::Instance());

    /* Create relevant Meshes*/
    auto boxMesh = Mesh::createMesh("box", Mesh::Cube);
    auto boxMaterial = Material::getMaterial<TextureMaterial>("box", mainRenderer->getRenderGraph());

    // Drawable objects
    auto box1 = std::make_shared<GameObject>("Box1");
    box1->setLocalPosition(Vector3(2.0f, 0.5f, 0.0f))
        ->setLocalScaling(Vector3(1.0f, 1.f, 1.0f));
    // Todo: when z is set to 1.0f, the bounding box debug gets very messed up.

    auto box1RenderComponent = box1->addComponent<Render2D>();
    box1RenderComponent
        ->setCamera(camera)
        ->setMesh(boxMesh)
        ->setMaterial(boxMaterial);

    auto floor = std::make_shared<GameObject>("Floor");
    floor->setLocalPosition(Vector3(0.0f, -1.0f, 0.0f))
        ->setLocalScaling(Vector3(10.0f, 0.05f, 10.0f));

    auto box2RenderComponent = floor->addComponent<Render2D>();
    box2RenderComponent
        ->setCamera(camera)
        ->setMesh(boxMesh)
        ->setMaterial(boxMaterial);


    // Create OBBs
    auto shape1 = std::make_shared<OBB>(
        Vector3(-0.5f, -0.5f, -0.5f),  // half width/height of 50 for 100x100 box
        Vector3(0.5f, 0.5f, 0.5f));
    shape1->initializeDebugDraw(mainRenderer->getRenderGraph(), camera);
    // Todo: When Z scale is set to 0, the box no longer follows the object in
    // the Z axis.
    auto shape2 = std::make_shared<OBB>(
        Vector3(-0.5f, -0.5f, -0.5f),  // half width/height of 50 for 100x100 box
        Vector3(0.5f, 0.5f, 0.5f));
    shape2->initializeDebugDraw(mainRenderer->getRenderGraph(), camera);


    // Create instances of bodies for boxes
    box1->addComponent<PhysicsBody>()
        ->setMass(10.0f)->setFriction(100.0f)
        ->setShape(shape1)
        ->setDebug(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());

    floor->addComponent<PhysicsBody>()
        ->setMass(10.0f)->setFriction(100.0f)
        ->setShape(shape2)
        ->setDebug(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());

    CollisionListener boxTouch(floor);


    auto box1InputMovementComponent = box1->addComponent<Movement3D>()->setInputSystem(mainInput)
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

    mainSceneGraph.addNode(box1);
    mainSceneGraph.addNode(floor);

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

        mainInput->update();
        if (mainInput->isKeyHeld(KEY_ESCAPE))
            break;

        // Physics update loop fixedStepTime
        while (mainFramerateController->shouldUpdatePhysics()) {
            PhysicsManager::Instance().update(mainFramerateController->getPhysicsTimestep());
            mainFramerateController->consumePhysicsTime();
        }

        //Audio Update
        AudioManager::instance().update();
        AudioManager::instance().setListenerPosition(box1.get()->getWorldTransform().getPosition());

        if (mainInput->isKeyPressed(KEY_SPACE)) {
            AudioManager::instance().playSound("pew");
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
