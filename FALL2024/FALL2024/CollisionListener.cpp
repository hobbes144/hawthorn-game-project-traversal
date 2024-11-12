#include "CollisionListener.h"

CollisionListener::CollisionListener(RenderableNode* owner) : owner(owner) {
    RegisterListener(); 
}


void CollisionListener::OnEvent(const CollisionEvent& event) {

    if (event.object1 == owner || event.object2 == owner) {
        std::cout << "Collision detected for " << owner->getName() << std::endl;

        RenderableNode* other = (event.object1 == owner) ? event.object2 : event.object1;
        if (onCollisionCallback) {
            onCollisionCallback(owner, other);
        }
    }
}
