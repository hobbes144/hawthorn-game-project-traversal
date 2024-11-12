#pragma once

#include "EventListener.h"
#include "CollisionEvent.h"

class CollisionListener : public EventListener<CollisionEvent> {
public:

	using CollisionCallback = std::function<void(RenderableNode*, RenderableNode*)>;

	CollisionListener(RenderableNode* owner);

	void OnEvent(const CollisionEvent& event) override;

	void setCallback(CollisionCallback callback) {}

private:
	RenderableNode* owner;
	CollisionCallback onCollisionCallback;
};