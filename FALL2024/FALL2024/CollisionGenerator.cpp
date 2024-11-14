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
  const Shape * a, const Shape * b, Contact & contact) {
  //TODO: Implement your algorithm here
  const AABB * boxA = static_cast<const AABB *>( a );
  const AABB * boxB = static_cast<const AABB *>( b );

  Vector3 minA = boxA->getMin();
  Vector3 maxA = boxA->getMax();
  Vector3 minB = boxB->getMin();
  Vector3 maxB = boxB->getMax();

  if (
    ( minA.x > maxB.x || maxA.x < minB.x ) ||
    ( minA.y > maxB.y || maxA.y < minB.y ) ||
    ( minA.z > maxB.z || maxA.z < minB.z ) ) {
    return false;
  }

  contact.point =
    boxA->getCenter() + ( ( boxB->getCenter() - boxA->getCenter() ) * (1/2) );

  return true;
}

bool CollisionGenerator::OBBvsOBB(const Shape* a, const Shape* b, Contact& contact) {
  //TODO: Implement your algorithm here
  const OBB * boxA = static_cast<const OBB *>( a );
  const OBB * boxB = static_cast<const OBB *>( b );

  // Vector between two centers
  Vector3 T = boxA->getCenter() - boxB->getCenter();

  Vector3 aRight = boxA->getRight();
  Vector3 aUp = boxA->getUp();
  Vector3 bRight = boxB->getRight();
  Vector3 bUp = boxB->getUp();
  Vector3 aExtents = boxA->getHalfExtents();
  Vector3 bExtents = boxB->getHalfExtents();

  // T projected to A's axes:
  T = Vector3(T.dot(aRight), T.dot(aUp), 1);

  // Projections of B's axes on A:
  Vector3 R[2];
  R[0].x = abs(aRight.dot(bRight)) + 0.0000000001f;
  R[0].y = abs(aRight.dot(bUp)) + 0.0000000001f;
  R[1].x = abs(aUp.dot(bRight)) + 0.0000000001f;
  R[1].y = abs(aUp.dot(bUp)) + 0.0000000001f;

  // A axes
  if ( abs(T.x) > ( aExtents.x +
    (
      bExtents.x * R[0].x +
      bExtents.y * R[0].y
      ) ) ) return false;
  if ( abs(T.y) > ( aExtents.y +
    (
      bExtents.x * R[1].x +
      bExtents.y * R[1].y
      ) ) ) return false;

  // B axes
  if ( ( abs(T.x * R[0].x + T.y * R[1].x) ) >
    ( bExtents.x +
      (
        aExtents.x * R[0].x +
        aExtents.y * R[1].x
        ) ) ) return false;
  if ( ( abs(T.x * R[0].y + T.y * R[1].y) ) >
    ( bExtents.y +
      (
        aExtents.x * R[0].y +
        aExtents.y * R[1].y
        ) ) ) return false;
  // Todo: Finish this for 3D. This much will work for 2D.

  return true;
}

bool CollisionGenerator::AABBvsOBB(const Shape* a, const Shape* b, Contact& contact) {
    //TODO: Implement your algorithm here

    return true;
}

bool CollisionGenerator::OBBvsAABB(const Shape* a, const Shape* b, Contact& contact) {
    return AABBvsOBB(b, a, contact);
}

void CollisionGenerator::initializeCollisionMatrix() {
    // Initialize all to nullptr
    for (auto& row : collisionTests)
        for (auto& test : row)
            test = nullptr;

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