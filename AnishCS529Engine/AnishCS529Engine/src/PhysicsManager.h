#pragma once

#include "CollisionEvent.h"
#include "CollisionGenerator.h"
#include "EventManager.h"
#include "PhysicsBody.h"

#include <vector>

class PhysicsManager {
public:
  static PhysicsManager& Instance();

  void addBody(PhysicsBody* body);
  void removeBody(PhysicsBody* body);

  void update(const float deltaTime);

  const std::vector<PhysicsBody*>& getBodies() const { return bodies; }

private:
  PhysicsManager() = default;
  PhysicsManager(const PhysicsManager&) = delete;
  PhysicsManager& operator=(const PhysicsManager&) = delete;

  void checkCollisions();

  std::vector<PhysicsBody*> bodies;
  CollisionGenerator collisionGenerator;
};