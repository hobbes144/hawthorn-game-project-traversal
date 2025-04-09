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

void MapLoader::initializeResources() {
    boxMesh = Mesh::createMesh("box", Mesh::Cube);
    sphereMesh = Mesh::createSphereMesh("sphere", 32);
    boxMaterial = Material::getMaterial<TextureMaterial>("box");
    floorMaterial = Material::getMaterial<TextureMaterial>("floor");
    concreteMaterial = Material::getMaterial<TextureMaterial>("concrete");
    grassMaterial = Material::getMaterial<TextureMaterial>("grass");
    cracksMaterial = Material::getMaterial<TextureMaterial>("cracks");
    myhouseMaterial = Material::getMaterial<TextureMaterial>("myhouse");
    brickMaterial = Material::getMaterial<TextureMaterial>("brick");
    skyBoxMaterial = Material::getMaterial<TextureMaterial>("skyBox");
    LightBlueConcrete = Material::getMaterial<TextureMaterial>("LightBlueConcrete");
    YellowConcrete = Material::getMaterial<TextureMaterial>("YellowConcrete");
    BrownConcrete = Material::getMaterial<TextureMaterial>("BrownConcrete");
    BlueConcrete = Material::getMaterial<TextureMaterial>("BlueConcrete");
    WhiteFloorTiles = Material::getMaterial<TextureMaterial>("WhiteFloorTiles");
    keyMaterial = Material::getMaterial<TextureMaterial>("key");
}


void MapLoader::loadMap(int mapId, float offsetX, float offsetY, float offsetZ,
                        SceneGraph& sceneGraph) {


    switch (mapId) {
    case -1:
        menu(offsetX, offsetY, offsetZ, sceneGraph);
        break;
    case 0:
        tutorial(offsetX, offsetY, offsetZ, sceneGraph);
        break;
    case 1:
        tutorial2(offsetX, offsetY, offsetZ, sceneGraph);
        break;
    case 2:
        intermediate(offsetX, offsetY, offsetZ, sceneGraph);
        break;
    case 3:
        advanced(offsetX, offsetY, offsetZ, sceneGraph);
        break;
    case 4:
        victory(offsetX, offsetY, offsetZ, sceneGraph);
        break;

    default:
        std::cerr << "[MapLoader] Map ID " << mapId << " is not recognized.\n";
        break;
    }
}

void MapLoader::writeLetter(SceneGraph& sceneGraph,
                            const std::string& meshPath,
                            const Vector3& position,
                            const Vector3& scale,
                            const Vector3& rotation,
                            std::shared_ptr<Material> keyMaterial)
{
    std::shared_ptr<Mesh> mesh = Mesh::loadMesh(meshPath);
    auto letter = std::make_shared<GameObject>("letter", GameObject::WALL);
    sceneGraph.addNode(letter);
    letter->setLocalPosition(position);
    letter->setLocalScaling(scale);
    letter->setLocalRotation(rotation);
    auto renderComp = letter->addComponent<Render3D>();
    renderComp->setMesh(mesh)->setMaterial(keyMaterial);
}








