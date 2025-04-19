/*!****************************************************************************
 * \file   Map_Tutorial2.cpp
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

void MapLoader::tutorial2(
    float offsetX, float offsetY, float offsetZ,
    SceneGraph& sceneGraph) {

    // Keys & Doors test
    {
        std::shared_ptr<Mesh> keyMesh = Mesh::loadMesh("media/Map/key.fbx");
        auto key = std::make_shared<GameObject>("key", GameObject::WALL);
        sceneGraph.addNode(key);
        key->setLocalPosition(Vector3(Vector3(-238.0f + offsetX, 5.0f + offsetY, 0.0f + offsetZ)));
        key->setLocalScaling(Vector3(0.005f, 0.005f, 0.005f));
        auto renderComp = key->addComponent<Render3D>();
        renderComp->setMesh(keyMesh)->setMaterial(keyMaterial);

        auto shape = std::make_shared<OBB>(Vector3(0, 0, 0), Vector3(1.0f / 0.005f, 2.0f / 0.005f, 1.0f / 0.005f));
        auto keyComp = key->addComponent<InGameKey>();
        keyComp->setID(0);
        keyComp->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        keyComp->initialize();

        key->addComponent<Animate>()->setAnimateFunction(
             [rotationSpeed = 45.0f, amplitude = 1.0f, currentTime = 0.0f, initialPos = key->getLocalPosition()]
             (std::shared_ptr<GameObject> self, float deltaTime) mutable {
                 currentTime += deltaTime;
                 float yOffset = amplitude * std::sin(currentTime);
                 Vector3 newPos = initialPos;
                 newPos.y += yOffset;
                 self->setLocalPosition(newPos);
                 float radians = rotationSpeed * deltaTime * (3.14159265f / 180.0f);
                 self->setLocalRotation(Quaternion::fromEuler(0.0f, radians, 0.0f) * self->getLocalRotation());
             }
        )->runAnimateFunction(true);
    }
    {
        auto testDoor = std::make_shared<GameObject>("Door", GameObject::WALL);
        sceneGraph.addNode(testDoor);
        testDoor->setLocalPosition(Vector3(-399.7f + offsetX, -2.5f + offsetY, 0.0f + offsetZ));
        testDoor->setLocalScaling(Vector3(0.3f, 5.0f, 3.0f));
        auto renderComp = testDoor->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(BrownConcrete);
        auto shape = std::make_shared<OBB>();
        auto doorComp = testDoor->addComponent<Door>();
        doorComp->setID(0);
        doorComp->setType(Door::DoorType::NEXTLEVEL);
        doorComp->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        doorComp->initialize();
    }
    // Room walls
    {
        auto LeftWall = std::make_shared<GameObject>("LeftWall", GameObject::WALL);
        sceneGraph.addNode(LeftWall);
        LeftWall->setLocalPosition(Vector3(-200.0f + offsetX, 4.0f + offsetY, 10.1f + offsetZ));
        LeftWall->setLocalScaling(Vector3(420.0f, 150.0f, 1.0f));
        auto renderComp = LeftWall->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(LightBlueConcrete);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = LeftWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto RightWall = std::make_shared<GameObject>("RightWall", GameObject::WALL);
        sceneGraph.addNode(RightWall);
        RightWall->setLocalPosition(Vector3(-200.0f + offsetX, 4.0f + offsetY, -10.1f + offsetZ));
        RightWall->setLocalScaling(Vector3(420.0f, 150.0f, 1.0f));
        auto renderComp = RightWall->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(LightBlueConcrete);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = RightWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto BackWall = std::make_shared<GameObject>("BackWall", GameObject::WALL);
        sceneGraph.addNode(BackWall);
        BackWall->setLocalPosition(Vector3(10.5f + offsetX, 4.0f + offsetY, 0.0f + offsetZ));
        BackWall->setLocalScaling(Vector3(1.0f, 150.0f, 20.0f));
        auto renderComp = BackWall->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(LightBlueConcrete);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = BackWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto FrontWall = std::make_shared<GameObject>("FrontWall", GameObject::WALL);
        sceneGraph.addNode(FrontWall);
        FrontWall->setLocalPosition(Vector3(-400.5f + offsetX, 4.0f + offsetY, 0.0f + offsetZ));
        FrontWall->setLocalScaling(Vector3(1.0f, 150.0f, 20.0f));
        auto renderComp = FrontWall->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(LightBlueConcrete);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = FrontWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto TopWall = std::make_shared<GameObject>("TopWall", GameObject::WALL);
        sceneGraph.addNode(TopWall);
        TopWall->setLocalPosition(Vector3(-200.0f + offsetX, 44.0f + offsetY, 0.0f + offsetZ));
        TopWall->setLocalScaling(Vector3(420.0f, 10.0f, 20.0f));
        auto renderComp = TopWall->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(LightBlueConcrete);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = TopWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // deathplane test
    {
        auto DP1 = std::make_shared<GameObject>("DP1");
        sceneGraph.addNode(DP1);
        DP1->setLocalPosition(Vector3(-200.0f + offsetX, -50.0f + offsetY, 0.0f + offsetZ));
        DP1->setLocalScaling(Vector3(420.0f, 1.0f, 20.0f));
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

    // Floor1 pad
    {
        auto Floor1 = std::make_shared<GameObject>("Floor1");
        sceneGraph.addNode(Floor1);
        Floor1->setLocalPosition(Vector3(-10.0f + offsetX, -5.0f + offsetY, 0.0f + offsetZ));
        Floor1->setLocalScaling(Vector3(50.0f, 10.0f, 20.0f));
        Floor1->setLocalRotation(Vector3(0.0f, 0.0f, 0.0f));
        auto renderComp = Floor1->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Floor1->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }
    //// Box1
    //{
    //    auto Box1 = std::make_shared<GameObject>("Box1");
    //    sceneGraph.addNode(Box1);
    //    Box1->setLocalPosition(Vector3(-20.0f + offsetX, 1.0f + offsetY, 0.0f + offsetZ));
    //    Box1->setLocalScaling(Vector3(10.0f, 5.0f, 20.0f));
    //    auto renderComp = Box1->addComponent<Render3D>();
    //    renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
    //    auto shape = std::make_shared<OBB>();
    //    auto rigidBody = Box1->addComponent<RigidBody>();
    //    rigidBody->setMass(0.0f)
    //        ->setDrag(1.0f)
    //        ->setShape(shape)
    //        ->setStatic(true)
    //        ->registerToPhysicsManager(PhysicsManager::Instance());
    //    rigidBody->initialize();
    //}
    
    writeLetter(sceneGraph, "media/Map/words/ctrl.fbx", Vector3(-43.0f + offsetX, 1.0f + offsetY, 1.5f + offsetZ),
Vector3(0.02f, 0.02f, 0.02f), Vector3(0.0f, -1.57f, 0.0f), wordMaterial);
    writeLetter(sceneGraph, "media/Map/words/+.fbx", Vector3(-43.0f + offsetX, 1.7f + offsetY, 0.0f + offsetZ),
    Vector3(0.02f, 0.02f, 0.02f), Vector3(0.0f, -1.57f, 0.0f), wordMaterial);
    writeLetter(sceneGraph, "media/Map/words/space.fbx", Vector3(-43.0f + offsetX, 0.9f + offsetY, -5.0f + offsetZ),
Vector3(0.02f, 0.02f, 0.02f), Vector3(0.0f, -1.57f, 0.0f), wordMaterial);

    // Pit wall
    /*{
        auto pitWall1 = std::make_shared<GameObject>("pitWall1");
        sceneGraph.addNode(pitWall1);
        pitWall1->setLocalPosition(Vector3(-34.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall1->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall1->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall1->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto pitWall2 = std::make_shared<GameObject>("pitWall2");
        sceneGraph.addNode(pitWall2);
        pitWall2->setLocalPosition(Vector3(-65.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall2->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall2->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }*/

    // Pit floor
    {
        auto pitFloor = std::make_shared<GameObject>("pitFloor");
        sceneGraph.addNode(pitFloor);
        pitFloor->setLocalPosition(Vector3(-54.0f + offsetX, -10.0f + offsetY, 0.0f + offsetZ));
        pitFloor->setLocalScaling(Vector3(30.0f, 1.0f, 20.0f));
        auto renderComp = pitFloor->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitFloor->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }
    writeLetter(sceneGraph, "media/Map/words/space.fbx", Vector3(-148.0f + offsetX, 5.9f + offsetY, 5.0f + offsetZ),
Vector3(0.02f, 0.02f, 0.02f), Vector3(0.0f, -1.57f, 0.0f), wordMaterial);
    writeLetter(sceneGraph, "media/Map/words/+.fbx", Vector3(-148.0f + offsetX, 6.7f + offsetY, 3.0f + offsetZ),
Vector3(0.02f, 0.02f, 0.02f), Vector3(0.0f, -1.57f, 0.0f), wordMaterial);
    writeLetter(sceneGraph, "media/Map/words/DASH.fbx", Vector3(-148.0f + offsetX, 6.0f + offsetY - 0.3f, -2.5f + offsetZ + 0.7f),
Vector3(0.02f, 0.02f, 0.02f), Vector3(0.0f, -1.57f, 0.0f), wordMaterial);
    writeLetter(sceneGraph, "media/Map/words/space.fbx", Vector3(-148.0f + offsetX, 5.9f + offsetY, -7.5f + offsetZ),
Vector3(0.02f, 0.02f, 0.02f), Vector3(0.0f, -1.57f, 0.0f), wordMaterial);


    // Pit box
    {
        auto pitBox = std::make_shared<GameObject>("pitBox");
        sceneGraph.addNode(pitBox);
        pitBox->setLocalPosition(Vector3(-35.0f + offsetX, -10.0f + offsetY, 0.0f + offsetZ));
        pitBox->setLocalScaling(Vector3(20.0f, 10.0f, 20.0f));
        auto renderComp = pitBox->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitBox->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Floor2 pad
    {
        auto Floor2 = std::make_shared<GameObject>("Floor2", GameObject::CHECKPOINT);
        sceneGraph.addNode(Floor2);
        Floor2->setLocalPosition(Vector3(-75.0f + offsetX, -5.0f + offsetY, 0.0f + offsetZ));
        Floor2->setLocalScaling(Vector3(20.0f, 10.0f, 20.0f));
        auto renderComp = Floor2->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Floor2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Drop Pit 1
    {
        auto pitWall1 = std::make_shared<GameObject>("pitWall1");
        sceneGraph.addNode(pitWall1);
        pitWall1->setLocalPosition(Vector3(-84.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall1->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall1->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall1->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto pitWall2 = std::make_shared<GameObject>("pitWall2");
        sceneGraph.addNode(pitWall2);
        pitWall2->setLocalPosition(Vector3(-115.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall2->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall2->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }


    // Floor3 pad
    {
        auto Floor3 = std::make_shared<GameObject>("Floor3");
        sceneGraph.addNode(Floor3);
        Floor3->setLocalPosition(Vector3(-135.0f + offsetX, -5.0f + offsetY, 0.0f + offsetZ));
        Floor3->setLocalScaling(Vector3(40.0f, 10.0f, 20.0f));
        auto renderComp = Floor3->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Floor3->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Pit wall
    /*{
        auto pitWall1 = std::make_shared<GameObject>("pitWall1");
        sceneGraph.addNode(pitWall1);
        pitWall1->setLocalPosition(Vector3(-144.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall1->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall1->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall1->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }*/

    // Pit wall2
   /* {
        auto pitWall2 = std::make_shared<GameObject>("pitWall2");
        sceneGraph.addNode(pitWall2);
        pitWall2->setLocalPosition(Vector3(-199.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall2->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall2->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }*/

    // Pit floor 2
    {
        auto pitFloor = std::make_shared<GameObject>("pitFloor");
        sceneGraph.addNode(pitFloor);
        pitFloor->setLocalPosition(Vector3(-175.0f + offsetX, -10.0f + offsetY, 0.0f + offsetZ));
        pitFloor->setLocalScaling(Vector3(50.0f, 1.0f, 20.0f));
        auto renderComp = pitFloor->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitFloor->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Pit box2
    {
        auto pitBox = std::make_shared<GameObject>("pitBox");
        sceneGraph.addNode(pitBox);
        pitBox->setLocalPosition(Vector3(-155.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        pitBox->setLocalScaling(Vector3(10.0f, 30.0f, 20.0f));
        auto renderComp = pitBox->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitBox->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Floor4 pad
    {
        auto Floor4 = std::make_shared<GameObject>("Floor4", GameObject::CHECKPOINT);
        sceneGraph.addNode(Floor4);
        Floor4->setLocalPosition(Vector3(-209.0f + offsetX, -5.0f + offsetY, 0.0f + offsetZ));
        Floor4->setLocalScaling(Vector3(20.0f, 10.0f, 20.0f));
        auto renderComp = Floor4->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Floor4->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Pit wall
    /*{
        auto pitWall1 = std::make_shared<GameObject>("pitWall1");
        sceneGraph.addNode(pitWall1);
        pitWall1->setLocalPosition(Vector3(-218.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall1->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall1->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall1->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto pitWall2 = std::make_shared<GameObject>("pitWall2");
        sceneGraph.addNode(pitWall2);
        pitWall2->setLocalPosition(Vector3(-254.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall2->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall2->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }*/

    // Floor5 pad
    {
        auto Floor5 = std::make_shared<GameObject>("Floor5", GameObject::CHECKPOINT);
        sceneGraph.addNode(Floor5);
        Floor5->setLocalPosition(Vector3(-264.0f + offsetX, -5.0f + offsetY, 0.0f + offsetZ));
        Floor5->setLocalScaling(Vector3(20.0f, 10.0f, 20.0f));
        auto renderComp = Floor5->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Floor5->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto wallRunWall = std::make_shared<GameObject>("WallRunWall", GameObject::RUNNABLE_WALL);
        sceneGraph.addNode(wallRunWall);
        wallRunWall->setLocalPosition(Vector3(-345.0f + offsetX, 4.0f + offsetY, -9.5f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(60.0f, 12.0f, 0.1f));
        auto renderComp = wallRunWall->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(BlueConcrete);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }
    {
        auto wallRunWall = std::make_shared<GameObject>("WallRunWall", GameObject::RUNNABLE_WALL);
        sceneGraph.addNode(wallRunWall);
        wallRunWall->setLocalPosition(Vector3(-345.0f + offsetX, 4.0f + offsetY, 9.5f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(60.0f, 12.0f, 0.1f));
        auto renderComp = wallRunWall->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(BlueConcrete);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Pit wall
    /*{
        auto pitWall1 = std::make_shared<GameObject>("pitWall1");
        sceneGraph.addNode(pitWall1);
        pitWall1->setLocalPosition(Vector3(-273.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall1->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall1->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall1->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    {
        auto pitWall2 = std::make_shared<GameObject>("pitWall2");
        sceneGraph.addNode(pitWall2);
        pitWall2->setLocalPosition(Vector3(-375.5f + offsetX, -10.5f + offsetY, 0.0f + offsetZ));
        pitWall2->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall2->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }*/

    // Floor6 pad
    {
        auto Floor6 = std::make_shared<GameObject>("Floor6");
        sceneGraph.addNode(Floor6);
        Floor6->setLocalPosition(Vector3(-390.0f + offsetX, -10.0f + offsetY, 0.0f + offsetZ));
        Floor6->setLocalScaling(Vector3(30.0f, 10.0f, 20.0f));
        auto renderComp = Floor6->addComponent<Render3D>();
        renderComp->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Floor6->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }


}
