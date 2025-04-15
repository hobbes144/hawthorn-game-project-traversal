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
    //createWall("TopWall", Vector3(0.0f, height, 0.0f), Vector3(width, wallThickness, depth));
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
        auto movingWallRun2 = [&](const std::string& name, const Vector3& basePos, const Vector3& scale, const Vector3& moveDir, int platformCount) {
            std::vector<std::shared_ptr<GameObject>> movingWalls;
            float spawnInterval = 5.0f;
            auto spawnTimer = std::make_shared<float>(0.0f);
            auto spawnedCount = std::make_shared<int>(0);

            auto spawner = std::make_shared<GameObject>("Spawner_" + name);
            sceneGraph.addNode(spawner);

            spawner->addComponent<Animate>()->setAnimateFunction(
                [=](std::shared_ptr<GameObject> self, float deltaTime) mutable {
                    *spawnTimer += deltaTime;
                    if (*spawnedCount < platformCount && *spawnTimer >= spawnInterval) {
                        *spawnTimer = 0.0f;
                        std::string wallName = name + "_" + std::to_string(*spawnedCount);
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
                            [moveVec = moveDir, basePos, time = 0.0f](std::shared_ptr<GameObject> self, float dt) mutable {
                            time += dt;
                            if (time >= 25.0f) {
                                self->setLocalPosition(basePos);
                                time = 0.0f;
                            }
                            else {
                                self->setLocalPosition(self->getLocalPosition() + moveVec * dt);
                            }
                            }
                        )->runAnimateFunction(true);
                        movingWalls.push_back(wall);
                        (*spawnedCount)++;
                    }
                }
            )->runAnimateFunction(true);
            };
    

        movingWallRun2("Wall1", Vector3(200.0f, 10.0f, 8.0f), Vector3(40.0f, 20.0f, 1.0f), Vector3(-10.0f, 0.0f, 0.0f), 5);
        movingWallRun2("Wall2", Vector3(220.0f, 10.0f, -8.0f), Vector3(40.0f, 20.0f, 1.0f), Vector3(-10.0f, 0.0f, 0.0f), 5);

        movingWallRun2("Wall1", Vector3(250.0f, 30.0f, 8.0f), Vector3(40.0f, 20.0f, 1.0f), Vector3(-10.0f, 0.0f, 0.0f), 5);
        movingWallRun2("Wall2", Vector3(270.0f, 30.0f, -8.0f), Vector3(40.0f, 20.0f, 1.0f), Vector3(-10.0f, 0.0f, 0.0f), 5);

        movingWallRun2("Wall1", Vector3(300.0f, 50.0f, 8.0f), Vector3(40.0f, 20.0f, 1.0f), Vector3(-10.0f, 0.0f, 0.0f), 5);
        movingWallRun2("Wall2", Vector3(320.0f, 50.0f, -8.0f), Vector3(40.0f, 20.0f, 1.0f), Vector3(-10.0f, 0.0f, 0.0f), 5);
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