/*!****************************************************************************
 * \file   CollisionListener.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \author Mariojulio Osmin Zaldivar Alvarez (ex-Adjunct Professor)
 *   (zaldivaralvarez@gmail.com) (Advising and Base Code)
 * \par    **Course**
 *    GAM541
 * \brief  Collision Listener that receives the Collision Event
 * 
 * Copyright © 2025 DIGIPEN Institute of Technology. All rights reserved.
 *
 *****************************************************************************/
#pragma once

#include <functional>

#include "CollisionEvent.h"
#include "EventListener.h"

class CollisionListener : public EventListener<CollisionEvent> {
public:

	using CollisionCallback = std::function<void(std::shared_ptr<GameObject>, std::shared_ptr<GameObject>, const Vector3&)>;

	CollisionListener(std::shared_ptr<GameObject> owner);

	void OnEvent(const CollisionEvent& event) override;

	void setCallback(CollisionCallback callback) { onCollisionCallback = callback; }

private:
	std::shared_ptr<GameObject> owner;
	CollisionCallback onCollisionCallback;
};