#include "Tank.h"

std::shared_ptr<Tank> createTank(
  std::string name, Renderer* renderer,
  std::shared_ptr<Camera> camera, Vector3 color)
{
  auto tank = std::make_shared<Tank>(name);
  tank->addComponent<Render2D>()
    ->setRenderer(renderer)->setCamera(camera)
    ->setMaterial(createSolidColorMaterial(color))
    ->setMesh(createSquareMesh(name));

  auto tankShape = std::make_shared<AABB>(
    Vector3(-0.5f, -0.5f, -0.5f),
    Vector3(0.5f, 0.5f, 0.5f));

  tank->addComponent<PhysicsBody>()
    ->setMass(10.0f)->setFriction(100.0f)
    ->setShape(tankShape)
    ->registerToPhysicsManager(PhysicsManager::Instance());
  return tank;
}
