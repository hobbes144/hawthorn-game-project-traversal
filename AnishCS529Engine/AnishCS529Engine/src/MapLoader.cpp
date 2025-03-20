#include "precompiled.h"
#include "MapLoader.h"
#include <iostream>
#include <string>
#include "Render2D.h"

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
    case 1:
        loadWallrun(offsetX, offsetY, offsetZ, sceneGraph, camera, floorMesh, floorMaterial);
        break;
    case 2:
        loadJump(offsetX, offsetY, offsetZ, sceneGraph, camera, floorMesh, floorMaterial);
        break;
    default:
        std::cerr << "[MapLoader] Map ID " << mapId << " is not recognized.\n";
        break;
    }
}

// Wallrun map 
void MapLoader::loadWallrun(float offsetX, float offsetY, float offsetZ,
                            SceneGraph& sceneGraph,
                            std::shared_ptr<Camera> camera,
                            std::shared_ptr<Mesh> floorMesh,
                            std::shared_ptr<Material> floorMaterial) {
// Left pad
{
    auto mainFloorLeft = std::make_shared<GameObject>("MainFloorLeft");
    sceneGraph.addNode(mainFloorLeft);
    mainFloorLeft->setLocalPosition(Vector3(-4.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
    mainFloorLeft->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto renderComp = mainFloorLeft->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
}

// Right pad
{
    auto mainFloorRight = std::make_shared<GameObject>("MainFloorRight");
    sceneGraph.addNode(mainFloorRight);
    mainFloorRight->setLocalPosition(Vector3(40.0f + offsetX, 0.0f + offsetY, 0.0f + offsetZ));
    mainFloorRight->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto renderComp = mainFloorRight->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
}

// Wall for wall running
{
    auto wallRunWall = std::make_shared<GameObject>("WallRunWall");
    sceneGraph.addNode(wallRunWall);
    wallRunWall->setLocalPosition(Vector3(18.0f + offsetX, 2.5f + offsetY, -4.0f + offsetZ));
    wallRunWall->setLocalScaling(Vector3(30.0f, 8.0f, 1.0f));
    auto renderComp = wallRunWall->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
}

std::cout << "[MapLoader] Wallrun map loaded with offset ("
    << offsetX << ", " << offsetY << ", " << offsetZ << ").\n";
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
    mainFloor->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto renderComp = mainFloor->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
}

// Platforms data arrays.
float platformSizes[] = { 4.0f, 3.5f, 3.0f, 3.2f, 3.6f, 3.1f, 3.4f, 3.7f, 4.2f };
float yVariation[] = { 0.3f, -0.2f, 0.5f, -0.4f, 0.2f, -0.3f, 0.4f, -0.2f, 0.1f };
float xSpacing = 6.0f;
float xOffset[] = { 2.0f, 2.0f, -3.0f, 3.0f, -4.0f, 4.0f, -5.0f, 5.0f, 8.0f };

for (int i = 0; i < 9; ++i) {
    auto platform = std::make_shared<GameObject>("Platform" + std::to_string(i + 1));
    sceneGraph.addNode(platform);
    float adjustedX = (i == 0) ? (xSpacing * 1.5f) : ((i + 1) * xSpacing + 5.0f);
    platform->setLocalPosition(Vector3(adjustedX + offsetX, yVariation[i] + offsetY, xOffset[i] + offsetZ));
    platform->setLocalScaling(Vector3(platformSizes[i], 0.5f, platformSizes[i]));
    auto renderComp = platform->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
}

// Exit platform
{
    auto upperFloor = std::make_shared<GameObject>("UpperFloor");
    sceneGraph.addNode(upperFloor);
    upperFloor->setLocalPosition(Vector3(60.0f + offsetX, 0.2f + offsetY, 8.0f + offsetZ));
    upperFloor->setLocalScaling(Vector3(8.0f, 1.0f, 8.0f));
    auto renderComp = upperFloor->addComponent<Render2D>();
    renderComp->setCamera(camera)->setMesh(floorMesh)->setMaterial(floorMaterial);
}

std::cout << "[MapLoader] Jump map loaded with offset ("
    << offsetX << ", " << offsetY << ", " << offsetZ << ").\n";
}
