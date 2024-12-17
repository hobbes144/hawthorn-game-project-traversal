#include "Wall.h"

std::shared_ptr<Wall> createWall(
  std::string name, Renderer* renderer,
  std::shared_ptr<Camera> camera, Vector3 color)
{
  auto wall = std::make_shared<Wall>(name);
  wall->addComponent<Render2D>()
    ->setRenderer(renderer)->setCamera(camera)
    ->setMaterial(createSolidColorMaterial(color))
    ->setMesh(createSquareMesh(name));

  auto wallShape = std::make_shared<AABB>(
    Vector3(-0.5f, -0.5f, -0.5f),
    Vector3(0.5f, 0.5f, 0.5f));

  wall->addComponent<PhysicsBody>()
    ->setMass(0.0f)
    ->setShape(wallShape)
    ->registerToPhysicsManager(PhysicsManager::Instance());
  return wall;
}
