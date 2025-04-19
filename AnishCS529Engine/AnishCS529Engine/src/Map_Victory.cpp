/*!****************************************************************************
 * \file   Map_Victory.cpp
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


void MapLoader::victory(float offsetX, float offsetY, float offsetZ,
                            SceneGraph& sceneGraph) {

    Vector3 center(offsetX, offsetY, offsetZ);

    auto createWall = [&](const std::string& name, const Vector3& localPos, const Vector3& localScale) {
        auto wall = std::make_shared<GameObject>(name, GameObject::RUNNABLE_WALL);
        sceneGraph.addNode(wall);
        wall->setLocalPosition(center + localPos);
        wall->setLocalScaling(localScale);

        auto renderComp = wall->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(BlueConcrete);

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

    float width = size;
    float height = 30.0f;
    float depth = size;



    // Walls
    createWall("LeftWall", Vector3(-width / 2.0f, height / 2.0f, 0.0f), Vector3(wallThickness, height, depth));
    createWall("RightWall", Vector3(width / 2.0f, height / 2.0f, 0.0f), Vector3(wallThickness, height, depth));
    createWall("BackWall", Vector3(0.0f, height / 2.0f, depth / 2.0f), Vector3(width, height, wallThickness));
    createWall("FrontWall", Vector3(0.0f, height / 2.0f, -depth / 2.0f), Vector3(width, height, wallThickness));
    createWall("TopWall", Vector3(0.0f, height, 0.0f), Vector3(width, wallThickness, depth));
    createWall("BottomWall", Vector3(0.0f, 0.0f, 0.0f), Vector3(width, wallThickness, depth));

    {
        std::shared_ptr<Mesh> youwin = Mesh::loadMesh("media/Map/words/youwin.fbx");
        auto letter = std::make_shared<GameObject>("letter", GameObject::WALL);
        sceneGraph.addNode(letter);
        letter->setLocalPosition(Vector3(offsetX, 3.5f + offsetY, 7 + offsetZ));
        letter->setLocalScaling(Vector3(0.03f, 0.03f, 0.03f));
        auto renderComp = letter->addComponent<Render3D>();
        renderComp->setMesh(youwin)->setMaterial(keyMaterial);

    }

    {
        auto testDoor = std::make_shared<GameObject>("Door", GameObject::WALL);
        sceneGraph.addNode(testDoor);
        testDoor->setLocalPosition(Vector3(0.0f + offsetX, 2.5f + offsetY, 9.0f + offsetZ));
        testDoor->setLocalScaling(Vector3(0.3f, 5.0f, 3.0f));
        testDoor->setLocalRotation(Vector3(0.0f, 1.57f, 0.0f));
        auto renderComp = testDoor->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(BrownConcrete);
        auto shape = std::make_shared<OBB>();
        auto doorComp = testDoor->addComponent<Door>();
        doorComp->setID(0);
        doorComp->setType(Door::NEXTLEVEL);
        doorComp->setRequiresKey(false);
        doorComp->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        doorComp->initialize();
    }
}