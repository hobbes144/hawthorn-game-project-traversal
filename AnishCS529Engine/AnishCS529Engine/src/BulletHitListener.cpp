#include "precompiled.h"
#include "BulletHitListener.h"

BulletHitListener::BulletHitListener(std::shared_ptr<Bullet> owner) :
  owner(owner) {

  RegisterListener();
}


void BulletHitListener::OnEvent(const CollisionEvent& event) {

  if (event.object1 == owner || event.object2 == owner) {
    //std::cout << "Collision detected for " << owner->getName() << std::endl;

    std::shared_ptr<GameObject> other =
      (event.object1 == owner) ? event.object2 : event.object1;
    if (onCollisionCallback) {
      onCollisionCallback(owner, other);
    }
  }
}
