/*!****************************************************************************
 * \file   RaycastManager.h
 * \author Nicholas Shaw (nick_shaw@me.com)
 * \par    **DigiPen Email**
 *    nick.shaw@digipen.edu
 * \par    **Course**
 *    GAM541
 * \date   03-01-2025
 * \brief  This is the RaycastManager class it is called when a raycast is made
 * 
 *****************************************************************************/
#ifndef RAYCAST_MANAGER
#define RAYCAST_MANAGER

#pragma once

#include "Ray.h"
#include "RaycastHit.h"
#include "src/SceneGraph.h"
#include "src/Node.h"

class RaycastManager
{

public: 
	static bool Raycast(const Ray& ray, const SceneGraph* sceneGraph, RaycastHit& hit, float maxDistance = FLT_MAX);

private:
	static bool processNode(const std::shared_ptr<Node>& node,
					 const Ray& ray,
					 RaycastHit& hit,
					 float& closeHitDistance);

};


#endif // !RAYCAST_MANAGER