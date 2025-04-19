/*!****************************************************************************
 * \file   Map_Intermediate2.cpp
 * \author Li Kuang (li.kuang@digipen.edu) (Level Management/Raycasting)
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 * 
 *****************************************************************************/
#include "precompiled.h"
#include "MapLoader.h"
#include "Door.h"
#include "DeathPlane.h"
#include "InGameKey.h"

void MapLoader::intermediate2(
    float offsetX, float offsetY, float offsetZ,
    SceneGraph& sceneGraph) {


    {
        auto testDoor = std::make_shared<GameObject>("TestDoor", GameObject::WALL);
        sceneGraph.addNode(testDoor);
        testDoor->setLocalPosition(Vector3(0.0f + offsetX, 128.0f + offsetY, -32.0f + offsetZ));
        testDoor->setLocalScaling(Vector3(0.3f, 5.0f, 3.0f));
        testDoor->setLocalRotation(Vector3(0.0f, 1.57f, 0.0f));
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


    Vector3 center(offsetX, offsetY - 21, offsetZ);

    auto createWall = [&](const std::string& name, const Vector3& localPos, const Vector3& localScale) {
        auto wall = std::make_shared<GameObject>(name, GameObject::WALL);
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
    float size = 70.0f;
    float wallThickness = 1.0f;

    float width = size;
    float height = 200.0f;
    float depth = size;



    // Walls
    createWall("LeftWall", Vector3(-width / 2.0f, height / 2.0f, 0.0f), Vector3(wallThickness, height, depth));
    createWall("RightWall", Vector3(width / 2.0f, height / 2.0f, 0.0f), Vector3(wallThickness, height, depth));
    createWall("BackWall", Vector3(0.0f, height / 2.0f, depth / 2.0f), Vector3(width, height, wallThickness));
    createWall("FrontWall", Vector3(0.0f, height / 2.0f, -depth / 2.0f), Vector3(width, height, wallThickness));
    createWall("BottomWall", Vector3(0.0f, 0.0f, 0.0f), Vector3(width, wallThickness, depth));
    createWall("TopWall", Vector3(0.0f, height, 0.0f), Vector3(width, wallThickness, depth));



    {
        auto createFerrisWheel = [&](const std::string& name, const Vector3& center, int platformCount, float radius, float speed) {
            for (int i = 0; i < platformCount; ++i) {
                float initialAngle = (2.0f * 3.14159265f / platformCount) * i;
                std::string platformName = name + "_" + std::to_string(i);
                auto platform = std::make_shared<GameObject>(platformName);
                sceneGraph.addNode(platform);
                float xOffset = radius * std::cos(initialAngle);
                float yOffset = radius * std::sin(initialAngle);
                platform->setLocalPosition(center + Vector3(xOffset, yOffset, 0.0f));
                platform->setLocalScaling(Vector3(16.0f, 2.0f, 16.0f));
                platform->setLocalRotation(Vector3(0.0f, 0.0f, 0.0f));
                platform->addComponent<Render3D>()->setMesh(boxMesh)->setMaterial(concreteMaterial);
                auto rigidBody = platform->addComponent<RigidBody>();
                auto shape = std::make_shared<OBB>();
                rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)->registerToPhysicsManager(PhysicsManager::Instance());
                rigidBody->initialize();
                platform->addComponent<Animate>()->setAnimateFunction(
                    [angle = initialAngle, center, radius, speed](std::shared_ptr<GameObject> self, float deltaTime) mutable {
                        angle += deltaTime * speed;
                        float newX = center.x + radius * std::cos(angle);
                        float newY = center.y + radius * std::sin(angle);
                        self->setLocalPosition(Vector3(newX, newY, center.z));
                    }
                )->runAnimateFunction(true);
            }
            };

        //writeLetter(sceneGraph, "media/Map/words/arrow2.fbx", Vector3(75.0f + offsetX, 64.5f + offsetY, -77.0f + offsetZ),
        //        Vector3(0.1f, 0.1f, 0.01f), Vector3(0.0f, 0.0f, 5.7f), BrownConcrete);

        createFerrisWheel("Wheel1", Vector3(0.0f + offsetX, 6.0f + offsetY, 28.0f + offsetZ), 4, 25.0f, 5.0f);

        createFerrisWheel("Wheel1", Vector3(0.0f + offsetX, 46.0f + offsetY, -28.0f + offsetZ), 4, 25.0f, -5.0f);
    }

    {
        auto Box1 = std::make_shared<GameObject>("Box1");
        sceneGraph.addNode(Box1);
        Box1->setLocalPosition(Vector3(0.0f + offsetX, -1.0f + offsetY, -10.0f + offsetZ));
        Box1->setLocalScaling(Vector3(70.0f, 40.0f, 60.0f));
        auto renderComp = Box1->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Box1->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    createBlock(sceneGraph, "wall", Vector3(0.0f, 34.0f, -19.5f), Vector3(70.0f, 30.0f, 1.0f), concreteMaterial);
    createBlock(sceneGraph, "wall", Vector3(-20.0f, 34.0f, 0.0f), Vector3(70.0f, 30.0f, 40.0f), concreteMaterial);
    
    writeLetter(sceneGraph, "media/Map/words/arrow2.fbx", Vector3(23.0f, 27.0f, 34.0f), Vector3(0.03f, 0.03f, 0.01f), Vector3(0.0f, 0.0f, 0.0f), wordMaterial);
    writeLetter(sceneGraph, "media/Map/words/arrow2.fbx", Vector3(-33.0f, 35.0f, 27.0f), Vector3(0.03f, 0.03f, 0.01f), Vector3(0.0f, 1.57f, 0.0f), wordMaterial);
    writeLetter(sceneGraph, "media/Map/words/arrow2.fbx", Vector3(-33.0f, 60.0f, 29.0f), Vector3(0.03f, 0.03f, 0.01f), Vector3(-1.57f, 0.0f, 1.57f), wordMaterial);


    {
        auto firstCheckpoint = std::make_shared<GameObject>("firstCheckpoint", GameObject::CHECKPOINT);
        sceneGraph.addNode(firstCheckpoint);
        firstCheckpoint->setLocalPosition(Vector3(0.0f, 49.5f, 0.0f));
        firstCheckpoint->setLocalScaling(Vector3(70.0f, 1.0f, 40.0f));
        auto renderComp = firstCheckpoint->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = firstCheckpoint->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto TopFloorCheckpoint = std::make_shared<GameObject>("TopFloorCheckpoint", GameObject::CHECKPOINT);
        sceneGraph.addNode(TopFloorCheckpoint);
        TopFloorCheckpoint->setLocalPosition(Vector3(0.0f, 89.5f, 20.0f));
        TopFloorCheckpoint->setLocalScaling(Vector3(70.0f, 1.0f, 50.0f));
        auto renderComp = TopFloorCheckpoint->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = TopFloorCheckpoint->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }


    {
        auto exitCheckpoint = std::make_shared<GameObject>("exitCheckpoint", GameObject::CHECKPOINT);
        sceneGraph.addNode(exitCheckpoint);
        exitCheckpoint->setLocalPosition(Vector3(0.0f + offsetX, 125.0f + offsetY, -25.0f + offsetZ));
        exitCheckpoint->setLocalScaling(Vector3(15.0f, 1.0f, 15.0f));
        auto renderComp = exitCheckpoint->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = exitCheckpoint->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto createFerrisWheelZ = [&](const std::string& name, const Vector3& center, int platformCount, float radius, float speed) {
            for (int i = 0; i < platformCount; ++i) {
                float initialAngle = (2.0f * 3.14159265f / platformCount) * i;
                std::string platformName = name + "_" + std::to_string(i);
                auto platform = std::make_shared<GameObject>(platformName);
                sceneGraph.addNode(platform);
                float yOffset = radius * std::cos(initialAngle);
                float zOffset = radius * std::sin(initialAngle);
                platform->setLocalPosition(center + Vector3(0.0f, yOffset, zOffset));
                platform->setLocalScaling(Vector3(12.0f, 2.0f, 12.0f));
                platform->addComponent<Render3D>()->setMesh(boxMesh)->setMaterial(concreteMaterial);
                auto rigidBody = platform->addComponent<RigidBody>();
                auto shape = std::make_shared<OBB>();
                rigidBody->setMass(0.0f)->setDrag(1.0f)->setShape(shape)->setStatic(true)
                    ->registerToPhysicsManager(PhysicsManager::Instance());
                rigidBody->initialize();
                platform->addComponent<Animate>()->setAnimateFunction(
                    [angle = initialAngle, center, radius, speed](std::shared_ptr<GameObject> self, float deltaTime) mutable {
                        angle += deltaTime * speed;
                        float newY = center.y + radius * std::cos(angle);
                        float newZ = center.z + radius * std::sin(angle);
                        self->setLocalPosition(Vector3(center.x, newY, newZ));
                    }
                )->runAnimateFunction(true);
            }
            };

            createFerrisWheelZ("FerrisPlatformZ", Vector3(0.0f + offsetX, 105.0f + offsetY, 10.0f + offsetZ), 3, 13.0f, 4.0f);
       


    }
}