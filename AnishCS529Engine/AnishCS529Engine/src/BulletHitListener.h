/*!****************************************************************************
 * \file   BulletHitListener.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 * \brief  Listener for Bullet Hit event
 * 
 *****************************************************************************/
#pragma once

#include <functional>

#include "CollisionEvent.h"
#include "EventListener.h"
#include "Bullet.h"

class BulletHitListener : public EventListener<CollisionEvent> {
public:

	using CollisionCallback = std::function<void(std::shared_ptr<GameObject>, std::shared_ptr<GameObject>)>;

	BulletHitListener(std::shared_ptr<Bullet> owner);

	void OnEvent(const CollisionEvent& event) override;

	void setCallback(CollisionCallback callback) { onCollisionCallback = callback; }

private:
	std::shared_ptr<GameObject> owner;
	CollisionCallback onCollisionCallback;
};