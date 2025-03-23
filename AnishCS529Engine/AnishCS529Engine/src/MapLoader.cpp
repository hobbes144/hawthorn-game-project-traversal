#include "precompiled.h"
#include "MapLoader.h"
#include <iostream>
#include <string>
#include "Render2D.h"
#include "RigidBody.h"
#include "OBB.h"

MapLoader& MapLoader::instance() {
    static MapLoader instance;
    return instance;
}

void MapLoader::loadMap(int mapId, float offsetX, float offsetY, float offsetZ,
                        SceneGraph& sceneGraph,
                        std::shared_ptr<Camera> camera,
                        std::shared_ptr<Mesh> floorMesh,
                        std::shared_ptr<Material> floorMaterial) {
    switch (mapId) {
    case 1:
        loadWallrun(offsetX, offsetY, offsetZ, sceneGraph, camera, floorMesh, floorMaterial);
        break;
    case 2:
        loadJump(offsetX, offsetY, offsetZ, sceneGraph, camera, floorMesh, floorMaterial);
        break;
    case 3:
        three(offsetX, offsetY, offsetZ, sceneGraph, camera, floorMesh, floorMaterial);
        break;
    default:
        std::cerr << "[MapLoader] Map ID " << mapId << " is not recognized.\n";
        break;
    }
}

// Wallrun map 
void MapLoader::loadWallrun(float offsetX, float offsetY, float offsetZ,
                            SceneGraph& sceneGraph,
                            std::shared_ptr<Camera> camera,
                            std::shared_ptr<Mesh> floorMesh,
                            std::shared_ptr<Material> floorMaterial) {
    // Left pad
    {
        auto mainFloorLeft = std::make_shared<GameObject>("MainFloorLeft");
        sceneGraph.addNode(mainFloorLeft);
        mainFloorLeft->setLocalPosition(Vector3(-4.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        mainFloorLeft->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
        auto renderComp = mainFloorLeft->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
        auto rigidBody = mainFloorLeft->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();


    }

    // Right pad
    {
        auto mainFloorRight = std::make_shared<GameObject>("MainFloorRight");
        sceneGraph.addNode(mainFloorRight);
        mainFloorRight->setLocalPosition(Vector3(40.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        mainFloorRight->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
        auto renderComp = mainFloorRight->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
        auto rigidBody = mainFloorRight->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Wall for wall running
    {
        auto wallRunWall = std::make_shared<GameObject>("WallRunWall");
        sceneGraph.addNode(wallRunWall);
        wallRunWall->setLocalPosition(Vector3(18.0f + offsetX, 2.5f + offsetY, 4.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(30.0f, 8.0f, 1.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
        auto rigidBody = wallRunWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }
}

// Jump map
void MapLoader::loadJump(float offsetX, float offsetY, float offsetZ,
                         SceneGraph& sceneGraph,
                         std::shared_ptr<Camera> camera,
                         std::shared_ptr<Mesh> floorMesh,
                         std::shared_ptr<Material> floorMaterial) {
    // Starting platform
{
    auto mainFloor = std::make_shared<GameObject>("MainFloor");
    sceneGraph.addNode(mainFloor);
    mainFloor->setLocalPosition(Vector3(0.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
    mainFloor->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto renderComp = mainFloor->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = mainFloor->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)
        ->setDrag(1.0f)
        ->setShape(shape)
        ->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}

float platformSizes[] = { 4.0f, 3.5f, 3.0f, 3.2f, 3.6f, 3.1f, 3.4f, 3.7f, 4.2f };
float yVariation[] = { 0.3f, -0.2f, 0.5f, -0.4f, 0.2f, -0.3f, 0.4f, -0.2f, 0.1f };
float xSpacing = 6.0f;
float xOffset[] = { 2.0f, 2.0f, -3.0f, 3.0f, -4.0f, 4.0f, -5.0f, 5.0f, 8.0f };

for (int i = 0; i < 9; ++i) {
    auto platform = std::make_shared<GameObject>("Platform" + std::to_string(i + 1));
    sceneGraph.addNode(platform);
    float adjustedX = (i == 0) ? (xSpacing * 1.5f) : ((i + 1) * xSpacing + 5.0f);
    platform->setLocalPosition(Vector3(adjustedX + offsetX, yVariation[i] + offsetY, xOffset[i] + offsetZ));
    platform->setLocalScaling(Vector3(platformSizes[i], 0.5f, platformSizes[i]));
    auto renderComp = platform->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = platform->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)
        ->setDrag(1.0f)
        ->setShape(shape)
        ->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}

// Exit platform
{
    auto upperFloor = std::make_shared<GameObject>("UpperFloor");
    sceneGraph.addNode(upperFloor);
    upperFloor->setLocalPosition(Vector3(60.0f + offsetX, 0.2f + offsetY, 8.0f + offsetZ));
    upperFloor->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto renderComp = upperFloor->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = upperFloor->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)
        ->setDrag(1.0f)
        ->setShape(shape)
        ->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}
}
void MapLoader::three(float offsetX, float offsetY, float offsetZ,
                              SceneGraph & sceneGraph,
                              std::shared_ptr<Camera> camera,
                              std::shared_ptr<Mesh> floorMesh,
                              std::shared_ptr<Material> floorMaterial) {
        // --- Room (Box) ---
 // Room floor
{
    auto boxRoomFloor = std::make_shared<GameObject>("BoxRoomFloor");
    sceneGraph.addNode(boxRoomFloor);
    boxRoomFloor->setLocalPosition(Vector3(0.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
    boxRoomFloor->setLocalScaling(Vector3(20.0f, 1.0f, 20.0f));
    auto renderComp = boxRoomFloor->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = boxRoomFloor->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}
// Left wall
{
    auto wall = std::make_shared<GameObject>("RoomWallLeft");
    sceneGraph.addNode(wall);
    wall->setLocalPosition(Vector3(-10.5f + offsetX, 7.0f + offsetY, 0.0f + offsetZ));
    wall->setLocalScaling(Vector3(1.0f, 15.0f, 20.0f));
    auto renderComp = wall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = wall->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}
// Right wall
{
    auto wall = std::make_shared<GameObject>("RoomWallRight");
    sceneGraph.addNode(wall);
    wall->setLocalPosition(Vector3(10.5f + offsetX, 7.0f + offsetY, 0.0f + offsetZ));
    wall->setLocalScaling(Vector3(1.0f, 15.0f, 20.0f));
    auto renderComp = wall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = wall->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}
// Back wall
{
    auto wall = std::make_shared<GameObject>("RoomWallBack");
    sceneGraph.addNode(wall);
    wall->setLocalPosition(Vector3(0.0f + offsetX, 7.0f + offsetY, -10.5f + offsetZ));
    wall->setLocalScaling(Vector3(20.0f, 15.0f, 1.0f));
    auto renderComp = wall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = wall->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}
// Front left wall
{
    auto wall = std::make_shared<GameObject>("RoomWallFrontLeft");
    sceneGraph.addNode(wall);
    wall->setLocalPosition(Vector3(-7.0f + offsetX, 7.0f + offsetY, 10.5f + offsetZ));
    wall->setLocalScaling(Vector3(7.5f, 15.0f, 1.0f));
    auto renderComp = wall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = wall->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}
// Front right wall
{
    auto wall = std::make_shared<GameObject>("RoomWallFrontRight");
    sceneGraph.addNode(wall);
    wall->setLocalPosition(Vector3(7.0f + offsetX, 7.0f + offsetY, 10.5f + offsetZ));
    wall->setLocalScaling(Vector3(7.5f, 15.0f, 1.0f));
    auto renderComp = wall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = wall->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}
// Tunnel floor
{
    auto tunnel = std::make_shared<GameObject>("TunnelFloor");
    sceneGraph.addNode(tunnel);
    tunnel->setLocalPosition(Vector3(0.0f + offsetX, 0.0f + offsetY, 14.0f + offsetZ));
    tunnel->setLocalScaling(Vector3(3.0f, 1.0f, 12.0f));
    auto renderComp = tunnel->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = tunnel->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}
// Tunnel left wall
{
    auto wall = std::make_shared<GameObject>("TunnelWallLeft");
    sceneGraph.addNode(wall);
    wall->setLocalPosition(Vector3(-1.75f + offsetX, 1.0f + offsetY, 14.0f + offsetZ));
    wall->setLocalScaling(Vector3(0.5f, 3.0f, 12.0f));
    auto renderComp = wall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = wall->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}
// Tunnel right wall
{
    auto wall = std::make_shared<GameObject>("TunnelWallRight");
    sceneGraph.addNode(wall);
    wall->setLocalPosition(Vector3(1.75f + offsetX, 1.0f + offsetY, 14.0f + offsetZ));
    wall->setLocalScaling(Vector3(0.5f, 3.0f, 12.0f));
    auto renderComp = wall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = wall->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}
// Tunnel ceiling
{
    auto ceiling = std::make_shared<GameObject>("TunnelCeiling");
    sceneGraph.addNode(ceiling);
    ceiling->setLocalPosition(Vector3(0.0f + offsetX, 3.0f + offsetY, 14.0f + offsetZ));
    ceiling->setLocalScaling(Vector3(3.0f, 1.0f, 12.0f));
    auto renderComp = ceiling->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = ceiling->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}
// Landing platform
{
    auto platform = std::make_shared<GameObject>("LandingPlatform");
    sceneGraph.addNode(platform);
    platform->setLocalPosition(Vector3(0.0f + offsetX, -4.0f + offsetY, 20.0f + offsetZ));
    platform->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto renderComp = platform->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = platform->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}
}
