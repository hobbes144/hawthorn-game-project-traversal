#pragma once

#include "Event.h"
#include "RenderableNode.h"

class CollisionEvent : public Event {
public:
    CollisionEvent(RenderableNode* obj1, RenderableNode* obj2)
        : object1(obj1), object2(obj2) {}

    RenderableNode* object1;
    RenderableNode* object2;
};