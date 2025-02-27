#include "precompiled.h"
#include "Tank.h"

void onTankHit(
  std::shared_ptr<GameObject> obj1, 
  std::shared_ptr<GameObject> obj2, 
  const Vector3& point) {

  std::shared_ptr<Tank> tank;
  std::shared_ptr<GameObject> other;
  if (!(tank = std::dynamic_pointer_cast<Tank>(obj1))) {
    tank = std::dynamic_pointer_cast<Tank>(obj2);
    other = obj1;
  }
  else {
    other = obj2;
  }

  auto tankPtr = std::dynamic_pointer_cast<Tank>(other);
  if (tankPtr) {
    other->disable();
    tank->disable();
    return;
  }

  auto wallPtr = std::dynamic_pointer_cast<Wall>(other);
  if (wallPtr) {
    auto tankPhysicsComponent = tank->findComponent<PhysicsBody>();
    Vector3 f = tankPhysicsComponent->getVelocity();
    if (wallPtr->getName() == "upWall") {
      f.y = -f.y * 5000.0f;
      f.y -= 1000.0f;
    }
    if (wallPtr->getName() == "downWall") {
      f.y = -f.y * 5000.0f;
      f.y += 1000.0f;
    }
    if (wallPtr->getName() == "leftWall") {
      f.x = -f.x * 5000.0f;
      f.x -= 1000.0f;
    }
    if (wallPtr->getName() == "rightWall") {
      f.x = -f.x * 5000.0f;
      f.x += 1000.0f;
    }
    f = f;
    tankPhysicsComponent->applyForce(f);
    return;
  }
}

//std::shared_ptr<Tank> createTank(
//  std::string name, Renderer* renderer,
//  std::shared_ptr<Camera> camera, Vector3 color)
//{
//  auto tank = std::make_shared<Tank>(name);
//  tank->addComponent<Render2D>()
//    ->setRenderer(renderer)->setCamera(camera)
//    ->setMaterial(createSolidColorMaterial(color))
//    ->setMesh(createSquareMesh(name));
//
//  auto tankShape = std::make_shared<AABB>(
//    Vector3(-0.5f, -0.5f, -0.5f),
//    Vector3(0.5f, 0.5f, 0.5f));
//
//  tank->addComponent<PhysicsBody>()
//    ->setMass(10.0f)->setFriction(100.0f)
//    ->setShape(tankShape)
//    ->registerToPhysicsManager(PhysicsManager::Instance());
//  return tank;
//}
//
//std::shared_ptr<Tank> createTank(
//  std::string name, Renderer* renderer,
//  std::shared_ptr<Camera> camera, const std::string& textureFile)
//{
//  auto tank = std::make_shared<Tank>(name);
//  tank->addComponent<Render2D>()
//    ->setRenderer(renderer)->setCamera(camera)
//    ->setMaterial(createTextureMaterial(textureFile))
//    ->setMesh(createSquareMesh(name));
//
//  auto tankShape = std::make_shared<AABB>(
//    Vector3(-0.5f, -0.5f, -0.5f),
//    Vector3(0.5f, 0.5f, 0.5f));
//
//  tank->addComponent<PhysicsBody>()
//    ->setMass(10.0f)->setFriction(100.0f)
//    ->setShape(tankShape)
//    ->registerToPhysicsManager(PhysicsManager::Instance());
//  return tank;
//}
