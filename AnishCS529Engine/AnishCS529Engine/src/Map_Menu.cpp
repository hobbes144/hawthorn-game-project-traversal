#include "precompiled.h"
#include "MapLoader.h"
#include "Door.h"
#include "DeathPlane.h"
#include "InGameKey.h"

void MapLoader::menu(float offsetX, float offsetY, float offsetZ,
                            SceneGraph& sceneGraph) {

    auto boxRoomFloor = std::make_shared<GameObject>("BoxRoomFloor");
    sceneGraph.addNode(boxRoomFloor);
    boxRoomFloor->setLocalPosition(Vector3(offsetX, offsetY, offsetZ));
    boxRoomFloor->setLocalScaling(Vector3(20.0f, 1.0f, 20.0f));
    auto rc1 = boxRoomFloor->addComponent<Render3D>();
    rc1->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto s1 = std::make_shared<OBB>();
    auto rb1 = boxRoomFloor->addComponent<RigidBody>();
    rb1->setMass(0.0f)->setShape(s1)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb1->initialize();

    auto wallRight = std::make_shared<GameObject>("RoomWallRight");
    sceneGraph.addNode(wallRight);
    wallRight->setLocalPosition(Vector3(10.5f + offsetX, 7.0f + offsetY, offsetZ));
    wallRight->setLocalScaling(Vector3(1.0f, 15.0f, 20.0f));
    auto rc2 = wallRight->addComponent<Render3D>();
    rc2->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto s2 = std::make_shared<OBB>();
    auto rb2 = wallRight->addComponent<RigidBody>();
    rb2->setMass(0.0f)->setDrag(1.0f)->setShape(s2)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb2->initialize();

    auto wallBack = std::make_shared<GameObject>("RoomWallBack");
    sceneGraph.addNode(wallBack);
    wallBack->setLocalPosition(Vector3(offsetX, 7.0f + offsetY, -10.5f + offsetZ));
    wallBack->setLocalScaling(Vector3(20.0f, 15.0f, 1.0f));
    auto rc3 = wallBack->addComponent<Render3D>();
    rc3->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto s3 = std::make_shared<OBB>();
    auto rb3 = wallBack->addComponent<RigidBody>();
    rb3->setMass(0.0f)->setDrag(1.0f)->setShape(s3)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb3->initialize();

    auto wallFrontLeft = std::make_shared<GameObject>("RoomWallFrontLeft");
    sceneGraph.addNode(wallFrontLeft);
    wallFrontLeft->setLocalPosition(Vector3(-7.0f + offsetX, 7.0f + offsetY, 10.5f + offsetZ));
    wallFrontLeft->setLocalScaling(Vector3(7.5f, 15.0f, 1.0f));
    auto rc4 = wallFrontLeft->addComponent<Render3D>();
    rc4->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto s4 = std::make_shared<OBB>();
    auto rb4 = wallFrontLeft->addComponent<RigidBody>();
    rb4->setMass(0.0f)->setDrag(1.0f)->setShape(s4)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb4->initialize();

    auto wallFrontRight = std::make_shared<GameObject>("RoomWallFrontRight");
    sceneGraph.addNode(wallFrontRight);
    wallFrontRight->setLocalPosition(Vector3(7.0f + offsetX, 7.0f + offsetY, 10.5f + offsetZ));
    wallFrontRight->setLocalScaling(Vector3(7.5f, 15.0f, 1.0f));
    auto rc5 = wallFrontRight->addComponent<Render3D>();
    rc5->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto s5 = std::make_shared<OBB>();
    auto rb5 = wallFrontRight->addComponent<RigidBody>();
    rb5->setMass(0.0f)->setDrag(1.0f)->setShape(s5)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb5->initialize();

    auto roomCeiling = std::make_shared<GameObject>("BoxRoomCeiling");
    sceneGraph.addNode(roomCeiling);
    roomCeiling->setLocalPosition(Vector3(offsetX, 15.0f + offsetY, offsetZ));
    roomCeiling->setLocalScaling(Vector3(20.0f, 1.0f, 20.0f));
    auto rc6 = roomCeiling->addComponent<Render3D>();
    rc6->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto s6 = std::make_shared<OBB>();
    auto rb6 = roomCeiling->addComponent<RigidBody>();
    rb6->setMass(0.0f)->setDrag(1.0f)->setShape(s6)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb6->initialize();

    // Floor End
    auto tunnelFloor1 = std::make_shared<GameObject>("TunnelFloor1");
    sceneGraph.addNode(tunnelFloor1);
    tunnelFloor1->setLocalPosition(Vector3(-65.0f + offsetX, -15.5f + offsetY, offsetZ));
    tunnelFloor1->setLocalScaling(Vector3(10.0f, 1.0f, 10.0f));
    auto rc7a = tunnelFloor1->addComponent<Render3D>();
    rc7a->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto s7a = std::make_shared<OBB>();
    auto rb7a = tunnelFloor1->addComponent<RigidBody>();
    rb7a->setMass(0.0f)->setDrag(1.0f)->setShape(s7a)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb7a->initialize();

    // Floor Start
    auto tunnelFloor2 = std::make_shared<GameObject>("TunnelFloor2");
    sceneGraph.addNode(tunnelFloor2);
    tunnelFloor2->setLocalPosition(Vector3(-15.0f + offsetX, -15.5f + offsetY, offsetZ));
    tunnelFloor2->setLocalScaling(Vector3(10.0f, 1.0f, 10.0f));
    auto rc7b = tunnelFloor2->addComponent<Render3D>();
    rc7b->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto s7b = std::make_shared<OBB>();
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
    auto rc8 = tunnelWallLeft->addComponent<Render3D>();
    rc8->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto s8 = std::make_shared<OBB>();
    auto rb8 = tunnelWallLeft->addComponent<RigidBody>();
    rb8->setMass(0.0f)->setDrag(1.0f)->setShape(s8)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb8->initialize();

    auto tunnelWallRight = std::make_shared<GameObject>("TunnelWallRight");
    sceneGraph.addNode(tunnelWallRight);
    tunnelWallRight->setLocalPosition(Vector3(-40.0f + offsetX, 0.0f + offsetY, 5.0f + offsetZ));
    tunnelWallRight->setLocalScaling(Vector3(60.0f, 30.0f, 0.5f));
    auto rc9 = tunnelWallRight->addComponent<Render3D>();
    rc9->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto s9 = std::make_shared<OBB>();
    auto rb9 = tunnelWallRight->addComponent<RigidBody>();
    rb9->setMass(0.0f)->setDrag(1.0f)->setShape(s9)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb9->initialize();

    auto dropWall = std::make_shared<GameObject>("DropWall");
    sceneGraph.addNode(dropWall);
    dropWall->setLocalPosition(Vector3(-10.0f + offsetX, -7.5f + offsetY, offsetZ));
    dropWall->setLocalScaling(Vector3(0.5f, 15.0f, 10.0f));
    auto rcDW = dropWall->addComponent<Render3D>();
    rcDW->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto sDW = std::make_shared<OBB>();
    auto rbDW = dropWall->addComponent<RigidBody>();
    rbDW->setMass(0.0f)->setDrag(1.0f)->setShape(sDW)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rbDW->initialize();

    auto dropWall2 = std::make_shared<GameObject>("DropWall2");
    sceneGraph.addNode(dropWall2);
    dropWall2->setLocalPosition(Vector3(-20.0f + offsetX, 5.0f + offsetY, offsetZ));
    dropWall2->setLocalScaling(Vector3(0.5f, 20.0f, 10.0f));
    auto rcDW2 = dropWall2->addComponent<Render3D>();
    rcDW2->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto sDW2 = std::make_shared<OBB>();
    auto rbDW2 = dropWall2->addComponent<RigidBody>();
    rbDW2->setMass(0.0f)->setDrag(1.0f)->setShape(sDW2)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rbDW2->initialize();

    auto landingPlatform = std::make_shared<GameObject>("LandingPlatform");
    sceneGraph.addNode(landingPlatform);
    landingPlatform->setLocalPosition(Vector3(offsetX, 5.0f + offsetY, 20.0f + offsetZ));
    landingPlatform->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto rc10 = landingPlatform->addComponent<Render3D>();
    rc10->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto s10 = std::make_shared<OBB>();
    auto rb10 = landingPlatform->addComponent<RigidBody>();
    rb10->setMass(0.0f)->setDrag(1.0f)->setShape(s10)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb10->initialize();
}

