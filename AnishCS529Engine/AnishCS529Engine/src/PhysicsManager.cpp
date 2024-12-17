#include "PhysicsManager.h"
#include <algorithm>

PhysicsManager& PhysicsManager::Instance() {
  static PhysicsManager instance;
  instance.initialize();
  return instance;
}

void PhysicsManager::addBody(std::shared_ptr<PhysicsBody> body) {
  bodies.push_back(body);
}

void PhysicsManager::removeBody(std::shared_ptr<PhysicsBody> body) {
  bodies.erase(
      std::remove(bodies.begin(), bodies.end(), body),
      bodies.end()
  );
}

void PhysicsManager::checkCollisions() {
  Contact contact;
  for (size_t i = 0; i < bodies.size(); i++) {
    if (!bodies[i]->getParent()->isEnabled()) continue;

    for (size_t j = i + 1; j < bodies.size(); j++) {
      if (!bodies[j]->getParent()->isEnabled()) continue;

      if (collisionGenerator.generateContact(bodies[i], bodies[j], contact)) {
        // Collision detected, broadcast event
        CollisionEvent event(
            contact.bodies[0]->getParent(),
            contact.bodies[1]->getParent(),
            contact.point
            );
        EventManager::Instance().BroadcastEvent(event);
      }
    }
  }
}

/*!****************************************************************************
 * \brief Initialize the PhysicsManager
 * 
 * ## Usage:
 * 
 * This function is not to be used. It is automatically executed in the 
 * Instance() call.
 * 
 * ## Explanation:
 * 
 * Initializes the CollisionGenerator object used by the PhysicsManager.
 * 
 *****************************************************************************/
void PhysicsManager::initialize()
{
  collisionGenerator.initialize();
}

/*!****************************************************************************
 * \brief Update the physics
 * 
 * ## Usage:
 * 
 * This function is to be called in the main loop's physics loop. Ideally it is
 * called using a separate physics timestep accumulator that is implemented in
 * the FramerateController class.
 * 
 * ## Explanation:
 * 
 * This will update all objects' positions based on their PhysicsBody state. It
 * will then check for collisions between any two bodies in the scene.
 * 
 * ## Note:
 * 
 * Because collision detection compares every Shape in the scene with every
 * other Shape, it is advised not to use too many collision Shapes. There are
 * more efficient ways to handle this, but we have not implemented them.
 * 
 * \param deltaTime Time passed since last update
 *****************************************************************************/
void PhysicsManager::update(const float deltaTime) {
  for (size_t i = 0; i < bodies.size(); i++) {
    if (bodies[i]->getParent()->isEnabled())
      bodies[i]->integrate(deltaTime);
  }
  checkCollisions();
}

/*!****************************************************************************
 * \brief Dummy shutdown function
 * 
 *****************************************************************************/
void PhysicsManager::shutdown() {}
