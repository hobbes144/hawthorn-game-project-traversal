#pragma once

#include <functional>

#include "CollisionEvent.h"
#include "EventListener.h"

class CollisionListener : public EventListener<CollisionEvent> {
public:

	using CollisionCallback = std::function<void(std::shared_ptr<GameObject>, std::shared_ptr<GameObject>)>;

	CollisionListener(std::shared_ptr<GameObject> owner);

	void OnEvent(const CollisionEvent& event) override;

	void setCallback(CollisionCallback callback) {}

private:
	std::shared_ptr<GameObject> owner;
	CollisionCallback onCollisionCallback;
};