/*!****************************************************************************
 * \file   Movement3D3D.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-11-2025
 * 
 *****************************************************************************/
#include "Movement3D.h"


std::shared_ptr<Movement3D> Movement3D::setInputSystem(
  Input* _inputSystem)
{
  inputSystem = _inputSystem;

  return shared_from_this();
}

std::shared_ptr<Movement3D> Movement3D::setForce(float _force)
{
  force = _force;

  return shared_from_this();
}

std::shared_ptr<Movement3D> Movement3D::setRotationalForce(float _rotationalForce)
{
  rotationalForce = _rotationalForce;

  return shared_from_this();
}

std::shared_ptr<Movement3D> Movement3D::setAction(Action action, Key key)
{
  std::function<void(std::shared_ptr<PhysicsBody>)> actionFunction;
  switch (action) {
  case Forward:
    actionFunction = [this, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyForce(Vector3(0.0f, 0.0f, -force));
      } };
    break;
  case Back:
    actionFunction = [this, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyForce(Vector3(0.0f, 0.0f, force));
      } };
    break;
  case Left:
    actionFunction = [this, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyForce(Vector3(-force, 0.0f, 0.0f));
      } };
    break;
  case Right:
    actionFunction = [this, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyForce(Vector3(force, 0.0f, 0.0f));
      } };
    break;
  case Up:
    actionFunction = [this, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyForce(Vector3(0.0f, force, 0.0f));
      } };
    break;
  case Down:
    actionFunction = [this, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyForce(Vector3(0.0f, -force, 0.0f));
      } };
    break;
  case RollClockwise:
    actionFunction = [this, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyRotationalForce(Vector3(0.0f, 0.0f, -force));
      } };
    break;
  case RollAntiClockwise:
    actionFunction = [this, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyRotationalForce(Vector3(0.0f, 0.0f, force));
      } };
    break;
  case PitchClockwise:
    actionFunction = [this, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyRotationalForce(Vector3(-force, 0.0f, 0.0f));
      } };
    break;
  case PitchAnticlockwise:
    actionFunction = [this, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyRotationalForce(Vector3(force, 0.0f, 0.0f));
      } };
    break;
  case YawClockwise:
    actionFunction = [this, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyRotationalForce(Vector3(0.0f, force, 0.0f));
      } };
    break;
  case YawAntiClockwise:
    actionFunction = [this, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyRotationalForce(Vector3(0.0f, -force, 0.0f));
      } };
    break;
  default:
    assert(("ERROR::MOVEMENT3D::INVALIDACTION") && false);
    action = Invalid;
    actionFunction = nullptr;
  }
  registeredActions[action] = actionFunction;
  return shared_from_this();
}

void Movement3D::initialize() {}

void Movement3D::update(float deltaTime)
{
  auto physicsComponent = parent->findComponent<PhysicsBody>();
  for (const auto& [action, actionFunction] : registeredActions) {
    actionFunction(physicsComponent);
  }
}

void Movement3D::shutdown() {}