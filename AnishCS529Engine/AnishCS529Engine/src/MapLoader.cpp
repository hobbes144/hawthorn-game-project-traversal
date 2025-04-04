#include "precompiled.h"
#include "DeathPlane.h"
#include "Door.h"
#include "InGameKey.h"
#include "KeyList.h"
#include "MainTestMaterial.h"
#include "MapLoader.h"
#include "Matrix4.h"
#include <random>
#include <math.h>

MapLoader& MapLoader::instance() {
    static MapLoader instance;
    return instance;
}

void MapLoader::initializeResources(std::shared_ptr<RenderGraph> renderGraph) {
    boxMesh = Mesh::createMesh("box", Mesh::Cube);
    sphereMesh = Mesh::createSphereMesh("sphere", 32);
    boxMaterial = Material::getMaterial<Material>("box", renderGraph);
    floorMaterial = Material::getMaterial<Material>("floor", renderGraph);
    concreteMaterial = Material::getMaterial<Material>("concrete", renderGraph);
    grassMaterial = Material::getMaterial<Material>("grass", renderGraph);
    cracksMaterial = Material::getMaterial<Material>("cracks", renderGraph);
    myhouseMaterial = Material::getMaterial<Material>("myhouse", renderGraph);
    brickMaterial = Material::getMaterial<Material>("brick", renderGraph);
    skyBoxMaterial = Material::getMaterial<Material>("skyBox", renderGraph);
    LightBlueConcrete = Material::getMaterial<Material>("LightBlueConcrete", renderGraph);
    YellowConcrete = Material::getMaterial<Material>("YellowConcrete", renderGraph);
    BrownConcrete = Material::getMaterial<Material>("BrownConcrete", renderGraph);
    BlueConcrete = Material::getMaterial<Material>("BlueConcrete", renderGraph);
    WhiteFloorTiles = Material::getMaterial<Material>("WhiteFloorTiles", renderGraph);
}


void MapLoader::loadMap(int mapId, float offsetX, float offsetY, float offsetZ,
                        SceneGraph& sceneGraph,
                        std::shared_ptr<Camera> camera) {


    switch (mapId) {
    case 0:
        tutorial(offsetX, offsetY, offsetZ, sceneGraph, camera);
        break;
    case 1:
        intermediate(offsetX, offsetY, offsetZ, sceneGraph, camera);
        break;
    case 2:
        advanced(offsetX, offsetY, offsetZ, sceneGraph, camera);
        break;
    case 3:
        three(offsetX, offsetY, offsetZ, sceneGraph, camera);
        break;
    case 4:
        four(offsetX, offsetY, offsetZ, sceneGraph, camera);
        break;
    case 5:
        loadWallrun(offsetX, offsetY, offsetZ, sceneGraph, camera);
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



void MapLoader::tutorial(float offsetX, float offsetY, float offsetZ, SceneGraph& sceneGraph, std::shared_ptr<Camera> camera){


    
    // Keys & Doors test
    {
        std::shared_ptr<Mesh> keyMesh = Mesh::loadMesh("media/Map/Big_Button.fbx");
        auto key = std::make_shared<GameObject>("key", GameObject::WALL);
        sceneGraph.addNode(key);
        key->setLocalPosition(Vector3(-396.0f + offsetX, 0.5f + offsetY, 4.0f + offsetZ));
        key->setLocalScaling(Vector3(0.03f, 0.01f, 0.03f));
        auto renderComp = key->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(keyMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto keyComp = key->addComponent<InGameKey>();
        keyComp->setID(0);
        keyComp->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        keyComp->initialize();


    }
    {
        auto testDoor = std::make_shared<GameObject>("TestDoor", GameObject::WALL);
        sceneGraph.addNode(testDoor);
        testDoor->setLocalPosition(Vector3(-399.7f + offsetX, 2.5f + offsetY, 0.0f + offsetZ));
        testDoor->setLocalScaling(Vector3(0.3f, 5.0f, 3.0f));
        auto renderComp = testDoor->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(BrownConcrete);
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
        LeftWall->setLocalScaling(Vector3(420.0f, 40.0f, 1.0f));
        auto renderComp = LeftWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        RightWall->setLocalScaling(Vector3(420.0f, 40.0f, 1.0f));
        auto renderComp = RightWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        BackWall->setLocalScaling(Vector3(1.0f, 40.0f, 20.0f));
        auto renderComp = BackWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        FrontWall->setLocalScaling(Vector3(1.0f, 40.0f, 20.0f));
        auto renderComp = FrontWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        TopWall->setLocalPosition(Vector3(-200.0f + offsetX, 24.0f + offsetY, 0.0f + offsetZ));
        TopWall->setLocalScaling(Vector3(420.0f, 1.0f, 20.0f));
        auto renderComp = TopWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        DP1->setLocalPosition(Vector3(-200.0f + offsetX, -12.0f + offsetY, 0.0f + offsetZ));
        DP1->setLocalScaling(Vector3(420.0f, 1.0f, 20.0f));
        //DP1->setLocalRotation(Vector3(0.0f, 1.57f, 0.0f));
        auto renderComp = DP1->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(cracksMaterial);
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
        Floor1->setLocalPosition(Vector3(-20.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        Floor1->setLocalScaling(Vector3(60.0f, 1.0f, 20.0f));
        Floor1->setLocalRotation(Vector3(0.0f, 0.0f, 0.0f));
        auto renderComp = Floor1->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Floor1->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }
    // Box1
    {
        auto Box1 = std::make_shared<GameObject>("Box1");
        sceneGraph.addNode(Box1);
        Box1->setLocalPosition(Vector3(-20.0f + offsetX, 1.0f + offsetY, 0.0f + offsetZ));
        Box1->setLocalScaling(Vector3(10.0f, 5.0f, 20.0f));
        auto renderComp = Box1->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Box1->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }


    // Pit wall
    {
        auto pitWall1 = std::make_shared<GameObject>("pitWall1");
        sceneGraph.addNode(pitWall1);
        pitWall1->setLocalPosition(Vector3(-49.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall1->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall1->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        auto renderComp = pitWall2->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Pit floor
    {
        auto pitFloor = std::make_shared<GameObject>("pitFloor");
        sceneGraph.addNode(pitFloor);
        pitFloor->setLocalPosition(Vector3(-58.0f + offsetX, -10.0f + offsetY, 0.0f + offsetZ));
        pitFloor->setLocalScaling(Vector3(20.0f, 1.0f, 20.0f));
        auto renderComp = pitFloor->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitFloor->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Pit box
    {
        auto pitBox = std::make_shared<GameObject>("pitBox");
        sceneGraph.addNode(pitBox);
        pitBox->setLocalPosition(Vector3(-45.0f + offsetX, -10.0f + offsetY, 0.0f + offsetZ));
        pitBox->setLocalScaling(Vector3(20.0f, 10.0f, 20.0f));
        auto renderComp = pitBox->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        Floor2->setLocalPosition(Vector3(-80.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        Floor2->setLocalScaling(Vector3(30.0f, 1.0f, 20.0f));
        auto renderComp = Floor2->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        pitWall1->setLocalPosition(Vector3(-94.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall1->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall1->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        pitWall2->setLocalPosition(Vector3(-105.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall2->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall2->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        Floor3->setLocalPosition(Vector3(-120.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        Floor3->setLocalScaling(Vector3(30.0f, 1.0f, 20.0f));
        auto renderComp = Floor3->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    {
        auto pitWall1 = std::make_shared<GameObject>("pitWall1");
        sceneGraph.addNode(pitWall1);
        pitWall1->setLocalPosition(Vector3(-134.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall1->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall1->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall1->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Pit wall2
    {
        auto pitWall2 = std::make_shared<GameObject>("pitWall2");
        sceneGraph.addNode(pitWall2);
        pitWall2->setLocalPosition(Vector3(-184.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall2->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall2->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Pit floor 2
    {
        auto pitFloor = std::make_shared<GameObject>("pitFloor");
        sceneGraph.addNode(pitFloor);
        pitFloor->setLocalPosition(Vector3(-160.0f + offsetX, -10.0f + offsetY, 0.0f + offsetZ));
        pitFloor->setLocalScaling(Vector3(50.0f, 1.0f, 20.0f));
        auto renderComp = pitFloor->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        pitBox->setLocalPosition(Vector3(-135.0f + offsetX, -10.0f + offsetY, 0.0f + offsetZ));
        pitBox->setLocalScaling(Vector3(10.0f, 10.0f, 20.0f));
        auto renderComp = pitBox->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitBox->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Wall Running
    {
        auto wallRunWall = std::make_shared<GameObject>("WallRunWall", GameObject::RUNNABLE_WALL);
        sceneGraph.addNode(wallRunWall);
        wallRunWall->setLocalPosition(Vector3(-160.0f + offsetX, 4.0f + offsetY, -9.4f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(60.0f, 12.0f, 0.1f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = wallRunWall->addComponent<RigidBody>();
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
        Floor4->setLocalPosition(Vector3(-199.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        Floor4->setLocalScaling(Vector3(30.0f, 1.0f, 20.0f));
        auto renderComp = Floor4->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Floor4->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Wall Running 2
    {
        auto wallRunWall = std::make_shared<GameObject>("WallRunWall", GameObject::RUNNABLE_WALL);
        sceneGraph.addNode(wallRunWall);
        wallRunWall->setLocalPosition(Vector3(-230.0f + offsetX, 4.0f + offsetY, 9.4f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(60.0f, 12.0f, 0.1f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
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
    {
        auto pitWall1 = std::make_shared<GameObject>("pitWall1");
        sceneGraph.addNode(pitWall1);
        pitWall1->setLocalPosition(Vector3(-213.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall1->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall1->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        pitWall2->setLocalPosition(Vector3(-245.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall2->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall2->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Floor5 pad
    {
        auto Floor5 = std::make_shared<GameObject>("Floor5", GameObject::CHECKPOINT);
        sceneGraph.addNode(Floor5);
        Floor5->setLocalPosition(Vector3(-259.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        Floor5->setLocalScaling(Vector3(30.0f, 1.0f, 20.0f));
        auto renderComp = Floor5->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = Floor5->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Wall Running 3 & 4
        {
        auto wallRunWall = std::make_shared<GameObject>("WallRunWall", GameObject::RUNNABLE_WALL);
        sceneGraph.addNode(wallRunWall);
        wallRunWall->setLocalPosition(Vector3(-295.0f + offsetX, 4.0f + offsetY, -9.4f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(60.0f, 12.0f, 0.1f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
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
        wallRunWall->setLocalPosition(Vector3(-350.0f + offsetX, 4.0f + offsetY, 9.4f + offsetZ));
        wallRunWall->setLocalScaling(Vector3(60.0f, 12.0f, 0.1f));
        auto renderComp = wallRunWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(WhiteFloorTiles);
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
    {
        auto pitWall1 = std::make_shared<GameObject>("pitWall1");
        sceneGraph.addNode(pitWall1);
        pitWall1->setLocalPosition(Vector3(-273.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall1->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall1->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        pitWall2->setLocalPosition(Vector3(-375.5f + offsetX, -5.5f + offsetY, 0.0f + offsetZ));
        pitWall2->setLocalScaling(Vector3(1.0f, 10.0f, 20.0f));
        auto renderComp = pitWall2->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = pitWall2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Floor6 pad
    {
        auto Floor6 = std::make_shared<GameObject>("Floor6");
        sceneGraph.addNode(Floor6);
        Floor6->setLocalPosition(Vector3(-390.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        Floor6->setLocalScaling(Vector3(30.0f, 1.0f, 20.0f));
        auto renderComp = Floor6->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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

void MapLoader::intermediate(float offsetX, float offsetY, float offsetZ, SceneGraph& sceneGraph, std::shared_ptr<Camera> camera) {

    // Keys & Doors test
    {
        std::shared_ptr<Mesh> keyMesh = Mesh::loadMesh("media/Map/Big_Button.fbx");
        auto key = std::make_shared<GameObject>("key", GameObject::WALL);
        sceneGraph.addNode(key);
        key->setLocalPosition(Vector3(-186.0f + offsetX, 6.5f + offsetY, 4.0f + offsetZ));
        key->setLocalScaling(Vector3(0.03f, 0.01f, 0.03f));
        auto renderComp = key->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(keyMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto keyComp = key->addComponent<InGameKey>();
        keyComp->setID(1);
        keyComp->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        keyComp->initialize();


    }
    {
        auto testDoor = std::make_shared<GameObject>("TestDoor", GameObject::WALL);
        sceneGraph.addNode(testDoor);
        testDoor->setLocalPosition(Vector3(-189.7f + offsetX, 8.5f + offsetY, 0.0f + offsetZ));
        testDoor->setLocalScaling(Vector3(0.3f, 5.0f, 3.0f));
        auto renderComp = testDoor->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(BrownConcrete);
        auto shape = std::make_shared<OBB>();
        auto doorComp = testDoor->addComponent<Door>();
        doorComp->setID(1);
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
        LeftWall->setLocalScaling(Vector3(420.0f, 40.0f, 1.0f));
        auto renderComp = LeftWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        RightWall->setLocalScaling(Vector3(420.0f, 40.0f, 1.0f));
        auto renderComp = RightWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        BackWall->setLocalScaling(Vector3(1.0f, 40.0f, 20.0f));
        auto renderComp = BackWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        FrontWall->setLocalPosition(Vector3(-190.5f + offsetX, 4.0f + offsetY, 0.0f + offsetZ));
        FrontWall->setLocalScaling(Vector3(1.0f, 40.0f, 20.0f));
        auto renderComp = FrontWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        TopWall->setLocalPosition(Vector3(-200.0f + offsetX, 24.0f + offsetY, 0.0f + offsetZ));
        TopWall->setLocalScaling(Vector3(420.0f, 1.0f, 20.0f));
        auto renderComp = TopWall->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = TopWall->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }


    // deathplane 
    {
        auto DP1 = std::make_shared<GameObject>("DP1");
        sceneGraph.addNode(DP1);
        DP1->setLocalPosition(Vector3(-200.0f + offsetX, -12.0f + offsetY, 0.0f + offsetZ));
        DP1->setLocalScaling(Vector3(420.0f, 1.0f, 20.0f));
        //DP1->setLocalRotation(Vector3(0.0f, 1.57f, 0.0f));
        auto renderComp = DP1->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(cracksMaterial);
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
    // Starting platform
    {
        auto mainFloor = std::make_shared<GameObject>("MainFloor", GameObject::CHECKPOINT);
        sceneGraph.addNode(mainFloor);
        mainFloor->setLocalPosition(Vector3(-0.0f + offsetX, 0.0f + offsetY, -0.0f + offsetZ));
        mainFloor->setLocalScaling(Vector3(10.0f, 1.0f, 10.0f));
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

    float platformSizes[] = { 4.0f, 3.5f, 3.0f, 3.2f, 3.6f, 3.1f, 3.4f, 3.7f};
    float yVariation[] = { 0.3f, -5.2f, -3.5f, -1.4f, 0.f, 0.0f, 3.4f, 7.2f};
    float xSpacing = 8.0f;
    float xOffset[] = { 2.0f, 2.0f, -3.0f, 3.0f, -4.0f, 5.0f, -5.0f, 5.0f};

    for (int i = 0; i < 8; ++i) {
        auto platform = std::make_shared<GameObject>("Platform" + std::to_string(i + 1));
        sceneGraph.addNode(platform);
        float adjustedX = (i == 0) ? -(xSpacing * 1.5f) : -((i + 1) * xSpacing + 5.0f);
        platform->setLocalPosition(Vector3(adjustedX + offsetX, yVariation[i] + offsetY, -xOffset[i] + offsetZ));
        platform->setLocalScaling(Vector3(8.0f, 3.0f, 8.0f));
        auto renderComp = platform->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        
        if (i == 5 || i == 6) {
            auto rigidBody = platform->addComponent<RigidBody>();
            rigidBody->setMass(0.0f)
                ->setDrag(1.0f)
                ->setShape(shape)
                ->setStatic(true)
                ->registerToPhysicsManager(PhysicsManager::Instance());
            rigidBody->initialize();
            auto platformAnimate = platform->addComponent<Animate>();
            float direction = (i == 5) ? -1.0f : 1.0f;
            platformAnimate->setAnimateFunction(
                [currentTime = 0.0f, initialPos = platform->getLocalPosition().x, phase = direction](std::shared_ptr<GameObject> self, float deltaTime) mutable {
                    deltaTime *= timeScale;
                    float affineSpeed = 5.0f;
                    float affinePosVarianceX = 5.0f;

                    currentTime += deltaTime;

                    if ((phase == -1.0f) && (initialPos - affinePosVarianceX) > self->getWorldPosition().x)
                        phase = 1.0f;
                    else if ((phase == 1.0f) && (initialPos + affinePosVarianceX) < self->getWorldPosition().x)
                        phase = -1.0f;

                    Vector3 velocity = Vector3(affineSpeed * phase, 0.0f, 0.0f);
                    Vector3 newPos = self->getWorldPosition() + (velocity * deltaTime);
                    self->setWorldPosition(newPos);
                }
            );
            platformAnimate->runAnimateFunction(true);
        }
        if (i == 7) {
            auto rigidBody = platform->addComponent<RigidBody>();
            rigidBody->setMass(0.0f)
                ->setDrag(1.0f)
                ->setShape(shape)
                ->setStatic(true)
                ->registerToPhysicsManager(PhysicsManager::Instance());
            rigidBody->initialize();

            auto platformAnimate = platform->addComponent<Animate>();
            platformAnimate->setAnimateFunction(
                  [currentTime = 0.0f, initialPos = platform->getLocalPosition().y, phase = 1.0f](std::shared_ptr<GameObject> self, float deltaTime) mutable {


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

    // Checkpoint
    {
        auto checkpoint = std::make_shared<GameObject>("checkpoint", GameObject::CHECKPOINT);
        sceneGraph.addNode(checkpoint);
        checkpoint->setLocalPosition(Vector3(-80.0f + offsetX, 11.0f + offsetY, 0.0f + offsetZ));
        checkpoint->setLocalScaling(Vector3(12.0f, 3.0f, 12.0f));
        auto renderComp = checkpoint->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = checkpoint->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Wall
    {
        auto upperFloor = std::make_shared<GameObject>("upperFloor");
        sceneGraph.addNode(upperFloor);
        upperFloor->setLocalPosition(Vector3(-125.0f + offsetX, 30.0f + offsetY, 0.0f + offsetZ));
        upperFloor->setLocalScaling(Vector3(50.0f, 40.0f, 20.0f));
        auto renderComp = upperFloor->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = upperFloor->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    // Under Wall
    {
        auto lowerFloor = std::make_shared<GameObject>("lowerFloor");
        sceneGraph.addNode(lowerFloor);
        lowerFloor->setLocalPosition(Vector3(-125.0f + offsetX, -5.0f + offsetY, 0.0f + offsetZ));
        lowerFloor->setLocalScaling(Vector3(35.0f, 10.0f, 17.0f));
        auto renderComp = lowerFloor->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = lowerFloor->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }

    //// Wall
    //{
    //    auto wall = std::make_shared<GameObject>("wall");
    //    sceneGraph.addNode(wall);
    //    wall->setLocalPosition(Vector3(-115.0f + offsetX, -10.0f + offsetY, 0.0f + offsetZ));
    //    wall->setLocalScaling(Vector3(1.0f, 7.0f, 17.0f));
    //    auto renderComp = wall->addComponent<Render2D>();
    //    renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
    //    auto shape = std::make_shared<OBB>();
    //    auto rigidBody = wall->addComponent<RigidBody>();
    //    rigidBody->setMass(0.0f)
    //        ->setDrag(1.0f)
    //        ->setShape(shape)
    //        ->setStatic(true)
    //        ->registerToPhysicsManager(PhysicsManager::Instance());
    //    rigidBody->initialize();
    //}

    //// Wall2
    //{
    //    auto wall = std::make_shared<GameObject>("wall");
    //    sceneGraph.addNode(wall);
    //    wall->setLocalPosition(Vector3(-125.0f + offsetX, -5.0f + offsetY, 3.5f + offsetZ));
    //    wall->setLocalScaling(Vector3(1.0f, 10.0f, 10.0f));
    //    auto renderComp = wall->addComponent<Render2D>();
    //    renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
    //    auto shape = std::make_shared<OBB>();
    //    auto rigidBody = wall->addComponent<RigidBody>();
    //    rigidBody->setMass(0.0f)
    //        ->setDrag(1.0f)
    //        ->setShape(shape)
    //        ->setStatic(true)
    //        ->registerToPhysicsManager(PhysicsManager::Instance());
    //    rigidBody->initialize();
    //}

    //{
    //    auto wall = std::make_shared<GameObject>("wall");
    //    sceneGraph.addNode(wall);
    //    wall->setLocalPosition(Vector3(-135.0f + offsetX, -5.0f + offsetY, -3.5f + offsetZ));
    //    wall->setLocalScaling(Vector3(1.0f, 10.0f, 10.0f));
    //    auto renderComp = wall->addComponent<Render2D>();
    //    renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
    //    auto shape = std::make_shared<OBB>();
    //    auto rigidBody = wall->addComponent<RigidBody>();
    //    rigidBody->setMass(0.0f)
    //        ->setDrag(1.0f)
    //        ->setShape(shape)
    //        ->setStatic(true)
    //        ->registerToPhysicsManager(PhysicsManager::Instance());
    //    rigidBody->initialize();
    //}


    // Checkpoint 2
    {
        auto checkpoint2 = std::make_shared<GameObject>("checkpoint2");
        sceneGraph.addNode(checkpoint2);
        checkpoint2->setLocalPosition(Vector3(-180.0f + offsetX, -6.0f + offsetY, 0.0f + offsetZ));
        checkpoint2->setLocalScaling(Vector3(20.0f, 25.0f, 17.0f));
        auto renderComp = checkpoint2->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
        auto shape = std::make_shared<OBB>();
        auto rigidBody = checkpoint2->addComponent<RigidBody>();
        rigidBody->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(shape)
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance());
        rigidBody->initialize();
    }
}


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

// Jump Pad
{
    auto JumpPad = std::make_shared<GameObject>("JumpPad");
    sceneGraph.addNode(JumpPad);
    JumpPad->setLocalPosition(Vector3(-130.0f + offsetX, 26.0f + offsetY, 70.0f + offsetZ));
    JumpPad->setLocalScaling(Vector3(12.0f, 52.0f, 12.0f));
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

// Jump Pad
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

// Jump Pad2
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
// Moving Platforms
// ----------------
{
    auto createJumpPad = [&](const std::string& name, const Vector3& pos, const Vector3& scale, float rotationSpeed) {
        auto pad = std::make_shared<GameObject>(name);
        sceneGraph.addNode(pad);
        pad->setLocalPosition(pos);
        pad->setLocalScaling(scale);
        pad->setLocalRotation(Vector3(0.0f, 0.0f, 0.0f));

        pad->addComponent<Render2D>()->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);

        pad->addComponent<RigidBody>()
            ->setMass(0.0f)
            ->setDrag(1.0f)
            ->setShape(std::make_shared<OBB>())
            ->setStatic(true)
            ->registerToPhysicsManager(PhysicsManager::Instance())
            ->initialize();

        pad->addComponent<Animate>()->setAnimateFunction(
            [rotationSpeed](std::shared_ptr<GameObject> self, float deltaTime) {
                float radians = rotationSpeed * deltaTime * (3.14159265f / 180.0f);
                self->setLocalRotation(Quaternion::fromEuler(0.0f, radians, 0.0f) * self->getLocalRotation());
            }
        )->runAnimateFunction(true);
        };

    float startX = -110.0f;
    float endX = 120.0f;
    float step = 60.0f;

    Vector3 scaleTop(30.0f, 3.0f, 20.0f);
    Vector3 scaleBottom(20.0f, 3.0f, 30.0f); 

    int count = 0;
    for (float x = startX; x <= endX; x += step) {

        Vector3 posTop(x + offsetX, 65.0f + offsetY, 135.0f + offsetZ);
        createJumpPad("JumpPad" + std::to_string(count), posTop, scaleTop, +45.0f);


        Vector3 posBottom((x + 30.0f) + offsetX, 68.0f + offsetY, 110.0f + offsetZ);
        createJumpPad("JumpPad" + std::to_string(count), posBottom, scaleBottom, -45.0f);

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

                // Animate block movement and reset after 20 seconds
                block->addComponent<Animate>()->setAnimateFunction(
                    [velocity, startPos, time = 0.0f](std::shared_ptr<GameObject> self, float dt) mutable {
                        time += dt;
                        if (time >= 20.0f) { // changed from 12.0f to 20.0f
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
// Wallrun map 
void MapLoader::loadWallrun(float offsetX, float offsetY, float offsetZ,
                            SceneGraph& sceneGraph,
                            std::shared_ptr<Camera> camera) {
    // Start pad
    {
        auto mainFloorLeft = std::make_shared<GameObject>("MainFloorLeft");
        sceneGraph.addNode(mainFloorLeft);
        mainFloorLeft->setLocalPosition(Vector3(-1.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        mainFloorLeft->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
        auto renderComp = mainFloorLeft->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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

    // Wall2 for wall running
    {
        auto wallRunWall2 = std::make_shared<GameObject>("WallRunWall2");
        sceneGraph.addNode(wallRunWall2);
        wallRunWall2->setLocalPosition(Vector3(60.0f + offsetX, 2.5f + offsetY, -4.0f + offsetZ));
        wallRunWall2->setLocalScaling(Vector3(30.0f, 8.0f, 1.0f));
        auto renderComp = wallRunWall2->addComponent<Render2D>();
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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


void MapLoader::three(float offsetX, float offsetY, float offsetZ,
                      SceneGraph& sceneGraph,
                      std::shared_ptr<Camera> camera) {
    auto boxRoomFloor = std::make_shared<GameObject>("BoxRoomFloor");
    sceneGraph.addNode(boxRoomFloor);
    boxRoomFloor->setLocalPosition(Vector3(offsetX, offsetY, offsetZ));
    boxRoomFloor->setLocalScaling(Vector3(20.0f, 1.0f, 20.0f));
    auto rc1 = boxRoomFloor->addComponent<Render2D>();
    rc1->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    rc2->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    rc3->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    rc4->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    rc5->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    rc6->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    rc7a->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    rc7b->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    rc8->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    rc9->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    rcDW->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    rcDW2->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
    rc10->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
    auto s10 = std::make_shared<OBB>();
    auto rb10 = landingPlatform->addComponent<RigidBody>();
    rb10->setMass(0.0f)->setDrag(1.0f)->setShape(s10)->setStatic(true)
        ->registerToPhysicsManager(PhysicsManager::Instance());
    rb10->initialize();
}

void MapLoader::four(float offsetX, float offsetY, float offsetZ,
                         SceneGraph& sceneGraph,
                         std::shared_ptr<Camera> camera) {
    // Starting platform
    {
        auto mainFloor = std::make_shared<GameObject>("MainFloor");
        sceneGraph.addNode(mainFloor);
        mainFloor->setLocalPosition(Vector3(0.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
        mainFloor->setLocalScaling(Vector3(10.0f, 1.0f, 10.0f));
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
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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
        renderComp->setCamera(camera)->setMesh(boxMesh)->setMaterial(concreteMaterial);
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

