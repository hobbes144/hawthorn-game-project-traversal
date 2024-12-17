/*!****************************************************************************
 * \file   CollisionGenerator.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-16-2024
 * \brief  Collision Generator class
 * 
 *****************************************************************************/
#ifndef COLLISION_GENERATOR_H
#define COLLISION_GERERATOR_H

#pragma once

/* Base class */
#include "Component.h"

/* Used classes */
#include "Contact.h"
#include "Shape.h"

class PhysicsManager;

class CollisionGenerator : public Component {
  friend class PhysicsManager;
public:
  using CollisionTest = bool(*)(
    const std::shared_ptr<Shape>, const std::shared_ptr<Shape>, Contact&);


  /* Component functions */
  void initialize();
  void update(float deltaTime);
  void shutdown();

private:
  CollisionGenerator() = default;
  ~CollisionGenerator() = default;

  void initializeCollisionMatrix();

  // Main collision check function
  bool generateContact(
    std::shared_ptr<PhysicsBody> body1,
    std::shared_ptr<PhysicsBody> body2,
    Contact& contact);

  // Collision test functions
  static bool AABBvsAABB(
    const std::shared_ptr<Shape> a, 
    const std::shared_ptr<Shape> b, 
    Contact& contact);
  static bool AABBvsOBB(
    const std::shared_ptr<Shape> a, 
    const std::shared_ptr<Shape> b, 
    Contact& contact);
  static bool AABBvsSphere(
    const std::shared_ptr<Shape> a, 
    const std::shared_ptr<Shape> b, 
    Contact& contact);

  static bool OBBvsOBB(
    const std::shared_ptr<Shape> a, 
    const std::shared_ptr<Shape> b, 
    Contact& contact);
  static bool OBBvsAABB(
    const std::shared_ptr<Shape> a, 
    const std::shared_ptr<Shape> b, 
    Contact& contact);
  static bool OBBvsSphere(
    const std::shared_ptr<Shape> a, 
    const std::shared_ptr<Shape> b, 
    Contact& contact);

  static bool SpherevsSphere(
    const std::shared_ptr<Shape> a, 
    const std::shared_ptr<Shape> b, 
    Contact& contact);
  static bool SpherevsAABB(
    const std::shared_ptr<Shape> a, 
    const std::shared_ptr<Shape> b, 
    Contact& contact);
  static bool SpherevsOBB(
    const std::shared_ptr<Shape> a, 
    const std::shared_ptr<Shape> b, 
    Contact& contact);


  // The collision test table
  std::array<std::array<CollisionTest, 3>, 3> collisionTests;
};

#endif // COLLISION_GENERATOR_H
