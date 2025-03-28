#include "precompiled.h"
#include "MapLoader.h"

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
    case 0:
        zero(offsetX, offsetY, offsetZ, sceneGraph, camera, floorMesh, floorMaterial);
        break;
    case 1:
        one(offsetX, offsetY, offsetZ, sceneGraph, camera, floorMesh, floorMaterial);
        break;
    case 2:
        loadJump(offsetX, offsetY, offsetZ, sceneGraph, camera, floorMesh, floorMaterial);
        break;
    case 3:
        three(offsetX, offsetY, offsetZ, sceneGraph, camera, floorMesh, floorMaterial);
        break;
    case 4:
        four(offsetX, offsetY, offsetZ, sceneGraph, camera, floorMesh, floorMaterial);
        break;
    case 5:
        loadWallrun(offsetX, offsetY, offsetZ, sceneGraph, camera, floorMesh, floorMaterial);
        break;
    default:
        std::cerr << "[MapLoader] Map ID " << mapId << " is not recognized.\n";
        break;
    }
}


//std::shared_ptr<GameObject> CreateBlock(
//    const std::string& name,
//    const Vector3& pos = Vector3(0.0f, 0.0f, 0.0f),
//    const Vector3& scaling = Vector3(1.0f, 1.0f, 1.0f),
//    const Vector3& rotation = Vector3(0.0f, 0.0f, 0.0f),
//    std::shared_ptr<Mesh> mesh = nullptr,
//    std::shared_ptr<Material> material = nullptr
//)
//{
//    auto block = std::make_shared<GameObject>(name);
//    block->setLocalPosition(pos);
//    block->setLocalScaling(scaling);
//    block->setLocalRotation(rotation);
//    auto renderComp = block->addComponent<Render2D>();
//    renderComp->setMesh(mesh)->setMaterial(material);
//    auto shape = std::make_shared<OBB>();
//    auto rigidBody = block->addComponent<RigidBody>();
//    rigidBody->setMass(0.0f)
//        ->setDrag(1.0f)
//        ->setShape(shape)
//        ->setStatic(true)
//        ->registerToPhysicsManager(PhysicsManager::Instance());
//    rigidBody->initialize();
//    return block;
//}



void MapLoader::zero(float offsetX, float offsetY, float offsetZ, SceneGraph& sceneGraph, std::shared_ptr<Camera> camera, std::shared_ptr<Mesh> floorMesh, std::shared_ptr<Material> floorMaterial){
{
    auto mainFloor = std::make_shared<GameObject>("mainFloor");
    sceneGraph.addNode(mainFloor);
    mainFloor->setLocalPosition(Vector3(0.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
    mainFloor->setLocalScaling(Vector3(300.0f, 1.0f, 300.0f));
    auto renderComp = mainFloor->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>();
    auto rigidBody = mainFloor->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)
        ->setDrag(1.0f)
        ->setShape(shape)
        ->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}

}

void MapLoader::one(float offsetX, float offsetY, float offsetZ,
                            SceneGraph& sceneGraph,
                            std::shared_ptr<Camera> camera,
                            std::shared_ptr<Mesh> floorMesh,
                            std::shared_ptr<Material> floorMaterial) {


// Floor pad
{
    auto mainFloor = std::make_shared<GameObject>("mainFloor");
    sceneGraph.addNode(mainFloor);
    mainFloor->setLocalPosition(Vector3(0.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
    mainFloor->setLocalScaling(Vector3(300.0f, 1.0f, 300.0f));
    auto renderComp = mainFloor->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
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
    auto checkPoint1 = std::make_shared<GameObject>("checkPoint1");
    sceneGraph.addNode(checkPoint1);
    checkPoint1->setLocalPosition(Vector3(-130.5f + offsetX, 6.0f + offsetY, -130.0f + offsetZ));
    checkPoint1->setLocalScaling(Vector3(12.0f, 1.0f, 12.0f));
    auto renderComp = checkPoint1->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
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
    auto wallRunWall = std::make_shared<GameObject>("WallRunWall");
    sceneGraph.addNode(wallRunWall);
    wallRunWall->setLocalPosition(Vector3(-135.0f + offsetX, 20.0f + offsetY, -110.0f + offsetZ));
    wallRunWall->setLocalScaling(Vector3(1.0f, 30.0f, 30.0f));
    auto renderComp = wallRunWall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
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
    auto checkPoint2 = std::make_shared<GameObject>("checkPoint2");
    sceneGraph.addNode(checkPoint2);
    checkPoint2->setLocalPosition(Vector3(-130.5f + offsetX, 10.0f + offsetY, -95.0f + offsetZ));
    checkPoint2->setLocalScaling(Vector3(8.0f, 1.0f, 12.0f));
    auto renderComp = checkPoint2->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
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
    auto wallRunWall = std::make_shared<GameObject>("WallRunWall");
    sceneGraph.addNode(wallRunWall);
    wallRunWall->setLocalPosition(Vector3(-125.0f + offsetX, 15.0f + offsetY, -70.0f + offsetZ));
    wallRunWall->setLocalScaling(Vector3(1.0f, 50.0f, 30.0f));
    auto renderComp = wallRunWall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
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
    auto wallRunWall = std::make_shared<GameObject>("WallRunWall");
    sceneGraph.addNode(wallRunWall);
    wallRunWall->setLocalPosition(Vector3(-135.0f + offsetX, 15.0f + offsetY, -70.0f + offsetZ));
    wallRunWall->setLocalScaling(Vector3(1.0f, 50.0f, 30.0f));
    auto renderComp = wallRunWall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
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
    auto wallRunWall = std::make_shared<GameObject>("WallRunWall");
    sceneGraph.addNode(wallRunWall);
    wallRunWall->setLocalPosition(Vector3(-110.0f + offsetX, 15.0f + offsetY, -70.0f + offsetZ));
    wallRunWall->setLocalScaling(Vector3(1.0f, 50.0f, 40.0f));
    auto renderComp = wallRunWall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
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
    auto wallRunWall = std::make_shared<GameObject>("WallRunWall");
    sceneGraph.addNode(wallRunWall);
    wallRunWall->setLocalPosition(Vector3(-125.0f + offsetX, 15.0f + offsetY, -50.0f + offsetZ));
    wallRunWall->setLocalScaling(Vector3(30.0f, 50.0f, 1.0f));
    auto renderComp = wallRunWall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
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
    auto checkPoint3 = std::make_shared<GameObject>("checkPoint3");
    sceneGraph.addNode(checkPoint3);
    checkPoint3->setLocalPosition(Vector3(-130.5f + offsetX, 17.0f + offsetY, -95.0f + offsetZ));
    checkPoint3->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto renderComp = checkPoint3->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
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
    auto wallRunWall = std::make_shared<GameObject>("WallRunWall");
    sceneGraph.addNode(wallRunWall);
    wallRunWall->setLocalPosition(Vector3(-100.0f + offsetX, 22.0f + offsetY, -100.0f + offsetZ));
    wallRunWall->setLocalScaling(Vector3(50.0f, 10.0f, 1.0f));
    auto renderComp = wallRunWall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>();
    auto rigidBody = wallRunWall->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)
        ->setDrag(1.0f)
        ->setShape(shape)
        ->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}


}
// Wallrun map 
void MapLoader::loadWallrun(float offsetX, float offsetY, float offsetZ,
                            SceneGraph& sceneGraph,
                            std::shared_ptr<Camera> camera,
                            std::shared_ptr<Mesh> floorMesh,
                            std::shared_ptr<Material> floorMaterial) {
    // Start pad
    {
        auto mainFloorLeft = std::make_shared<GameObject>("MainFloorLeft");
        sceneGraph.addNode(mainFloorLeft);
        mainFloorLeft->setLocalPosition(Vector3(-1.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        mainFloorLeft->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
        auto renderComp = mainFloorLeft->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = mainFloorLeft->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();


    }

    // Rest pad
    {
        auto RestPad = std::make_shared<GameObject>("RestPad");
        sceneGraph.addNode(RestPad);
        RestPad->setLocalPosition(Vector3(40.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        RestPad->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
        auto renderComp = RestPad->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = RestPad->addComponent<RigidBody>();
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
        wallRunWall->setLocalScaling(Vector3(30.0f, 12.0f, 1.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Wall2 for wall running
    {
        auto wallRunWall2 = std::make_shared<GameObject>("WallRunWall2");
        sceneGraph.addNode(wallRunWall2);
        wallRunWall2->setLocalPosition(Vector3(60.0f + offsetX, 2.5f + offsetY, -4.0f + offsetZ));
        wallRunWall2->setLocalScaling(Vector3(30.0f, 8.0f, 1.0f));
        auto renderComp = wallRunWall2->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Wall3 for wall running
    {
        auto wallRunWall3 = std::make_shared<GameObject>("WallRunWall3");
        sceneGraph.addNode(wallRunWall3);
        wallRunWall3->setLocalPosition(Vector3(80.0f + offsetX, 5.0f + offsetY, 4.0f + offsetZ));
        wallRunWall3->setLocalScaling(Vector3(40.0f, 12.0f, 1.0f));
        auto renderComp = wallRunWall3->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall3->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Wall4 for wall running
    {
        auto wallRunWall4 = std::make_shared<GameObject>("WallRunWall4");
        sceneGraph.addNode(wallRunWall4);
        wallRunWall4->setLocalPosition(Vector3(120.0f + offsetX, offsetY, -4.0f + offsetZ));
        wallRunWall4->setLocalScaling(Vector3(30.0f, 8.0f, 1.0f));
        auto renderComp = wallRunWall4->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall4->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Rest pad2
    {
        auto RestPad2 = std::make_shared<GameObject>("RestPad2");
        sceneGraph.addNode(RestPad2);
        RestPad2->setLocalPosition(Vector3(140.0f + offsetX, -3.0f + offsetY, 0.0f + offsetZ));
        RestPad2->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
        auto renderComp = RestPad2->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = RestPad2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Wall5 for wall running
    {
        auto wallRunWall5 = std::make_shared<GameObject>("WallRunWall5");
        sceneGraph.addNode(wallRunWall5);
        wallRunWall5->setLocalPosition(Vector3(190.0f + offsetX,-20.0f + offsetY, 10.0f + offsetZ));
        wallRunWall5->setLocalScaling(Vector3(80.0f, 20.0f, 1.0f));
        auto renderComp = wallRunWall5->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall5->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Wall6 for wall running
    {
        auto wallRunWall6 = std::make_shared<GameObject>("WallRunWall6");
        sceneGraph.addNode(wallRunWall6);
        wallRunWall6->setLocalPosition(Vector3(280.0f + offsetX, -50 + offsetY, -15.0f + offsetZ));
        wallRunWall6->setLocalScaling(Vector3(50.0f, 8.0f, 1.0f));
        auto renderComp = wallRunWall6->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall6->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Rest pad3
    {
        auto RestPad3 = std::make_shared<GameObject>("RestPad3");
        sceneGraph.addNode(RestPad3);
        RestPad3->setLocalPosition(Vector3(310.0f + offsetX, -55 + offsetY, -10.0f + offsetZ));
        RestPad3->setLocalScaling(Vector3(12.0f, 1.0f, 12.0f));
        auto renderComp = RestPad3->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = RestPad3->addComponent<RigidBody>();
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
    mainFloor->setLocalScaling(Vector3(10.0f, 1.0f, 10.0f));
    auto renderComp = mainFloor->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>();
    auto rigidBody = mainFloor->addComponent<RigidBody>();
    rigidBody->setMass(0.0f)
        ->setDrag(1.0f)
        ->setShape(shape)
        ->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rigidBody->initialize();
}

float platformSizes[] = { 4.0f, 3.5f, 3.0f, 3.2f, 3.6f, 3.1f, 3.4f, 3.7f, 4.2f };
float yVariation[] = { 0.3f, -5.2f, -3.5f, -1.4f, 0.2f, 3.0f, 5.4f, 8.2f, 11.0f };
float xSpacing = 6.0f;
float xOffset[] = { 2.0f, 2.0f, -3.0f, 3.0f, -4.0f, 4.0f, -5.0f, 5.0f, 0.0f };

for (int i = 0; i < 9; ++i) {
    auto platform = std::make_shared<GameObject>("Platform" + std::to_string(i + 1));
    sceneGraph.addNode(platform);
    float adjustedX = (i == 0) ? (xSpacing * 1.5f) : ((i + 1) * xSpacing + 5.0f);
    platform->setLocalPosition(Vector3(adjustedX + offsetX, yVariation[i] + offsetY, xOffset[i] + offsetZ));
    platform->setLocalScaling(Vector3(platformSizes[i], 0.5f, platformSizes[i]));
    auto renderComp = platform->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>();
    if (i == 0) {
      auto rigidBody = platform->addComponent<TimeControlledRB>();
      rigidBody->setTimeScale(timeScale);
      rigidBody->setMass(0.0f)
          ->setDrag(1.0f)
          ->setShape(shape)
          ->setStatic(true)
          ->registerToPhysicsManager(PhysicsManager::Instance());
      rigidBody->initialize();

      auto platformAnimate = platform->addComponent<Animate>();
      platformAnimate->setAnimateFunction(
            [currentTime = 0.0f, initialPos = platform->getLocalPosition().z, phase = 1.0f](std::shared_ptr<GameObject> self, float deltaTime) mutable {
              std::shared_ptr<TimeControlledRB> rb = self->findComponent<TimeControlledRB>();
              float timeScale = rb->getTimeScale();
      
              deltaTime *= timeScale;
      
              /* Affine Transformation Variables */
              float affineSpeed = 10.0f;
              float affinePosVarianceZ = 5.0f;
      
              currentTime += deltaTime;

              if ((phase == -1.0f) && (initialPos - affinePosVarianceZ) > self->getWorldPosition().z)
                phase = 1.0f;
              else if ((phase == 1.0f) && (initialPos + affinePosVarianceZ) < self->getWorldPosition().z)
                phase = -1.0f;

              Vector3 velocity = Vector3(0.0f, 0.0f, affineSpeed * phase);
              
              rb->setVelocity(velocity);
              Vector3 newPos = self->getWorldPosition() + (velocity * deltaTime);
              self->setWorldPosition(newPos);
            }
          );
      
      platformAnimate->runAnimateFunction(true);
    }
    else {
      auto rigidBody = platform->addComponent<RigidBody>();
      rigidBody->setMass(0.0f)
        ->setDrag(1.0f)
        ->setShape(shape)
        ->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
      rigidBody->initialize();
    }
}

// Exit platform
{
    auto upperFloor = std::make_shared<GameObject>("UpperFloor");
    sceneGraph.addNode(upperFloor);
    upperFloor->setLocalPosition(Vector3(90.0f + offsetX, -20.2f + offsetY, 8.0f + offsetZ));
    upperFloor->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto renderComp = upperFloor->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto shape = std::make_shared<OBB>();
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
    auto s1 = std::make_shared<OBB>();
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
    auto s2 = std::make_shared<OBB>();
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
    auto s3 = std::make_shared<OBB>();
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
    auto s4 = std::make_shared<OBB>();
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
    auto s5 = std::make_shared<OBB>();
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
    auto rc7a = tunnelFloor1->addComponent<Render2D>();
    rc7a->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
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
    auto rc7b = tunnelFloor2->addComponent<Render2D>();
    rc7b->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
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
    auto rc8 = tunnelWallLeft->addComponent<Render2D>();
    rc8->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
    auto s8 = std::make_shared<OBB>();
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
    auto s9 = std::make_shared<OBB>();
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
    auto sDW = std::make_shared<OBB>();
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
    auto sDW2 = std::make_shared<OBB>();
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
    auto s10 = std::make_shared<OBB>();
    auto rb10 = landingPlatform->addComponent<RigidBody>();
    rb10->setMass(0.0f)->setDrag(1.0f)->setShape(s10)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb10->initialize();
}

void MapLoader::four(float offsetX, float offsetY, float offsetZ,
                         SceneGraph& sceneGraph,
                         std::shared_ptr<Camera> camera,
                         std::shared_ptr<Mesh> floorMesh,
                         std::shared_ptr<Material> floorMaterial) {
    // Starting platform
    {
        auto mainFloor = std::make_shared<GameObject>("MainFloor");
        sceneGraph.addNode(mainFloor);
        mainFloor->setLocalPosition(Vector3(0.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        mainFloor->setLocalScaling(Vector3(10.0f, 1.0f, 10.0f));
        auto renderComp = mainFloor->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = mainFloor->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    float platformSizes[] = { 4.0f, 4.0f, 4.0f, 4.0f};
    float yVariation[] = { 0.0f, 0.0f, 0.0f, 0.0f};
    float xSpacing = 6.0f;
    float xOffset[] = { 0.0f, 0.0f, 0.0f, 0.0f};

    for (int i = 0; i < 4; ++i) {
        auto platform = std::make_shared<GameObject>("Platform" + std::to_string(i + 1));
        sceneGraph.addNode(platform);
        float adjustedX = (i == 0) ? (xSpacing * 1.5f) : ((i + 1) * xSpacing + 5.0f);
        platform->setLocalPosition(Vector3(adjustedX + offsetX, yVariation[i] + offsetY, xOffset[i] + offsetZ));
        platform->setLocalScaling(Vector3(platformSizes[i], 0.5f, platformSizes[i]));
        auto renderComp = platform->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = platform->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Wall blocking player
    {
        auto wall = std::make_shared<GameObject>("wall");
        sceneGraph.addNode(wall);
        wall->setLocalPosition(Vector3(35.0f + offsetX, 4 + offsetY, offsetZ));
        wall->setLocalScaling(Vector3(1.0f, 10.0f, 10.0f));
        auto renderComp = wall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wall->addComponent<RigidBody>();
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
        upperFloor->setLocalPosition(Vector3(40.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        upperFloor->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
        auto renderComp = upperFloor->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = upperFloor->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }
}

void MapLoader::testing(float offsetX, float offsetY, float offsetZ, SceneGraph& sceneGraph, std::shared_ptr<Camera> camera, std::shared_ptr<Mesh> floorMesh, std::shared_ptr<Material> floorMaterial)
{

    // Floor pad
    {
        auto mainFloorLeft = std::make_shared<GameObject>("MainFloorLeft");
        sceneGraph.addNode(mainFloorLeft);
        mainFloorLeft->setLocalPosition(Vector3(-4.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        mainFloorLeft->setLocalScaling(Vector3(60.0f, 1.0f, 60.0f));
        auto renderComp = mainFloorLeft->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = mainFloorLeft->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();


    }

    //Running Wall
    {
        auto wallRunWall = std::make_shared<GameObject>("WallRunWall", GameObject::RUNNABLE_WALL);
        sceneGraph.addNode(wallRunWall);
        wallRunWall->setLocalPosition(Vector3(0.0f + offsetX, 2.5f + offsetY, -31.0f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(60.0f, 12.0f, 1.0f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

}