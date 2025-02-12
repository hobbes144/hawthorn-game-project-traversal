#include "CollisionListener.h"

CollisionListener::CollisionListener(std::shared_ptr<GameObject> owner) : 
  owner(owner) {

  RegisterListener();
}


void CollisionListener::OnEvent(const CollisionEvent& event) {

  if (event.object1 == owner || event.object2 == owner) {
    std::cout << "Collision detected for " << owner->getName() << std::endl;

    std::shared_ptr<GameObject> other = 
      (event.object1 == owner) ? event.object2 : event.object1;
    if (onCollisionCallback) {
      onCollisionCallback(owner, other, event.point);
    }
  }
}
