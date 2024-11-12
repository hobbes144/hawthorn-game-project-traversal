#include "PhysicsManager.h"
#include <algorithm>

PhysicsManager& PhysicsManager::Instance() {
  static PhysicsManager instance;
  return instance;
}

void PhysicsManager::addBody(PhysicsBody* body) {
  bodies.push_back(body);
}

void PhysicsManager::removeBody(PhysicsBody* body) {
  bodies.erase(
      std::remove(bodies.begin(), bodies.end(), body),
      bodies.end()
  );
}

void PhysicsManager::update(const float deltaTime) {
  for (size_t i = 0; i < bodies.size(); i++) {
    bodies[i]->integrate(deltaTime);
  }
  checkCollisions();
}


void PhysicsManager::checkCollisions() {
  Contact contact;
  for (size_t i = 0; i < bodies.size(); i++) {
    for (size_t j = i + 1; j < bodies.size(); j++) {
      if (collisionGenerator.generateContact(bodies[i], bodies[j], contact)) {
        // Collision detected, broadcast event
        CollisionEvent event(
            contact.bodies[0]->getOwner(),
            contact.bodies[1]->getOwner()
            );
        EventManager::Instance().BroadcastEvent(event);
      }
    }
  }
}
