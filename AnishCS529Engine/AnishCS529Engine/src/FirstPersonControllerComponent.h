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

/*!****************************************************************************
 * \brief This is the First Person Contorller responsible for player movement,
 * camera mouse movement, Jumping, Wall Running sliding, and Time Abilities
 * 
 * ## Pre - initialization calls :
 *
 * Need to initalizethe Input System, PhysicsBody, Body of the player, and a 
 * pointer to the camera
 * 
 * std::shared_ptr<FirstPersonControllerComponent>
 *      setInputSystem(Input* _inputSystem) { input = _inputSystem; }
 *  std::shared_ptr<FirstPersonControllerComponent>
 *      setPhysicsBody(PhysicsBody* _physicsBody) { physicsBody = _physicsBody; }
 *  std::shared_ptr<FirstPersonControllerComponent>
 *      setBody(GameObject* _body) { body = _body; }
 *  std::shared_ptr<FirstPersonControllerComponent>
 *      setCamera(Camera* _camera) { camera = _camera; }
 * 
 *****************************************************************************/
class FirstPersonControllerComponent
    : public Component, public std::enable_shared_from_this<FirstPersonControllerComponent> {

public:

    enum PlayerState {
        Free,
        WallRunning,
        Sliding
    };

    enum Action {
        MoveForward,
        MoveLeft,
        MoveRight,
        MoveBackward,
        Sprint,
        Jump,
        Slide
    };

    FirstPersonControllerComponent() : playerState(Free), isGrounded(false),
        input(nullptr), physicsBody(nullptr), body(nullptr), camera(nullptr),
        walkForce(10.0f), maxWalkSpeed(5.0f),
        runForce(2 * walkForce), maxRunSpeed(2 * maxWalkSpeed),
        jumpForce(1000),
        mouseSensitivity(0.001f), pitchLimit(80),
        coyoteTime(0.1f), jumpBufferTime(0.2f),
        slideCoolDown(5.0f)
        {}
    ~FirstPersonControllerComponent() = default;

    void initialize();
    void update(float deltaTime);
    void shutdown();

    //Setting up the componenet
    std::shared_ptr<FirstPersonControllerComponent>
        setInputSystem(Input* _inputSystem);
    std::shared_ptr<FirstPersonControllerComponent>
        setPhysicsBody(PhysicsBody* _physicsBody);
    std::shared_ptr<FirstPersonControllerComponent>
        setBody(GameObject* _body);
    std::shared_ptr<FirstPersonControllerComponent>
        setCamera(Camera* _camera);

    //Mapping the Actions to the Keys
    std::shared_ptr<FirstPersonControllerComponent>
        setActionKey(Action _action, Key _key);


private:
    //PlayerState
    PlayerState playerState;
    bool isGrounded;

    //Sytem Compenet Members
    Input* input;
    PhysicsBody* physicsBody;

    //GameObject Assembly
    GameObject* body;
    Camera* camera;

    //Action Key Mapping
    std::unordered_map<Action, Key> ActionKey;

    //PlayerMovement Members
    float walkForce;
    float maxWalkSpeed;
    float runForce;
    float maxRunSpeed;
    float jumpForce;

    //Player Mouse Members
    float mouseSensitivity;
    float pitchLimit;

    //Parkour Members
    float coyoteTime;
    float lastTimeGrounded = coyoteTime+1;
    float jumpBufferTime;
    float lastTimeJumpPressed = jumpBufferTime + 1;
    float slideCoolDown;
    float slideCoolDownTimer = slideCoolDown + 1;

    //Time Ability Members

};