#include "precompiled.h"
#include "MapLoader.h"
#include "Door.h"
#include "DeathPlane.h"
#include "InGameKey.h"

void MapLoader::menu(float offsetX, float offsetY, float offsetZ,
                            SceneGraph& sceneGraph,
                            std::shared_ptr<Camera> camera) {


    Vector3 center(offsetX, offsetY, offsetZ);

    auto createWall = [&](const std::string& name, const Vector3& localPos, const Vector3& localScale) {
        auto wall = std::make_shared<GameObject>(name, GameObject::RUNNABLE_WALL);
        sceneGraph.addNode(wall);
        wall->setLocalPosition(center + localPos);
        wall->setLocalScaling(localScale);

        auto renderComp = wall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(BlueConcrete);

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
    float size = 40.0f;
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

    writeLetter(sceneGraph, "media/Map/words/start.fbx", Vector3(-19.0f + offsetX, 6.5f + offsetY, -3.5f + offsetZ),
            Vector3(0.03f, 0.03f, 0.03f), Vector3(0.0f, -1.57f, 0.0f), camera, keyMaterial);

    writeLetter(sceneGraph, "media/Map/words/W.fbx", Vector3(-18.0f + offsetX, 3.2f + offsetY, -3.5f + offsetZ),
                Vector3(0.01f, 0.01f, 0.01f), Vector3(0.0f, -1.57f, 0.0f), camera, BrownConcrete);
    writeLetter(sceneGraph, "media/Map/words/A.fbx", Vector3(-18.0f + offsetX, 2.0f + offsetY, -2.3f + offsetZ),
            Vector3(0.01f, 0.01f, 0.01f), Vector3(0.0f, -1.57f, 0.0f), camera, BrownConcrete);
    writeLetter(sceneGraph, "media/Map/words/S.fbx", Vector3(-18.0f + offsetX, 2.0f + offsetY, -3.5f + offsetZ),
                Vector3(0.01f, 0.01f, 0.01f), Vector3(0.0f, -1.57f, 0.0f), camera, BrownConcrete);
    writeLetter(sceneGraph, "media/Map/words/D.fbx", Vector3(-18.0f + offsetX, 2.0f + offsetY, -4.7f + offsetZ),
                Vector3(0.01f, 0.01f, 0.01f), Vector3(0.0f, -1.57f, 0.0f), camera, BrownConcrete);
    writeLetter(sceneGraph, "media/Map/words/tomove.fbx", Vector3(-18.0f + offsetX, 2.5f + offsetY, -7.5f + offsetZ),
            Vector3(0.01f, 0.01f, 0.01f), Vector3(0.0f, -1.57f, 0.0f), camera, BrownConcrete);



    // Door to tutorial level
    {
        auto testDoor = std::make_shared<GameObject>("Door", GameObject::WALL);
        sceneGraph.addNode(testDoor);
        testDoor->setLocalPosition(Vector3(-19.0f + offsetX, 2.5f + offsetY, 0.0f + offsetZ));
        testDoor->setLocalScaling(Vector3(0.3f, 5.0f, 3.0f));
        auto renderComp = testDoor->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(BrownConcrete);
        auto shape = std::make_shared<OBB>();
        auto doorComp = testDoor->addComponent<Door>();
        doorComp->setID(0);
        doorComp->setType(Door::DoorType::NEXTLEVEL);
        doorComp->setRequiresKey(false);
        doorComp->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        doorComp->initialize();
    }
}