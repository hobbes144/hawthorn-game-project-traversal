#include "precompiled.h"
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

bool PhysicsManager::isHandledCollision(const std::shared_ptr<PhysicsBody> A, const std::shared_ptr<PhysicsBody> B) const
{
  for (auto it = handledCollisions.begin(); it != handledCollisions.end(); ++it) {
    if (
      (it->first == A && it->second == B) ||
      (it->first == B && it->second == A))
      return true;
  }
  return false;
}

void PhysicsManager::addHandledCollision(
  const std::shared_ptr<PhysicsBody> A,
  const std::shared_ptr<PhysicsBody> B)
{
  handledCollisions.push_back(std::make_pair(A, B));
}

void PhysicsManager::resetHandledCollisions()
{
  handledCollisions.clear();
}

std::vector<std::shared_ptr<GameObject>> PhysicsManager::getContactedObjects(
  std::shared_ptr<GameObject> body)
{
  std::vector<std::shared_ptr<GameObject>> results;
  for (const auto& pair : contactCache) {
    if (pair.first == body) {
      results.push_back(pair.second);
    }
    else if(pair.second == body) {
      results.push_back(pair.first);
    }
  }
  return results;
}

bool PhysicsManager::isInContact(
  std::shared_ptr<GameObject> body1, std::shared_ptr<GameObject> body2)
{
  return std::any_of(
    contactCache.begin(),
    contactCache.end(),
    [body1, body2](
      const std::pair<std::shared_ptr<GameObject>,
      std::shared_ptr<GameObject>>& p)
    {
      return
        (p.first == body1 && p.second == body2) ||
        (p.first == body2 && p.second == body1);
    }
  );
}

void PhysicsManager::checkCollisions() {
  Contact contact;
  bool body1IsStatic;
  for (size_t i = 0; i < bodies.size(); i++) {
      if (!bodies[i]->getParent()->isEnabled()) continue;
      body1IsStatic = bodies[i]->getIsStatic();
      for (size_t j = i + 1; j < bodies.size(); j++) {
          if (!bodies[j]->getParent()->isEnabled()) continue;
          if (body1IsStatic && bodies[j]->getIsStatic()) continue;
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
  resetHandledCollisions();
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
