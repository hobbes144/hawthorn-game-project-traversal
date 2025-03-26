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
        Sliding,
        Grounded
    };

    enum Action {
        MoveForward,
        MoveLeft,
        MoveRight,
        MoveBackward,
        Sprint,
        Jump,
        Slide,
        Debug
    };

    struct AnchorInfo {
      char direction = '0';
      std::shared_ptr<GameObject> object = nullptr;
      Vector3 normal = Vector3();

      void Reset() {
        this->direction = '0';
        this->object = nullptr;
        this->normal = Vector3();
      }
    };

    FirstPersonControllerComponent() : playerState(Free), isGrounded(false),
      anchorInfo(AnchorInfo()),
        input(nullptr), physicsBody(nullptr), body(nullptr), camera(nullptr),
        walkForce(10), maxWalkSpeed(10.0f),
        runForceMultiplier(2.0f), maxRunSpeed(2 * maxWalkSpeed),
        jumpSpeed(55), airDrag(0.1f), anchoredDrag(0.6f),
        mouseXSensitivity(0.1f), mouseYSensitivity(0.1f), pitchLimit(80),
        coyoteTime(0.1f), jumpBufferTime(0.2f), jumpCooldown(0.2f),
        slideForce(100), slideCoolDown(0.75f), slideEffectTime(0.5f),
        slideBufferTime(0.2f),
        wallRunSpeed(30), wallJumpForce(40), wallrunCooldown(0.2f),
        sceneRoot(nullptr)
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
    std::shared_ptr<FirstPersonControllerComponent>
      setCameraRotation(Vector3 rotation);
    std::shared_ptr<FirstPersonControllerComponent>
      setSceneRoot(std::shared_ptr<GameObject> root);

    //Mapping the Actions to the Keys
    std::shared_ptr<FirstPersonControllerComponent>
        setActionKey(Action _action, Key _key);

    //Accessors
    bool getIsGrounded();
    std::shared_ptr<GameObject> getRunningWall();

private:
    //Utility Functions
    void SwitchState(PlayerState originalState, PlayerState newState);
    void FreeToGrounded();
    void FreeToSliding();
    void FreeToWallRunning();
    void GroundedToFree();
    void GroundedToSliding();
    void WallRunningToFree();
    void WallRunningToGrounded();
    void SlidingToGrounded();
    void SlidingToFree();

    void GroundedJump();
    void SlidingJump();
    void WallrunningJump();

    bool passedCoyoteTime();
    bool JumpBuffered();
    bool CanJump();
    bool SlideBuffered();
    bool CanSlide();
    bool SlidingTimedOut();

    void UpdateAnchorInfo();

    //PlayerState
    PlayerState playerState;
    AnchorInfo anchorInfo;
    bool isGrounded;
    std::shared_ptr<GameObject> anchorSurface;

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
    float runForceMultiplier;
    float maxRunSpeed;
    float jumpSpeed;
    float anchoredDrag;
    float airDrag;

    //Player Mouse Members
    float mouseXSensitivity;
    float mouseYSensitivity;
    float pitchLimit;
    float yawRotation = 0.0f;
    float pitchRotation = 0.0;

    //Jumping Members
    float coyoteTime;
    float unanchoredTime = 0.0f;
    float jumpBufferTime;
    float sinceLastJumpPressedTime = 0.0f;
    float jumpCooldown;
    float sinceLastJumpTime = 0.0f;
    //Sliding Members
    float slideForce;
    Vector3 slideVector = Vector3();
    float slideBufferTime;
    float slideCoolDown;
    float slideEffectTime;
    float sinceLastSlidePressedTime = 0.0f;
    float sinceLastSlideTime = 0.0f;
    //WallRunning Members
    std::shared_ptr<GameObject> runningWall;
    bool isLeftWall = false;
    bool isRightWall = false;
    float wallRunSpeed;
    float wallJumpForce;
    Vector3 wallNormal = Vector3();
    bool isWallRunning = false;
    float wallrunCooldown;
    float wallrunCooldownTimer = wallrunCooldown + 1;
    bool hasSlidSinceAnchored = false;

    std::shared_ptr<GameObject> sceneRoot;

    //Time Ability Members

    //Debugging
    void debugCheck();
};