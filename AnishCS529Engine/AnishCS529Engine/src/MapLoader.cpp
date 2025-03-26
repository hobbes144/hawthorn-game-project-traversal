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
                      SceneGraph& sceneGraph,
                      std::shared_ptr<Camera> camera,
                      std::shared_ptr<Mesh> floorMesh,
                      std::shared_ptr<Material> floorMaterial) {
    auto boxRoomFloor = std::make_shared<GameObject>("BoxRoomFloor");
    sceneGraph.addNode(boxRoomFloor);
    boxRoomFloor->setLocalPosition(Vector3(offsetX, offsetY, offsetZ));
    boxRoomFloor->setLocalScaling(Vector3(20.0f, 1.0f, 20.0f));
    auto rc1 = boxRoomFloor->addComponent<Render2D>();
    rc1->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto s1 = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rb1 = boxRoomFloor->addComponent<RigidBody>();
    rb1->setMass(0.0f)->setShape(s1)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb1->initialize();

    auto wallRight = std::make_shared<GameObject>("RoomWallRight");
    sceneGraph.addNode(wallRight);
    wallRight->setLocalPosition(Vector3(10.5f + offsetX, 7.0f + offsetY, offsetZ));
    wallRight->setLocalScaling(Vector3(1.0f, 15.0f, 20.0f));
    auto rc2 = wallRight->addComponent<Render2D>();
    rc2->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto s2 = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rb2 = wallRight->addComponent<RigidBody>();
    rb2->setMass(0.0f)->setDrag(1.0f)->setShape(s2)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb2->initialize();

    auto wallBack = std::make_shared<GameObject>("RoomWallBack");
    sceneGraph.addNode(wallBack);
    wallBack->setLocalPosition(Vector3(offsetX, 7.0f + offsetY, -10.5f + offsetZ));
    wallBack->setLocalScaling(Vector3(20.0f, 15.0f, 1.0f));
    auto rc3 = wallBack->addComponent<Render2D>();
    rc3->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto s3 = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rb3 = wallBack->addComponent<RigidBody>();
    rb3->setMass(0.0f)->setDrag(1.0f)->setShape(s3)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb3->initialize();

    auto wallFrontLeft = std::make_shared<GameObject>("RoomWallFrontLeft");
    sceneGraph.addNode(wallFrontLeft);
    wallFrontLeft->setLocalPosition(Vector3(-7.0f + offsetX, 7.0f + offsetY, 10.5f + offsetZ));
    wallFrontLeft->setLocalScaling(Vector3(7.5f, 15.0f, 1.0f));
    auto rc4 = wallFrontLeft->addComponent<Render2D>();
    rc4->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto s4 = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rb4 = wallFrontLeft->addComponent<RigidBody>();
    rb4->setMass(0.0f)->setDrag(1.0f)->setShape(s4)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb4->initialize();

    auto wallFrontRight = std::make_shared<GameObject>("RoomWallFrontRight");
    sceneGraph.addNode(wallFrontRight);
    wallFrontRight->setLocalPosition(Vector3(7.0f + offsetX, 7.0f + offsetY, 10.5f + offsetZ));
    wallFrontRight->setLocalScaling(Vector3(7.5f, 15.0f, 1.0f));
    auto rc5 = wallFrontRight->addComponent<Render2D>();
    rc5->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto s5 = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rb5 = wallFrontRight->addComponent<RigidBody>();
    rb5->setMass(0.0f)->setDrag(1.0f)->setShape(s5)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb5->initialize();

    auto roomCeiling = std::make_shared<GameObject>("BoxRoomCeiling");
    sceneGraph.addNode(roomCeiling);
    roomCeiling->setLocalPosition(Vector3(offsetX, 15.0f + offsetY, offsetZ));
    roomCeiling->setLocalScaling(Vector3(20.0f, 1.0f, 20.0f));
    auto rc6 = roomCeiling->addComponent<Render2D>();
    rc6->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto s6 = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rb6 = roomCeiling->addComponent<RigidBody>();
    rb6->setMass(0.0f)->setDrag(1.0f)->setShape(s6)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb6->initialize();

    // Floor End
    auto tunnelFloor1 = std::make_shared<GameObject>("TunnelFloor1");
    sceneGraph.addNode(tunnelFloor1);
    tunnelFloor1->setLocalPosition(Vector3(-65.0f + offsetX, -15.5f + offsetY, offsetZ));
    tunnelFloor1->setLocalScaling(Vector3(10.0f, 1.0f, 10.0f));
    auto rc7a = tunnelFloor1->addComponent<Render2D>();
    rc7a->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto s7a = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rb7a = tunnelFloor1->addComponent<RigidBody>();
    rb7a->setMass(0.0f)->setDrag(1.0f)->setShape(s7a)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb7a->initialize();

    // Floor Start
    auto tunnelFloor2 = std::make_shared<GameObject>("TunnelFloor2");
    sceneGraph.addNode(tunnelFloor2);
    tunnelFloor2->setLocalPosition(Vector3(-15.0f + offsetX, -15.5f + offsetY, offsetZ));
    tunnelFloor2->setLocalScaling(Vector3(10.0f, 1.0f, 10.0f));
    auto rc7b = tunnelFloor2->addComponent<Render2D>();
    rc7b->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto s7b = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rb7b = tunnelFloor2->addComponent<RigidBody>();
    rb7b->setMass(0.0f)->setDrag(1.0f)->setShape(s7b)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb7b->initialize();

    // All tunnel walls now have Y=30 (15 units more than before),
    // and are repositioned so bottom stays at -15 and top goes to +15.
    auto tunnelWallLeft = std::make_shared<GameObject>("TunnelWallLeft");
    sceneGraph.addNode(tunnelWallLeft);
    tunnelWallLeft->setLocalPosition(Vector3(-40.0f + offsetX, 0.0f + offsetY, -5.0f + offsetZ));
    tunnelWallLeft->setLocalScaling(Vector3(60.0f, 30.0f, 0.5f));
    auto rc8 = tunnelWallLeft->addComponent<Render2D>();
    rc8->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto s8 = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rb8 = tunnelWallLeft->addComponent<RigidBody>();
    rb8->setMass(0.0f)->setDrag(1.0f)->setShape(s8)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb8->initialize();

    auto tunnelWallRight = std::make_shared<GameObject>("TunnelWallRight");
    sceneGraph.addNode(tunnelWallRight);
    tunnelWallRight->setLocalPosition(Vector3(-40.0f + offsetX, 0.0f + offsetY, 5.0f + offsetZ));
    tunnelWallRight->setLocalScaling(Vector3(60.0f, 30.0f, 0.5f));
    auto rc9 = tunnelWallRight->addComponent<Render2D>();
    rc9->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto s9 = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rb9 = tunnelWallRight->addComponent<RigidBody>();
    rb9->setMass(0.0f)->setDrag(1.0f)->setShape(s9)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb9->initialize();

    auto dropWall = std::make_shared<GameObject>("DropWall");
    sceneGraph.addNode(dropWall);
    dropWall->setLocalPosition(Vector3(-10.0f + offsetX, -7.5f + offsetY, offsetZ));
    dropWall->setLocalScaling(Vector3(0.5f, 15.0f, 10.0f));
    auto rcDW = dropWall->addComponent<Render2D>();
    rcDW->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto sDW = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rbDW = dropWall->addComponent<RigidBody>();
    rbDW->setMass(0.0f)->setDrag(1.0f)->setShape(sDW)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rbDW->initialize();

    auto dropWall2 = std::make_shared<GameObject>("DropWall2");
    sceneGraph.addNode(dropWall2);
    dropWall2->setLocalPosition(Vector3(-20.0f + offsetX, 5.0f + offsetY, offsetZ));
    dropWall2->setLocalScaling(Vector3(0.5f, 20.0f, 10.0f));
    auto rcDW2 = dropWall2->addComponent<Render2D>();
    rcDW2->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto sDW2 = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rbDW2 = dropWall2->addComponent<RigidBody>();
    rbDW2->setMass(0.0f)->setDrag(1.0f)->setShape(sDW2)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rbDW2->initialize();

    auto landingPlatform = std::make_shared<GameObject>("LandingPlatform");
    sceneGraph.addNode(landingPlatform);
    landingPlatform->setLocalPosition(Vector3(offsetX, 5.0f + offsetY, 20.0f + offsetZ));
    landingPlatform->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto rc10 = landingPlatform->addComponent<Render2D>();
    rc10->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto s10 = std::make_shared<OBB>(Vector3(0.5f, 0.5f, 0.5f));
    auto rb10 = landingPlatform->addComponent<RigidBody>();
    rb10->setMass(0.0f)->setDrag(1.0f)->setShape(s10)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb10->initialize();
}
