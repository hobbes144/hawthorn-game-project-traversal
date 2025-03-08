/*!****************************************************************************
 * \file   FirstPersonControllerComponent.h
 * \author Nicholas Shaw (nick_shaw@me.com)
 * \par    **DigiPen Email**
 *    nick.shaw@digipen.edu
 * \par    **Course**
 *    GAM541
 * \date   03-07-2025
 * \brief  This is the first person controller componet
 * Responsible for all player actions
 * 
 *****************************************************************************/

#pragma once

#include <cassert>
#include <functional>

#include "Component.h"
#include "Camera.h"
#include "Input.h"
#include "GameObject.h"
#include "PhysicsBody.h"

class FirstPersonControllerComponent
    : public Component, public std::enable_shared_from_this<FirstPersonControllerComponent> {

public:

    enum Action {
        MoveForward,
        MoveLeft,
        MoveRight,
        MoveBackward,
        Jump,
        Slide
    };

    FirstPersonControllerComponent() : walkSpeed(5.0f) {}
    ~FirstPersonControllerComponent() = default;

    void initialize();
    void update(float deltaTime);
    void shutdown();

    std::shared_ptr<FirstPersonControllerComponent> 
        setInputSystem(Input* _inputSystem);
    std::shared_ptr<FirstPersonControllerComponent>
        setPhysicsBody(PhysicsBody* _physicsBody);
    std::shared_ptr<FirstPersonControllerComponent>
        setHead(GameObject* _head);
    std::shared_ptr<FirstPersonControllerComponent>
        setCamera(Camera* _camera);
    std::shared_ptr<FirstPersonControllerComponent>
        setActionKey(Action _action, Key);


private:
    //Sytem Compenet Members
    Input* input;
    PhysicsBody* physicsBody;
    GameObject* head;
    Camera* camera;
    std::unordered_map<Action, Key> ActionKey;

    //PlayerMovement Members
    float walkSpeed;

};