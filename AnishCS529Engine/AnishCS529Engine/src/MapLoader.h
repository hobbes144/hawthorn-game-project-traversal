/*!****************************************************************************
 * \file   MapLoader.h
 * \author Lixiao Kuang
 * \date   03-11-2025
 * \brief  Map loader that loads different maps based on an ID.
 *
 * Usage:
 * 
 *   std::shared_ptr<RenderGraph> rg = mainRenderer->getRenderGraph();
 *   MapLoader::instance().initializeResources(rg);
 *   MapLoader::instance().loadMap(mapId, offsetX, offsetY, offsetZ,
 *       sceneGraph, camera, floorMesh, floorMaterial);
 *
 * Map IDs:
 *   1 = wallrun map
 *   2 = jump map
 *****************************************************************************/
#pragma once
#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <memory>
#include <iostream>
#include <string>

#include "GameObject.h"
#include "SceneGraph.h"
#include "Vector3.h"
#include "Camera.h"
#include "Mesh.h"
#include "Material.h"
#include "Render2D.h"
#include "RigidBody.h"
#include "OBB.h"
#include "Animate.h"
#include "TimeControlledRB.h"
#include "RenderGraph.h" 

#include "GlobalVariables.h"


class MapLoader {
public:
    /// Returns an instance of MapLoader.
    static MapLoader& instance();

    /*!
     * \brief Load a map given a map ID and positional offset.
     *
     * \param mapId         An integer representing the map type (example, 1 = wallrun, 2 = jump).
     * \param offsetX       X offset to add to each object's base position.
     * \param offsetY       Y offset to add to each object's base position.
     * \param offsetZ       Z offset to add to each object's base position.
     * \param sceneGraph    Reference to the SceneGraph where objects will be added.
     * \param camera        Shared pointer to the Camera.
     * \param floorMesh     Shared pointer to the Mesh used by map objects.
     * \param floorMaterial Shared pointer to the Material used by map objects.
     */

    void initializeResources(std::shared_ptr<RenderGraph> renderGraph);

    void loadMap(int mapId, float offsetX, float offsetY, float offsetZ,
                 SceneGraph& sceneGraph,
                 std::shared_ptr<Camera> camera);

private:
    MapLoader() = default;
    ~MapLoader() = default;
    MapLoader(const MapLoader&) = delete;
    MapLoader& operator=(const MapLoader&) = delete;

    // Materials
    std::shared_ptr<Mesh> boxMesh;
    std::shared_ptr<Mesh> sphereMesh;

    std::shared_ptr<Material> boxMaterial;
    std::shared_ptr<Material> floorMaterial;
    std::shared_ptr<Material> concreteMaterial;
    std::shared_ptr<Material> LightBlueConcrete;
    std::shared_ptr<Material> YellowConcrete;
    std::shared_ptr<Material> BrownConcrete;
    std::shared_ptr<Material> BlueConcrete;
    std::shared_ptr<Material> WhiteFloorTiles;
    std::shared_ptr<Material> grassMaterial;
    std::shared_ptr<Material> cracksMaterial;
    std::shared_ptr<Material> myhouseMaterial;
    std::shared_ptr<Material> brickMaterial;
    std::shared_ptr<Material> skyBoxMaterial;
    std::shared_ptr<Material> keyMaterial;
    


    //void loadWallrun(float offsetX, float offsetY, float offsetZ,
    //                     SceneGraph& sceneGraph,
    //                     std::shared_ptr<Camera> camera);

    void menu(float offsetX, float offsetY, float offsetZ,
          SceneGraph& sceneGraph,
          std::shared_ptr<Camera> camera);

    void tutorial(float offsetX, float offsetY, float offsetZ,
              SceneGraph& sceneGraph,
              std::shared_ptr<Camera> camera);

    void tutorial2(float offsetX, float offsetY, float offsetZ,
              SceneGraph& sceneGraph,
              std::shared_ptr<Camera> camera);

    void intermediate(float offsetX, float offsetY, float offsetZ,
         SceneGraph& sceneGraph,
         std::shared_ptr<Camera> camera);

    void advanced(float offsetX, float offsetY, float offsetZ,
             SceneGraph& sceneGraph,
             std::shared_ptr<Camera> camera);

    void victory(float offsetX, float offsetY, float offsetZ,
      SceneGraph& sceneGraph,
      std::shared_ptr<Camera> camera);
};

#endif // MAPLOADER_H
