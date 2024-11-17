#include "CollisionGenerator.h"
#include "AABB.h"
#include "OBB.h"
#include "Circle.h"

CollisionGenerator::CollisionGenerator() {
  initializeCollisionMatrix();
}

bool CollisionGenerator::generateContact(PhysicsBody* body1, PhysicsBody* body2, Contact& contact) {
  Shape* shape1 = body1->getShape();
  Shape* shape2 = body2->getShape();

  if (!shape1 || !shape2) return false;

  int type1 = static_cast<int>(shape1->getType());
  int type2 = static_cast<int>(shape2->getType());

  CollisionTest test = collisionTests[type1][type2];
  if (test) {
    if (test(shape1, shape2, contact)) {
      contact.bodies[0] = body1;
      contact.bodies[1] = body2;
      return true;
    }
  }
  return false;
}

bool CollisionGenerator::AABBvsAABB(
    const Shape* a, const Shape* b, Contact& contact) {
  //TODO: Implement your algorithm here
  const AABB* boxA = static_cast<const AABB*>(a);
  const AABB* boxB = static_cast<const AABB*>(b);

  Vector3 minA = boxA->getMin();
  Vector3 maxA = boxA->getMax();
  Vector3 minB = boxB->getMin();
  Vector3 maxB = boxB->getMax();

  if (
    (minA.x > maxB.x || maxA.x < minB.x) ||
    (minA.y > maxB.y || maxA.y < minB.y) ||
    (minA.z > maxB.z || maxA.z < minB.z)) {
    return false;
  }

  contact.point = 
    boxA->getCenter() + ((boxB->getCenter() - boxA->getCenter()) / 2);

  return true;
}

bool CollisionGenerator::OBBvsOBB(const Shape* a, const Shape* b, Contact& contact) {
  const OBB* boxA = static_cast<const OBB*>(a);
  const OBB* boxB = static_cast<const OBB*>(b);

  float minPenDepth = 0.0f;
  float penDepth = 0.0f;
  
  // Vector between two centers (scaled up appropriately)
  Vector3 T = (boxA->getCenter() - boxB->getCenter());

  const Vector3* aAxes = boxA->getAxes();
  const Vector3* bAxes = boxB->getAxes();
  Vector3 aExtents = boxA->getHalfExtents();
  Vector3 bExtents = boxB->getHalfExtents();

  // T projected to A's axes:
  T = Vector3(T.dot(aAxes[0]), T.dot(aAxes[1]), T.dot(aAxes[2]));

  // Projections of B's axes on A:
  Vector3 R[3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      R[i][j] = abs(aAxes[i].dot(bAxes[j])) + 0.0000000001f;
    }
  }

  // A0 axis
  // We calculate this separately so we can get the initial pen depth
  minPenDepth = penDepth = (aExtents[0] +
      (
        bExtents[0] * R[0][0] +
        bExtents[1] * R[0][1] +
        bExtents[2] * R[0][2]
        )) - T[0];
  if (penDepth <= 0) return false;

  // A1 and A2 axes
  for (int i = 1; i < 3; i++) {
    penDepth = (aExtents[i] +
      (
        bExtents[0] * R[i][0] +
        bExtents[1] * R[i][1] +
        bExtents[2] * R[i][2]
        )) - T[0];
    if (penDepth <= 0) return false;
    minPenDepth = std::min(minPenDepth, penDepth);
  }

  // B axes
  for (int i = 0; i < 3; i++) {
    penDepth = (bExtents[i] +
        (
          aExtents[0] * R[0][i] +
          aExtents[1] * R[1][i] +
          aExtents[2] * R[2][i]
          )) - abs(T[0] * R[0][i] + T[1] * R[1][i] + T[2] * R[2][i]);
    if (penDepth <= 0) return false;
    minPenDepth = std::min(minPenDepth, penDepth);
  }

  // A0xB0 axis
  penDepth = (
      aExtents[1] * R[2][0] + aExtents[2] * R[1][0] +
      bExtents[1] * R[0][2] + bExtents[2] * R[0][1]
    ) - abs(T[2] * R[1][0] - T[1] * R[2][0]);
  if (penDepth <= 0) return false;
  minPenDepth = std::min(minPenDepth, penDepth);

  // A0xB1 axis
  penDepth = (
      aExtents[1] * R[2][1] + aExtents[2] * R[1][1] +
      bExtents[0] * R[0][2] + bExtents[2] * R[0][0]
    ) - abs(T[2] * R[1][1] - T[1] * R[2][1]);
  if (penDepth <= 0) return false;
  minPenDepth = std::min(minPenDepth, penDepth);

  // A0xB2 axis
  penDepth = (
      aExtents[1] * R[2][2] + aExtents[2] * R[1][2] +
      bExtents[0] * R[0][1] + bExtents[1] * R[0][0]
    ) - abs(T[2] * R[1][2] - T[1] * R[2][2]);
  if (penDepth <= 0) return false;
  minPenDepth = std::min(minPenDepth, penDepth);

  // A1xB0 axis
  if (
    abs(T[0] * R[2][0] - T[2] * R[0][0]) >
    (
      aExtents[0] * R[2][0] + aExtents[2] * R[0][0] +
      bExtents[1] * R[1][2] + bExtents[2] * R[1][1]
      )
  ) return false;

  // A1xB1 axis
  if (
    abs(T[0] * R[2][1] - T[2] * R[0][1]) >
    (
      aExtents[0] * R[2][1] + aExtents[2] * R[0][1] +
      bExtents[0] * R[1][2] + bExtents[2] * R[1][0]
      )
  ) return false;

  // A1xB2 axis
  if (
    abs(T[0] * R[2][2] - T[2] * R[0][2]) >
    (
      aExtents[0] * R[2][2] + aExtents[2] * R[0][2] +
      bExtents[0] * R[1][1] + bExtents[1] * R[1][0]
      )
  ) return false;

  // A2xB0 axis
  if (
    abs(T[1] * R[0][0] - T[0] * R[1][0]) >
    (
      aExtents[0] * R[1][0] + aExtents[1] * R[0][0] +
      bExtents[1] * R[2][2] + bExtents[2] * R[2][1]
      )
  ) return false;

  // A2xB1 axis
  if (
    abs(T[1] * R[0][1] - T[0] * R[1][1]) >
    (
      aExtents[0] * R[1][1] + aExtents[1] * R[0][1] +
      bExtents[0] * R[2][2] + bExtents[2] * R[2][0]
      )
  ) return false;

  // A2xB2 axis
  if (
    abs(T[1] * R[0][2] - T[0] * R[1][2]) >
    (
      aExtents[0] * R[1][2] + aExtents[1] * R[0][2] +
      bExtents[0] * R[2][1] + bExtents[1] * R[2][0]
      )
  ) return false;

  // Todo: find point of contact

  return true;
}

bool CollisionGenerator::AABBvsOBB(const Shape* a, const Shape* b, Contact& contact) {
  //TODO: Implement your algorithm here
  const AABB* boxA = static_cast<const AABB*>(a);
  const OBB* boxB = static_cast<const OBB*>(b);
  
  //Vector3 minA = boxA->getMin();
  //Vector3 maxA = boxA->getMax();

  //// Finding intersection in X
  //Vector3 minB;
  //Vector3 maxB;
  //boxB->project(Vector3(1.0f, 0.0f, 0.0f), minB.x, maxB.x);
  //boxB->project(Vector3(0.0f, 1.0f, 0.0f), minB.y, maxB.y);
  //boxB->project(Vector3(0.0f, 0.0f, 0.1f), minB.z, maxB.z);

  //if (minA.x > maxB.x || maxA.x < minB.x) return false;
  //if (minA.y > maxB.y || maxA.y < minB.y) return false;
  //if (minA.z > maxB.z || maxA.z < minB.z) return false;

  // Vector between two centers (scaled up appropriately)
  Vector3 T = (boxA->getCenter() - boxB->getCenter());

  const Vector3 aAxes[3] = {
    Vector3(1.0f, 0.0f, 0.0f),
    Vector3(0.0f, 1.0f, 0.0f),
    Vector3(0.0f, 0.0f, 1.0f),
  };
  const Vector3* bAxes = boxB->getAxes();
  Vector3 aExtents = boxA->getHalfExtents();
  Vector3 bExtents = boxB->getHalfExtents();

  // T projected to A's axes:
  T = Vector3(T.dot(aAxes[0]), T.dot(aAxes[1]), T.dot(aAxes[2]));

  // Projections of B's axes on A:
  Vector3 R[3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      R[i][j] = abs(aAxes[i].dot(bAxes[j])) + 0.0000000001f;
    }
  }

  // A axes
  for (int i = 0; i < 3; i++) {
    if (abs(T[i]) > (aExtents[i] +
      (
        bExtents[0] * R[i][0] +
        bExtents[1] * R[i][1] +
        bExtents[2] * R[i][2]
        ))) return false;
  }

  // B axes
  for (int i = 0; i < 3; i++) {
    if (
      (abs(T[0] * R[0][i] + T[1] * R[1][i] + T[2] * R[2][i])) >
      abs(bExtents[i] +
        (
          aExtents[0] * R[0][i] +
          aExtents[1] * R[1][i] +
          aExtents[2] * R[2][i]
          ))) return false;
  }

  // A0xB0 axis
  if (
    abs(T[2] * R[1][0] - T[1] * R[2][0]) >
    abs(
      aExtents[1] * R[2][0] + aExtents[2] * R[1][0] +
      bExtents[1] * R[0][2] + bExtents[2] * R[0][1]
    )
  ) return false;

  // A0xB1 axis
  if (
    abs(T[2] * R[1][1] - T[1] * R[2][1]) >
    abs(
      aExtents[1] * R[2][1] + aExtents[2] * R[1][1] +
      bExtents[0] * R[0][2] + bExtents[2] * R[0][0]
    )
  ) return false;

  // A0xB2 axis
  if (
    abs(T[2] * R[1][2] - T[1] * R[2][2]) >
    abs(
      aExtents[1] * R[2][2] + aExtents[2] * R[1][2] +
      bExtents[0] * R[0][1] + bExtents[1] * R[0][0]
    )
  ) return false;

  // A1xB0 axis
  if (
    abs(T[0] * R[2][0] - T[2] * R[0][0]) >
    abs(
      aExtents[0] * R[2][0] + aExtents[2] * R[0][0] +
      bExtents[1] * R[1][2] + bExtents[2] * R[1][1]
    )
  ) return false;

  // A1xB1 axis
  if (
    abs(T[0] * R[2][1] - T[2] * R[0][1]) >
    abs(
      aExtents[0] * R[2][1] + aExtents[2] * R[0][1] +
      bExtents[0] * R[1][2] + bExtents[2] * R[1][0]
    )
  ) return false;

  // A1xB2 axis
  if (
    abs(T[0] * R[2][2] - T[2] * R[0][2]) >
    abs(
      aExtents[0] * R[2][2] + aExtents[2] * R[0][2] +
      bExtents[0] * R[1][1] + bExtents[1] * R[1][0]
    )
  ) return false;

  // A2xB0 axis
  if (
    abs(T[1] * R[0][0] - T[0] * R[1][0]) >
    abs(
      aExtents[0] * R[1][0] + aExtents[1] * R[0][0] +
      bExtents[1] * R[2][2] + bExtents[2] * R[2][1]
    )
  ) return false;

  // A2xB1 axis
  if (
    abs(T[1] * R[0][1] - T[0] * R[1][1]) >
    abs(
      aExtents[0] * R[1][1] + aExtents[1] * R[0][1] +
      bExtents[0] * R[2][2] + bExtents[2] * R[2][0]
    )
  ) return false;

  // A2xB2 axis
  if (
    abs(T[1] * R[0][2] - T[0] * R[1][2]) >
    abs(
      aExtents[0] * R[1][2] + aExtents[1] * R[0][2] +
      bExtents[0] * R[2][1] + bExtents[1] * R[2][0]
    )
  ) return false;

  return true;
}

bool CollisionGenerator::OBBvsAABB(const Shape* a, const Shape* b, Contact& contact) {
  return AABBvsOBB(b, a, contact);
}

void CollisionGenerator::initializeCollisionMatrix() {
  collisionTests[0][0] = AABBvsAABB;
  collisionTests[0][1] = AABBvsOBB;
  collisionTests[0][2] = AABBvsCircle;
  collisionTests[1][0] = OBBvsAABB;
  collisionTests[1][1] = OBBvsOBB;
  collisionTests[1][2] = OBBvsCircle;
  collisionTests[2][0] = CirclevsAABB;
  collisionTests[2][1] = CirclevsOBB;
  collisionTests[2][2] = CirclevsCircle;


  // Set up existing collision tests
  // TODO: register all the collision functions in the test table

}

bool CollisionGenerator::CirclevsCircle(const Shape* a, const Shape* b, Contact& contact) {
  const Circle* circle1 = static_cast<const Circle*>(a);
  const Circle* circle2 = static_cast<const Circle*>(b);

  Vector3 diff = circle2->getCenter() - circle1->getCenter();
  float distSquared = diff.magnitudSquared();
  float radiusSum = circle1->getRadius() + circle2->getRadius();

  if (distSquared <= radiusSum * radiusSum) {
    contact.point = circle1->getCenter() + diff * 0.5f;
    return true;
  }
  return false;
}

bool CollisionGenerator::CirclevsAABB(const Shape* a, const Shape* b, Contact& contact) {
  const Circle* circle = static_cast<const Circle*>(a);
  const AABB* aabb = static_cast<const AABB*>(b);

  // Find closest point on AABB to circle center
  Vector3 closestPoint;
  Vector3 circleCenter = circle->getCenter();

  // For each axis, clamp circle center to AABB bounds
  closestPoint.x = std::max(aabb->getMin().x, std::min(circleCenter.x, aabb->getMax().x));
  closestPoint.y = std::max(aabb->getMin().y, std::min(circleCenter.y, aabb->getMax().y));

  // Check if closest point is within circle's radius
  Vector3 diff = circleCenter - closestPoint;
  float distSquared = diff.magnitudSquared();

  if (distSquared <= circle->getRadius() * circle->getRadius()) {
    contact.point = closestPoint;
    return true;
  }
  return false;
}

bool CollisionGenerator::AABBvsCircle(const Shape* a, const Shape* b, Contact& contact) {
  return CirclevsAABB(b, a, contact);
}

bool CollisionGenerator::CirclevsOBB(const Shape* a, const Shape* b, Contact& contact) {
  const Circle* circle = static_cast<const Circle*>(a);
  const OBB* obb = static_cast<const OBB*>(b);

  // Convert circle center to OBB's local space
  Vector3 circleCenter = circle->getCenter() - obb->getCenter();

  // Get local space position using OBB's axes
  Vector3 localCenter(
      circleCenter.dot(obb->getRight()),
      circleCenter.dot(obb->getUp()),
      0.0f
  );

  // Find closest point in local space (clamp to OBB bounds)
  Vector3 closestPoint;
  closestPoint.x = std::max(-obb->getHalfExtents().x,
      std::min(localCenter.x, obb->getHalfExtents().x));
  closestPoint.y = std::max(-obb->getHalfExtents().y,
      std::min(localCenter.y, obb->getHalfExtents().y));

  // Convert back to world space
  Vector3 worldClosest = obb->getCenter() +
    obb->getRight() * closestPoint.x +
    obb->getUp() * closestPoint.y;

  // Check if closest point is within circle's radius
  Vector3 diff = circle->getCenter() - worldClosest;
  float distSquared = diff.magnitudSquared();

  if (distSquared <= circle->getRadius() * circle->getRadius()) {
    contact.point = worldClosest;
    return true;
  }
  return false;
}

bool CollisionGenerator::OBBvsCircle(const Shape* a, const Shape* b, Contact& contact) {
  return CirclevsOBB(b, a, contact);
}
