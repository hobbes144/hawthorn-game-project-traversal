/*!****************************************************************************
 * \file   MapLoader.h
 * \author Lixiao Kuang
 * \date   03-11-2025
 * \brief  Map loader that loads different maps based on an ID.
 *
 * Usage:
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
#include "GameObject.h"
#include "SceneGraph.h"
#include "Vector3.h"
#include "Camera.h"
#include "Mesh.h"
#include "Material.h"

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
    void loadMap(int mapId, float offsetX, float offsetY, float offsetZ,
                 SceneGraph& sceneGraph,
                 std::shared_ptr<Camera> camera,
                 std::shared_ptr<Mesh> floorMesh,
                 std::shared_ptr<Material> floorMaterial);

private:
    MapLoader() = default;
    ~MapLoader() = default;
    MapLoader(const MapLoader&) = delete;
    MapLoader& operator=(const MapLoader&) = delete;

    void loadWallrun(float offsetX, float offsetY, float offsetZ,
                     SceneGraph& sceneGraph,
                     std::shared_ptr<Camera> camera,
                     std::shared_ptr<Mesh> floorMesh,
                     std::shared_ptr<Material> floorMaterial);

    void loadJump(float offsetX, float offsetY, float offsetZ,
                  SceneGraph& sceneGraph,
                  std::shared_ptr<Camera> camera,
                  std::shared_ptr<Mesh> floorMesh,
                  std::shared_ptr<Material> floorMaterial);
    void three(float offsetX, float offsetY, float offsetZ,
              SceneGraph& sceneGraph,
              std::shared_ptr<Camera> camera,
              std::shared_ptr<Mesh> floorMesh,
              std::shared_ptr<Material> floorMaterial);
    void testing(float offsetX, float offsetY, float offsetZ,
              SceneGraph& sceneGraph,
              std::shared_ptr<Camera> camera,
              std::shared_ptr<Mesh> floorMesh,
              std::shared_ptr<Material> floorMaterial);
};

#endif // MAPLOADER_H
