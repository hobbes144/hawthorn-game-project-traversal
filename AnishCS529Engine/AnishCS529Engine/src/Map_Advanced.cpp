#include "precompiled.h"
#include "MapLoader.h"
#include "Door.h"
#include "DeathPlane.h"
#include "InGameKey.h"

void MapLoader::advanced(float offsetX, float offsetY, float offsetZ,
                            SceneGraph& sceneGraph,
                            std::shared_ptr<Camera> camera) {


    // Floor pad
    {
        auto mainFloor = std::make_shared<GameObject>("mainFloor");
        sceneGraph.addNode(mainFloor);
        mainFloor->setLocalPosition(Vector3(0.0f + offsetX, -25.0f + offsetY, 0.0f + offsetZ));
        mainFloor->setLocalScaling(Vector3(300.0f, 50.0f, 300.0f));
        auto renderComp = mainFloor->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = mainFloor->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }
    // ------------
    //   Wall run
    // ------------
    // 
    // Checkpoint pad
    {
        auto checkPoint1 = std::make_shared<GameObject>("checkPoint1", GameObject::CHECKPOINT);
        sceneGraph.addNode(checkPoint1);
        checkPoint1->setLocalPosition(Vector3(-130.5f + offsetX, 6.0f + offsetY, -130.0f + offsetZ));
        checkPoint1->setLocalScaling(Vector3(12.0f, 1.0f, 12.0f));
        auto renderComp = checkPoint1->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = checkPoint1->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Wall for wall running
    {
        auto wallRunWall = std::make_shared<GameObject>("WallRunWall", GameObject::RUNNABLE_WALL);
        sceneGraph.addNode(wallRunWall);
        wallRunWall->setLocalPosition(Vector3(-135.0f + offsetX, 20.0f + offsetY, -110.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(1.0f, 30.0f, 30.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Checkpoint2 
    {
        auto checkPoint2 = std::make_shared<GameObject>("checkPoint2", GameObject::CHECKPOINT);
        sceneGraph.addNode(checkPoint2);
        checkPoint2->setLocalPosition(Vector3(-130.5f + offsetX, 10.0f + offsetY, -95.0f + offsetZ));
        checkPoint2->setLocalScaling(Vector3(8.0f, 1.0f, 12.0f));
        auto renderComp = checkPoint2->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = checkPoint2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Walls


    {
        auto wallRunWall = std::make_shared<GameObject>("WallRunWall", GameObject::RUNNABLE_WALL);
        sceneGraph.addNode(wallRunWall);
        wallRunWall->setLocalPosition(Vector3(-135.0f + offsetX, 15.0f + offsetY, -70.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(1.0f, 50.0f, 30.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        wallRunWall->setLocalPosition(Vector3(-125.0f + offsetX, 15.0f + offsetY, -80.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(1.0f, 50.0f, 40.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        wallRunWall->setLocalPosition(Vector3(-110.0f + offsetX, 15.0f + offsetY, -70.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(1.0f, 50.0f, 40.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        wallRunWall->setLocalPosition(Vector3(-125.0f + offsetX, 15.0f + offsetY, -50.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(30.0f, 50.0f, 1.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Checkpoint3
    {
        auto checkPoint3 = std::make_shared<GameObject>("checkPoint3", GameObject::CHECKPOINT);
        sceneGraph.addNode(checkPoint3);
        checkPoint3->setLocalPosition(Vector3(-115.0f + offsetX, 16.0f + offsetY, -55.0f + offsetZ));
        checkPoint3->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
        auto renderComp = checkPoint3->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = checkPoint3->addComponent<RigidBody>();
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
        wallRunWall->setLocalPosition(Vector3(-110.0f + offsetX, 22.0f + offsetY, -100.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(30.0f, 10.0f, 1.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Checkpoint4
    {
        auto checkPoint4 = std::make_shared<GameObject>("checkPoint4", GameObject::CHECKPOINT);
        sceneGraph.addNode(checkPoint4);
        checkPoint4->setLocalPosition(Vector3(-100.5f + offsetX, 22.0f + offsetY, -40.0f + offsetZ));
        checkPoint4->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
        auto renderComp = checkPoint4->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = checkPoint4->addComponent<RigidBody>();
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
        wallRunWall->setLocalPosition(Vector3(-95.0f + offsetX, 22.0f + offsetY, -90.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        wallRunWall->setLocalPosition(Vector3(-140.0f + offsetX, 30.0f + offsetY, -30.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(1.0f, 10.0f, 30.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        wallRunWall->setLocalPosition(Vector3(-130.0f + offsetX, 38.0f + offsetY, 0.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(1.0f, 10.0f, 30.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        wallRunWall->setLocalPosition(Vector3(-140.0f + offsetX, 42.0f + offsetY, 30.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(1.0f, 10.0f, 30.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    //{
    //    auto wallRunWall = std::make_shared<GameObject>("WallRunWall", GameObject::RUNNABLE_WALL);
    //    sceneGraph.addNode(wallRunWall);
    //    wallRunWall->setLocalPosition(Vector3(-105.0f + offsetX, 20.0f + offsetY, 70.0f + offsetZ));
    //    wallRunWall->setLocalScaling(Vector3(1.0f, 10.0f, 30.0f));
    //    auto renderComp = wallRunWall->addComponent<Render2D>();
    //    renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
    //    auto shape = std::make_shared<OBB>();
    //    auto rigidBody = wallRunWall->addComponent<RigidBody>();
    //    rigidBody->setMass(0.0f)
    //        ->setDrag(1.0f)
    //        ->setShape(shape)
    //        ->setStatic(true)
    //        ->registerToPhysicsManager(PhysicsManager::Instance());
    //    rigidBody->initialize();
    //}

    {
        auto wallRunWall = std::make_shared<GameObject>("WallRunWall", GameObject::RUNNABLE_WALL);
        sceneGraph.addNode(wallRunWall);
        wallRunWall->setLocalPosition(Vector3(-125.0f + offsetX, 42.0f + offsetY, 45.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(30.0f, 10.0f, 1.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Jump Pad
    {
        auto JumpPad = std::make_shared<GameObject>("JumpPad");
        sceneGraph.addNode(JumpPad);
        JumpPad->setLocalPosition(Vector3(-103.0f + offsetX, 42 + offsetY, 38.0f + offsetZ));
        JumpPad->setLocalScaling(Vector3(12.0f, 1.0f, 12.0f));
        auto renderComp = JumpPad->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = JumpPad->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Checkpoint5
    {
        auto checkPoint5 = std::make_shared<GameObject>("checkPoint5", GameObject::CHECKPOINT);
        sceneGraph.addNode(checkPoint5);
        checkPoint5->setLocalPosition(Vector3(-115.5f + offsetX, 42.0f + offsetY, 55.0f + offsetZ));
        checkPoint5->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
        auto renderComp = checkPoint5->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = checkPoint5->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Moving platform going up/down
    {
        auto MovingPlatform = std::make_shared<GameObject>("MovingPlatform");
        sceneGraph.addNode(MovingPlatform);
        MovingPlatform->setLocalPosition(Vector3(-130.0f + offsetX, 47 + offsetY, 54.0f + offsetZ));
        MovingPlatform->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
        auto renderComp = MovingPlatform->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();

        auto rigidBody = MovingPlatform->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();

        auto platformAnimate = MovingPlatform->addComponent<Animate>();
        platformAnimate->setAnimateFunction(
                [currentTime = 0.0f, initialPos = MovingPlatform->getLocalPosition().y, phase = 1.0f](std::shared_ptr<GameObject> self, float deltaTime) mutable {


                    deltaTime *= timeScale;

                    /* Affine Transformation Variables */
                    float affineSpeed = 5.0f;
                    float affinePosVarianceZ = 5.0f;

                    currentTime += deltaTime;

                    if ((phase == -1.0f) && (initialPos - affinePosVarianceZ) > self->getWorldPosition().y)
                        phase = 1.0f;
                    else if ((phase == 1.0f) && (initialPos + affinePosVarianceZ) < self->getWorldPosition().y)
                        phase = -1.0f;

                    Vector3 velocity = Vector3(0.0f, affineSpeed * phase, 0.0f);

                    Vector3 newPos = self->getWorldPosition() + (velocity * deltaTime);
                    self->setWorldPosition(newPos);
                }
        );

        platformAnimate->runAnimateFunction(true);
    }

    // Pillar 1
    {
        auto Pillar = std::make_shared<GameObject>("Pillar");
        sceneGraph.addNode(Pillar);
        Pillar->setLocalPosition(Vector3(-130.0f + offsetX, 26.0f + offsetY, 70.0f + offsetZ));
        Pillar->setLocalScaling(Vector3(12.0f, 52.0f, 12.0f));
        auto renderComp = Pillar->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Pillar->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Pillar 2
    {
        auto JumpPad = std::make_shared<GameObject>("JumpPad");
        sceneGraph.addNode(JumpPad);
        JumpPad->setLocalPosition(Vector3(-130.0f + offsetX, 28.5f + offsetY, 90.0f + offsetZ));
        JumpPad->setLocalScaling(Vector3(12.0f, 57.0f, 12.0f));
        auto renderComp = JumpPad->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = JumpPad->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Pillar 3
    {
        auto JumpPad2 = std::make_shared<GameObject>("JumpPad2");
        sceneGraph.addNode(JumpPad2);
        JumpPad2->setLocalPosition(Vector3(-135.0f + offsetX, 31 + offsetY, 110.0f + offsetZ));
        JumpPad2->setLocalScaling(Vector3(12.0f, 62.0f, 12.0f));
        auto renderComp = JumpPad2->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = JumpPad2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }


    //{
    //    std::random_device rd;
    //    std::mt19937 gen(rd());
    //    std::uniform_real_distribution<float> zDist(-30.0f, 30.0f);
    //    //std::uniform_real_distribution<float> tiltDist(-10.0f, 10.0f);
    //
    //    for (float x = -100.0f; x <= 130.0f; x += 30.0f) {
    //        auto JumpPad = std::make_shared<GameObject>("JumpPad");
    //        sceneGraph.addNode(JumpPad);
    //
    //        float randomZOffset = zDist(gen);
    //        //float tiltX = tiltDist(gen);
    //        //float tiltZ = tiltDist(gen);
    //        JumpPad->setLocalPosition(Vector3(x + offsetX, 65 + offsetY, 130.0f + randomZOffset + offsetZ));
    //        //JumpPad->setLocalRotation(Vector3(tiltX, 0.0f, tiltZ));
    //        JumpPad->setLocalScaling(Vector3(12.0f, 1.0f, 12.0f));
    //
    //        auto renderComp = JumpPad->addComponent<Render2D>();
    //        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
    //
    //        auto shape = std::make_shared<OBB>();
    //        auto rigidBody = JumpPad->addComponent<RigidBody>();
    //        rigidBody->setMass(0.0f)
    //            ->setDrag(1.0f)
    //            ->setShape(shape)
    //            ->setStatic(true)
    //            ->registerToPhysicsManager(PhysicsManager::Instance());
    //        rigidBody->initialize();
    //    }
    //}
    // 

    // ----------------
    // Platforms Going in Circle
    // ----------------
    {
        auto createCircularPlatform = [&](const std::string& name, const Vector3& center, const Vector3& scale, float dirFactor, float initialAngle = 0.0f) {
            auto platform = std::make_shared<GameObject>(name);
            sceneGraph.addNode(platform);
            platform->setLocalPosition(center);
            platform->setLocalScaling(scale);
            platform->setLocalRotation(Vector3(0.0f, 0.0f, 0.0f));
            platform->addComponent<Render2D>()->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
            platform->addComponent<RigidBody>()
                ->setMass(0.0f)
                ->setDrag(1.0f)
                ->setShape(std::make_shared<OBB>())
                ->setStatic(true)
                ->registerToPhysicsManager(PhysicsManager::Instance())
                ->initialize();

            // Parameters for platform creation
            float radius = 20.0f;
            float angularSpeed = 0.5f;

            platform->addComponent<Animate>()->setAnimateFunction(
                [angle = initialAngle, center, radius, angularSpeed, dirFactor](std::shared_ptr<GameObject> self, float deltaTime) mutable {
                    angle += deltaTime * angularSpeed * dirFactor;
                    float xOffset = radius * std::cos(angle);
                    float zOffset = radius * std::sin(angle);
                    self->setLocalPosition(center + Vector3(xOffset, 0.0f, zOffset));
                }
            )->runAnimateFunction(true);
            };

        // First set
        float startX = -90.0f;
        float endX = 90.0f;
        float step = 90.0f;
        Vector3 scale(20.0f, 3.0f, 20.0f);
        int count = 0;
        for (float x = startX; x <= endX; x += step) {
            Vector3 center(x + offsetX, 65.0f + offsetY, 115.0f + offsetZ);

            // Left side
            for (int i = 0; i < 4; i++) {
                float initialAngle = i * (3.14159265f / 2.0f); // 0, π/2, π, 3π/2
                createCircularPlatform("Platform" + std::to_string(count) + "Left" + std::to_string(i), center, scale, 1.0f, initialAngle);
            }
            // Right side
            for (int i = 0; i < 4; i++) {
                float initialAngle = i * (3.14159265f / 2.0f) + 3.14159265f; // π, 3π/2, 2π, 5π/2
                createCircularPlatform("Platform" + std::to_string(count) + "Right" + std::to_string(i), center, scale, 1.0f, initialAngle);
            }
            count++;
        }

        // Second set
        count = 0;
        for (float x = startX; x <= endX - 10; x += step) {
            Vector3 center(x + offsetX + 45.0f, 65.0f + offsetY, (115.0f + offsetZ) + 50.0f);

            // Left side
            for (int i = 0; i < 4; i++) {
                float initialAngle = i * (3.14159265f / 2.0f);
                createCircularPlatform("PlatformAlt" + std::to_string(count) + "Left" + std::to_string(i), center, scale, -1.0f, initialAngle);
            }
            // Right side
            for (int i = 0; i < 4; i++) {
                float initialAngle = i * (3.14159265f / 2.0f) + 3.14159265f;
                createCircularPlatform("PlatformAlt" + std::to_string(count) + "Right" + std::to_string(i), center, scale, -1.0f, initialAngle);
            }
            count++;
        }
    }






    // Checkpoint6
    {
        auto checkPoint6 = std::make_shared<GameObject>("checkPoint6", GameObject::CHECKPOINT);
        sceneGraph.addNode(checkPoint6);
        checkPoint6->setLocalPosition(Vector3(130.5f + offsetX, 68.0f + offsetY, 130.0f + offsetZ));
        checkPoint6->setLocalScaling(Vector3(12.0f, 1.0f, 12.0f));
        auto renderComp = checkPoint6->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = checkPoint6->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Moving platform going up
    {
        std::vector<std::shared_ptr<GameObject>> movingBlocks;
        float spawnInterval = 5.0f;
        int maxBlocks = 4;
        Vector3 startPos(130.0f, 65.0f, 123.0f);
        Vector3 velocity(0.0f, 1.0f, -5.0f);

        auto spawnTimer = std::make_shared<float>(0.0f);
        auto spawnedCount = std::make_shared<int>(0);

        auto spawner = std::make_shared<GameObject>("BlockSpawner");
        sceneGraph.addNode(spawner);

        spawner->addComponent<Animate>()->setAnimateFunction(
            [=](std::shared_ptr<GameObject> self, float deltaTime) mutable {
                *spawnTimer += deltaTime;

                if (*spawnedCount < maxBlocks && *spawnTimer >= spawnInterval) {
                    *spawnTimer = 0.0f;

                    auto block = std::make_shared<GameObject>("MovingBlock_" + std::to_string(*spawnedCount));
                    sceneGraph.addNode(block);
                    block->setLocalPosition(startPos);
                    block->setLocalScaling(Vector3(12.0f, 1.0f, 12.0f));
                    block->setLocalRotation(Vector3(0.0f, 0.0f, 0.0f));

                    block->addComponent<Render2D>()->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);

                    block->addComponent<RigidBody>()
                        ->setMass(0.0f)
                        ->setDrag(1.0f)
                        ->setShape(std::make_shared<OBB>())
                        ->setStatic(true)
                        ->registerToPhysicsManager(PhysicsManager::Instance())
                        ->initialize();

                    block->addComponent<Animate>()->setAnimateFunction(
                        [velocity, startPos, time = 0.0f](std::shared_ptr<GameObject> self, float dt) mutable {
    time += dt;
    if (time >= 20.0f) {
    self->setLocalPosition(startPos);
    time = 0.0f;
    }
    else {
    self->setLocalPosition(self->getLocalPosition() + velocity * dt);
    }
                        }
                    )->runAnimateFunction(true);

                    movingBlocks.push_back(block);
                    (*spawnedCount)++;
                }
            }
        )->runAnimateFunction(true);
    }

    // Moving platform going down
    {
        std::vector<std::shared_ptr<GameObject>> movingBlocks;
        float spawnInterval = 5.0f;
        int maxBlocks = 4;
        Vector3 startPos(143.0f, 85.0f, 23.0f);
        Vector3 velocity(0.0f, -1.0f, 5.0f);

        auto spawnTimer = std::make_shared<float>(0.0f);
        auto spawnedCount = std::make_shared<int>(0);

        auto spawner = std::make_shared<GameObject>("BlockSpawner");
        sceneGraph.addNode(spawner);

        spawner->addComponent<Animate>()->setAnimateFunction(
            [=](std::shared_ptr<GameObject> self, float deltaTime) mutable {
                *spawnTimer += deltaTime;

                if (*spawnedCount < maxBlocks && *spawnTimer >= spawnInterval) {
                    *spawnTimer = 0.0f;

                    auto block = std::make_shared<GameObject>("MovingBlock_" + std::to_string(*spawnedCount));
                    sceneGraph.addNode(block);
                    block->setLocalPosition(startPos);
                    block->setLocalScaling(Vector3(12.0f, 1.0f, 12.0f));
                    block->setLocalRotation(Vector3(0.0f, 0.0f, 0.0f));

                    block->addComponent<Render2D>()->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);

                    block->addComponent<RigidBody>()
                        ->setMass(0.0f)
                        ->setDrag(1.0f)
                        ->setShape(std::make_shared<OBB>())
                        ->setStatic(true)
                        ->registerToPhysicsManager(PhysicsManager::Instance())
                        ->initialize();

                    // Animate block movement and reset after 20 seconds
                    block->addComponent<Animate>()->setAnimateFunction(
                        [velocity, startPos, time = 0.0f](std::shared_ptr<GameObject> self, float dt) mutable {
    time += dt;
    if (time >= 20.0f) {
    self->setLocalPosition(startPos);
    time = 0.0f;
    }
    else {
    self->setLocalPosition(self->getLocalPosition() + velocity * dt);
    }
                        }
                    )->runAnimateFunction(true);

                    movingBlocks.push_back(block);
                    (*spawnedCount)++;
                }
            }
        )->runAnimateFunction(true);
    }

    {
        auto wallRunWall = std::make_shared<GameObject>("WallRunWall", GameObject::RUNNABLE_WALL);
        sceneGraph.addNode(wallRunWall);
        wallRunWall->setLocalPosition(Vector3(153.0f + offsetX, 90.0f + offsetY, 15.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(1.0f, 10.0f, 30.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        wallRunWall->setLocalPosition(Vector3(125.0f + offsetX, 68.0f + offsetY, -40.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(1.0f, 10.0f, 50.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        wallRunWall->setLocalPosition(Vector3(100.0f + offsetX, 68.0f + offsetY, -65.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(30.0f, 10.0f, 1.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Checkpoint7
    {
        auto checkPoint7 = std::make_shared<GameObject>("checkPoint7", GameObject::CHECKPOINT);
        sceneGraph.addNode(checkPoint7);
        checkPoint7->setLocalPosition(Vector3(78.0f + offsetX, 63.0f + offsetY, -72.0f + offsetZ));
        checkPoint7->setLocalScaling(Vector3(12.0f, 1.0f, 12.0f));
        auto renderComp = checkPoint7->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = checkPoint7->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

}
