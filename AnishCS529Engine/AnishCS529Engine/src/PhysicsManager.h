#pragma once

#include "CollisionEvent.h"
#include "CollisionGenerator.h"
#include "EventManager.h"
#include "PhysicsBody.h"
#include "RigidBody.h"

#include <vector>

class PhysicsManager : public Component {
public:
  static PhysicsManager& Instance();

  void initialize();
  void update(float deltaTime);
  void shutdown();

  void addBody(std::shared_ptr<PhysicsBody> body);
  void removeBody(std::shared_ptr<PhysicsBody> body);

  const std::vector<std::shared_ptr<PhysicsBody>>& getBodies() const { 
    return bodies;
  }

  bool isHandledCollision(const std::shared_ptr<PhysicsBody> A, const std::shared_ptr<PhysicsBody> B) const;
  void addHandledCollision(const std::shared_ptr<PhysicsBody> A, const std::shared_ptr<PhysicsBody> B);
  void resetHandledCollisions();

  std::vector<GameObject> getContactedObjects(GameObject body);
  bool isInContact(GameObject body1, GameObject body2);
  void clearContactCache();

private:
  PhysicsManager() = default;
  PhysicsManager(const PhysicsManager&) = delete;
  PhysicsManager& operator=(const PhysicsManager&) = delete;

  void checkCollisions();

  std::vector<std::shared_ptr<PhysicsBody>> bodies;
  std::vector<std::pair< std::shared_ptr<PhysicsBody>, std::shared_ptr<PhysicsBody>>> handledCollisions;
  CollisionGenerator collisionGenerator;

  std::vector<std::pair<GameObject, GameObject>> contactCache;
};