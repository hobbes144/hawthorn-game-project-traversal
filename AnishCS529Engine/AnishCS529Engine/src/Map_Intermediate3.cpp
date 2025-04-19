/*!****************************************************************************
 * \file   Map_Intermediate3.cpp
 * \author Li Kuang (li.kuang@digipen.edu)
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#include "precompiled.h"
#include "MapLoader.h"
#include "Door.h"
#include "DeathPlane.h"
#include "InGameKey.h"

void MapLoader::intermediate3(
    float offsetX, float offsetY, float offsetZ,
    SceneGraph& sceneGraph) {
    

    {
        auto testDoor = std::make_shared<GameObject>("TestDoor", GameObject::WALL);
        sceneGraph.addNode(testDoor);
        testDoor->setLocalPosition(Vector3(270.0f + offsetX, 48.0f + offsetY, 0.0f + offsetZ));
        testDoor->setLocalScaling(Vector3(0.3f, 5.0f, 3.0f));
        auto renderComp = testDoor->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(BrownConcrete);
        auto shape = std::make_shared<OBB>();
        auto doorComp = testDoor->addComponent<Door>();
        doorComp->setID(1);
        doorComp->setType(Door::DoorType::NEXTLEVEL);
        doorComp->setRequiresKey(false);
        doorComp->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        doorComp->initialize();
    }

    Vector3 center(offsetX + 190, offsetY - 3, offsetZ);

    auto createWall = [&](const std::string& name, const Vector3& localPos, const Vector3& localScale) {
        auto wall = std::make_shared<GameObject>(name);
        sceneGraph.addNode(wall);
        wall->setLocalPosition(center + localPos);
        wall->setLocalScaling(localScale);

        auto renderComp = wall->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(LightBlueConcrete);

        auto shape = std::make_shared<OBB>();
        auto rigidBody = wall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
        };

    // Dimensions
    float size = 20.0f;
    float wallThickness = 1.0f;

    float width = 400.0f;
    float height = 100.0f;
    float depth = size;



    // Walls
    createWall("LeftWall", Vector3(-width / 2.0f, height / 2.0f, 0.0f), Vector3(wallThickness, height, depth));
    createWall("RightWall", Vector3(width / 2.0f, height / 2.0f, 0.0f), Vector3(wallThickness, height, depth));
    createWall("BackWall", Vector3(0.0f, height / 2.0f, depth / 2.0f), Vector3(width, height, wallThickness));
    createWall("FrontWall", Vector3(0.0f, height / 2.0f, -depth / 2.0f), Vector3(width, height, wallThickness));
    createWall("TopWall", Vector3(0.0f, height, 0.0f), Vector3(width, wallThickness, depth));
    createWall("BottomWall", Vector3(0.0f, 0.0f, 0.0f), Vector3(width, wallThickness, depth));
    
    {
        auto DP1 = std::make_shared<GameObject>("DP1");
        sceneGraph.addNode(DP1);
        DP1->setLocalPosition(Vector3(210.0f + offsetX, -2.0f + offsetY, 0.0f + offsetZ));
        DP1->setLocalScaling(Vector3(400.0f, 1.0f, 20.0f));
        //DP1->setLocalRotation(Vector3(0.0f, 1.57f, 0.0f));
        auto renderComp = DP1->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(cracksMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = DP1->addComponent<DeathPlane>();
        rigidBody->setPlayerName("PlayerBox");
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto Checkpoint1 = std::make_shared<GameObject>("Checkpoint1", GameObject::CHECKPOINT);
        sceneGraph.addNode(Checkpoint1);
        Checkpoint1->setLocalPosition(Vector3(0.0f + offsetX, -1.0f + offsetY, 0.0f + offsetZ));
        Checkpoint1->setLocalScaling(Vector3(20.0f, 1.0f, 20.0f));
        auto renderComp = Checkpoint1->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Checkpoint1->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto movingWallRun = [&](const std::string& name, const Vector3& resetPos, const Vector3& basePos, const Vector3& scale, const Vector3& moveDir, float offsetTime = 0.0f) {
            std::string wallName = name;
            auto wall = std::make_shared<GameObject>(wallName, GameObject::RUNNABLE_WALL);
            sceneGraph.addNode(wall);
            wall->setLocalPosition(basePos);
            wall->setLocalScaling(scale);
            wall->setLocalRotation(Vector3(0.0f, 0.0f, 0.0f));
            wall->addComponent<Render3D>()->setMesh(boxMesh)->setMaterial(BlueConcrete);
            auto rigidBody = wall->addComponent<RigidBody>();
            rigidBody->setMass(0.0f)
                ->setDrag(1.0f)
                ->setShape(std::make_shared<OBB>())
                ->setStatic(true)
                ->registerToPhysicsManager(PhysicsManager::Instance());
            rigidBody->initialize();
            wall->addComponent<Animate>()->setAnimateFunction(
                [moveVec = moveDir, resetPos, offsetTime,
                 firstCycle = true, time = 0.0f](std::shared_ptr<GameObject> self, float dt) mutable {

                             time += dt;
                             float cycleTime;
                             if (firstCycle) {
                                 cycleTime = offsetTime;
                             }
                             else {
                                 cycleTime = 25.0f;
                             }

                             if (time >= cycleTime) {
                                 self->setLocalPosition(resetPos);
                                 time = 0.0f;
                                 firstCycle = false;
                             }
                             else {
                                 self->setLocalPosition(self->getLocalPosition() + moveVec * dt);
                             }
                }
            )->runAnimateFunction(true);
            };
    
        int numLayers = 3;
        int wallPairCount = 5;
        float wallWidth = 40.0f, wallHeight = 20.0f, wallDepth = 1.0f;
        float moveSpeed = -10.0f;
        float offsetStep = 5.0f;
        float maxOffsetTime = 25.0f;
        float baseYs[3] = { 10.0f, 30.0f, 50.0f };
        float baseZ1 = 8.0f, baseZ2 = -8.0f;

        for (int layer = 0; layer < numLayers; ++layer)
        {
            float resetX1 = 200.0f + 50.0f * layer;
            float resetX2 = resetX1 + 20.0f;
            float baseY = baseYs[layer];
            for (int i = 0; i < wallPairCount; ++i)
            {
                float offsetTime = maxOffsetTime - i * offsetStep;
                float baseX1 = resetX1 - i * 50.0f;
                float baseX2 = resetX2 - i * 50.0f;

                movingWallRun(
                    "Wall1",
                    Vector3(resetX1, baseY, baseZ1),
                    Vector3(baseX1, baseY, baseZ1),
                    Vector3(wallWidth, wallHeight, wallDepth),
                    Vector3(moveSpeed, 0.0f, 0.0f),
                    offsetTime
                );
                movingWallRun(
                    "Wall2",
                    Vector3(resetX2, baseY, baseZ2),
                    Vector3(baseX2, baseY, baseZ2),
                    Vector3(wallWidth, wallHeight, wallDepth),
                    Vector3(moveSpeed, 0.0f, 0.0f),
                    offsetTime
                );
            }
        }

    }

    {
        auto Checkpoint2 = std::make_shared<GameObject>("Checkpoint2", GameObject::CHECKPOINT);
        sceneGraph.addNode(Checkpoint2);
        Checkpoint2->setLocalPosition(Vector3(260.0f + offsetX, 45.0f + offsetY, 0.0f + offsetZ));
        Checkpoint2->setLocalScaling(Vector3(20.0f, 1.0f, 20.0f));
        auto renderComp = Checkpoint2->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Checkpoint2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

}