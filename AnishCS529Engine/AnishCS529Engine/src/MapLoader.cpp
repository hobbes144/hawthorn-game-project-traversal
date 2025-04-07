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
    keyMaterial = Material::getMaterial<Material>("key", renderGraph);
}


void MapLoader::loadMap(int mapId, float offsetX, float offsetY, float offsetZ,
                        SceneGraph& sceneGraph,
                        std::shared_ptr<Camera> camera) {


    switch (mapId) {
    case -1:
        menu(offsetX, offsetY, offsetZ, sceneGraph, camera);
        break;
    case 0:
        tutorial(offsetX, offsetY, offsetZ, sceneGraph, camera);
        break;
    case 1:
        tutorial2(offsetX, offsetY, offsetZ, sceneGraph, camera);
        break;
    case 2:
        intermediate(offsetX, offsetY, offsetZ, sceneGraph, camera);
        break;
    case 3:
        advanced(offsetX, offsetY, offsetZ, sceneGraph, camera);
        break;
    case 4:
        victory(offsetX, offsetY, offsetZ, sceneGraph, camera);
        break;

    default:
        std::cerr << "[MapLoader] Map ID " << mapId << " is not recognized.\n";
        break;
    }
}








