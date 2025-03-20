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

//void addRigidBody(std::shared_ptr<GameObject> object, bool isStatic) {
//    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
//    object->addComponent<RigidBody>()
//        ->setMass(isStatic ? 0.0f : 10.0f)
//        ->setDrag(1.0f)
//        ->setShape(shape)
//        ->setStatic(isStatic)
//        ->registerToPhysicsManager(PhysicsManager::Instance())
//        ->initialize();
////Store the value gen by add rid comp in a variable and use it to call the init function
//}
void addRigidBody(std::shared_ptr<GameObject> object, bool isStatic) {
    auto shape = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rigidBody = object->addComponent<RigidBody>();
    rigidBody->setMass(isStatic ? 0.0f : 10.0f)
        ->setDrag(1.0f)
        ->setShape(shape)
        ->setStatic(isStatic)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
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
        mainFloorLeft->setLocalPosition(Vector3(-4.0f + offsetX, -20.0f + offsetY, 0.0f + offsetZ));
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
        addRigidBody(mainFloorRight, true);
    }

    // Wall for wall running
    {
        auto wallRunWall = std::make_shared<GameObject>("WallRunWall");
        sceneGraph.addNode(wallRunWall);
        wallRunWall->setLocalPosition(Vector3(18.0f + offsetX, 2.5f + offsetY, -4.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(30.0f, 8.0f, 1.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        addRigidBody(wallRunWall, true);
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
    addRigidBody(mainFloor, true);
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
    addRigidBody(platform, true);
}

// Exit platform
{
    auto upperFloor = std::make_shared<GameObject>("UpperFloor");
    sceneGraph.addNode(upperFloor);
    upperFloor->setLocalPosition(Vector3(60.0f + offsetX, 0.2f + offsetY, 8.0f + offsetZ));
    upperFloor->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto renderComp = upperFloor->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    addRigidBody(upperFloor, true);
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
        boxRoomFloor->setLocalScaling(Vector3(12.0f, 1.0f, 12.0f));
        auto renderComp = boxRoomFloor->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        addRigidBody(boxRoomFloor, true);
    }
    // Left wall
    {
        auto roomWallLeft = std::make_shared<GameObject>("RoomWallLeft");
        sceneGraph.addNode(roomWallLeft);
        roomWallLeft->setLocalPosition(Vector3(-6.0f + offsetX, 2.0f + offsetY, 0.0f + offsetZ));
        roomWallLeft->setLocalScaling(Vector3(1.0f, 4.0f, 12.0f));
        auto renderComp = roomWallLeft->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        addRigidBody(roomWallLeft, true);
    }
    // Right wall
    {
        auto roomWallRight = std::make_shared<GameObject>("RoomWallRight");
        sceneGraph.addNode(roomWallRight);
        roomWallRight->setLocalPosition(Vector3(6.0f + offsetX, 2.0f + offsetY, 0.0f + offsetZ));
        roomWallRight->setLocalScaling(Vector3(1.0f, 4.0f, 12.0f));
        auto renderComp = roomWallRight->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        addRigidBody(roomWallRight, true);
    }
    // Back wall
    {
        auto roomWallBack = std::make_shared<GameObject>("RoomWallBack");
        sceneGraph.addNode(roomWallBack);
        roomWallBack->setLocalPosition(Vector3(0.0f + offsetX, 2.0f + offsetY, -6.0f + offsetZ));
        roomWallBack->setLocalScaling(Vector3(12.0f, 4.0f, 1.0f));
        auto renderComp = roomWallBack->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        addRigidBody(roomWallBack, true);
    }
    // Front wall split into two parts to leave a gap (the tunnel entrance)
    {
        auto roomWallFrontLeft = std::make_shared<GameObject>("RoomWallFrontLeft");
        sceneGraph.addNode(roomWallFrontLeft);
        roomWallFrontLeft->setLocalPosition(Vector3(-4.0f + offsetX, 2.0f + offsetY, 6.0f + offsetZ));
        roomWallFrontLeft->setLocalScaling(Vector3(4.0f, 4.0f, 1.0f));
        auto renderComp = roomWallFrontLeft->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        addRigidBody(roomWallFrontLeft, true);
    }
    {
        auto roomWallFrontRight = std::make_shared<GameObject>("RoomWallFrontRight");
        sceneGraph.addNode(roomWallFrontRight);
        roomWallFrontRight->setLocalPosition(Vector3(4.0f + offsetX, 2.0f + offsetY, 6.0f + offsetZ));
        roomWallFrontRight->setLocalScaling(Vector3(4.0f, 4.0f, 1.0f));
        auto renderComp = roomWallFrontRight->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        addRigidBody(roomWallFrontRight, true);
    }

    // --- Tunnel ---
    // Tunnel floor
    {
        auto tunnelFloor = std::make_shared<GameObject>("TunnelFloor");
        sceneGraph.addNode(tunnelFloor);
        // Tunnel extends from the gap in the room’s front wall.
        // With a length of 12, the center is at z = 14 (tunnel spans z = 8 to 20).
        tunnelFloor->setLocalPosition(Vector3(0.0f + offsetX, 0.0f + offsetY, 14.0f + offsetZ));
        tunnelFloor->setLocalScaling(Vector3(3.0f, 1.0f, 12.0f));
        auto renderComp = tunnelFloor->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        addRigidBody(tunnelFloor, true);
    }
    // Tunnel left wall
    {
        auto tunnelWallLeft = std::make_shared<GameObject>("TunnelWallLeft");
        sceneGraph.addNode(tunnelWallLeft);
        // Position adjusted so that it sits along the left edge of the tunnel floor.
        tunnelWallLeft->setLocalPosition(Vector3(-1.75f + offsetX, 1.0f + offsetY, 14.0f + offsetZ));
        tunnelWallLeft->setLocalScaling(Vector3(0.5f, 3.0f, 12.0f));
        auto renderComp = tunnelWallLeft->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        addRigidBody(tunnelWallLeft, true);
    }
    // Tunnel right wall
    {
        auto tunnelWallRight = std::make_shared<GameObject>("TunnelWallRight");
        sceneGraph.addNode(tunnelWallRight);
        tunnelWallRight->setLocalPosition(Vector3(1.75f + offsetX, 1.0f + offsetY, 14.0f + offsetZ));
        tunnelWallRight->setLocalScaling(Vector3(0.5f, 3.0f, 12.0f));
        auto renderComp = tunnelWallRight->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        addRigidBody(tunnelWallRight, true);
    }
    // Tunnel ceiling
    {
        auto tunnelCeiling = std::make_shared<GameObject>("TunnelCeiling");
        sceneGraph.addNode(tunnelCeiling);
        tunnelCeiling->setLocalPosition(Vector3(0.0f + offsetX, 3.0f + offsetY, 14.0f + offsetZ));
        tunnelCeiling->setLocalScaling(Vector3(3.0f, 1.0f, 12.0f));
        auto renderComp = tunnelCeiling->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        addRigidBody(tunnelCeiling, true);
    }

    // --- Landing Platform (after the drop) ---
    {
        auto landingPlatform = std::make_shared<GameObject>("LandingPlatform");
        sceneGraph.addNode(landingPlatform);
        // The tunnel’s far end is at z = 20; position the landing platform below (y = -4)
        landingPlatform->setLocalPosition(Vector3(0.0f + offsetX, -4.0f + offsetY, 20.0f + offsetZ));
        landingPlatform->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
        auto renderComp = landingPlatform->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        addRigidBody(landingPlatform, true);
    }
    
}
