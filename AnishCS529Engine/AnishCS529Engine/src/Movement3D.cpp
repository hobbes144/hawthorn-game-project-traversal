/*!****************************************************************************
 * \file   Movement3D3D.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   02-11-2025
 * 
 *****************************************************************************/
#include "precompiled.h"
#include "Movement3D.h"
#include "Audio.h"


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
    actionFunction = [this, action, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if (inputSystem->isKeyDown(key)) {
        physicsBody->applyForce(Vector3(0.0f, 0.0f, -force));
        Movement3DEvent moveEvent(this->getParent(), action);
        EventManager::Instance().BroadcastEvent(moveEvent);
      } };
    break;
  case Back:
    actionFunction = [this, action, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if ( inputSystem->isKeyDown(key) ) {
        physicsBody->applyForce(Vector3(0.0f, 0.0f, force));
        Movement3DEvent moveEvent(this->getParent(), action);
        EventManager::Instance().BroadcastEvent(moveEvent);
      } };
    break;
  case Left:
    actionFunction = [this, action, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if ( inputSystem->isKeyDown(key) ) {
        physicsBody->applyForce(Vector3(-force, 0.0f, 0.0f));
        Movement3DEvent moveEvent(this->getParent(), action);
        EventManager::Instance().BroadcastEvent(moveEvent);
      } };
    break;
  case Right:
    actionFunction = [this, action, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if ( inputSystem->isKeyDown(key) ) {
        physicsBody->applyForce(Vector3(force, 0.0f, 0.0f));
        Movement3DEvent moveEvent(this->getParent(), action);
        EventManager::Instance().BroadcastEvent(moveEvent);
      } };
    break;
  case Up:
    actionFunction = [this, action, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if ( inputSystem->isKeyDown(key) ) {
        physicsBody->applyForce(Vector3(0.0f, force, 0.0f));
        Movement3DEvent moveEvent(this->getParent(), action);
        EventManager::Instance().BroadcastEvent(moveEvent);
      } };
    break;
  case Down:
    actionFunction = [this, action, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if ( inputSystem->isKeyDown(key) ) {
        physicsBody->applyForce(Vector3(0.0f, -force, 0.0f));
        Movement3DEvent moveEvent(this->getParent(), action);
        EventManager::Instance().BroadcastEvent(moveEvent);
      } };
    break;
  case RollClockwise:
    actionFunction = [this, action, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if ( inputSystem->isKeyDown(key) ) {
        physicsBody->applyRotationalForce(Vector3(0.0f, 0.0f, rotationalForce));
        Movement3DEvent moveEvent(this->getParent(), action);
        EventManager::Instance().BroadcastEvent(moveEvent);
      } };
    break;
  case RollAntiClockwise:
    actionFunction = [this, action, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if ( inputSystem->isKeyDown(key) ) {
        physicsBody->applyRotationalForce(Vector3(0.0f, 0.0f, -rotationalForce));
        Movement3DEvent moveEvent(this->getParent(), action);
        EventManager::Instance().BroadcastEvent(moveEvent);
      } };
    break;
  case PitchClockwise:
    actionFunction = [this, action, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if ( inputSystem->isKeyDown(key) ) {
        physicsBody->applyRotationalForce(Vector3(rotationalForce, 0.0f, 0.0f));
        Movement3DEvent moveEvent(this->getParent(), action);
        EventManager::Instance().BroadcastEvent(moveEvent);
      } };
    break;
  case PitchAnticlockwise:
    actionFunction = [this, action, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if ( inputSystem->isKeyDown(key) ) {
        physicsBody->applyRotationalForce(Vector3(-rotationalForce, 0.0f, 0.0f));
        Movement3DEvent moveEvent(this->getParent(), action);
        EventManager::Instance().BroadcastEvent(moveEvent);
      } };
    break;
  case YawClockwise:
    actionFunction = [this, action, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if ( inputSystem->isKeyDown(key) ) {
        physicsBody->applyRotationalForce(Vector3(0.0f, rotationalForce, 0.0f));
        Movement3DEvent moveEvent(this->getParent(), action);
        EventManager::Instance().BroadcastEvent(moveEvent);
      } };
    break;
  case YawAntiClockwise:
    actionFunction = [this, action, key](std::shared_ptr<PhysicsBody> physicsBody) {
      if ( inputSystem->isKeyDown(key) ) {
        physicsBody->applyRotationalForce(Vector3(0.0f, -rotationalForce, 0.0f));
        Movement3DEvent moveEvent(this->getParent(), action);
        EventManager::Instance().BroadcastEvent(moveEvent);
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

Movement3DListener::Movement3DListener(std::shared_ptr<GameObject> owner) :
  owner(owner) {

  RegisterListener();
}


void Movement3DListener::OnEvent(const Movement3DEvent & event) {

  if ( event.object == owner) {
    std::cout << "Movement detected for " << owner->getName() << std::endl;

    if ( onMovementCallback ) {
      onMovementCallback(owner, event.action);
    }
  }
}
