#pragma once
#include "GameWindow.h"

using Key = unsigned int;           // 4 bytes

// move WSAD and space              // 4 * 6 = 24 bytes
constexpr Key k_W       = 87;       
constexpr Key k_S       = 83;
constexpr Key k_A       = 65;
constexpr Key k_D       = 68;
constexpr Key k_SPACE   = 32;
constexpr Key K_ESCAPE  = 256;

// main numbers                     // 4 * 10 = 40 bytes
constexpr Key K_0       = 48;
constexpr Key K_1       = 49;
constexpr Key K_2       = 50;
constexpr Key K_3       = 51;
constexpr Key K_4       = 52;
constexpr Key K_5       = 53;
constexpr Key K_6       = 54;
constexpr Key K_7       = 55;
constexpr Key K_8       = 56;
constexpr Key K_9       = 57;

// numpad numbers                   // 4 * 10 = 40 bytes
constexpr Key NUMPAD_0  = 320;
constexpr Key NUMPAD_1  = 321;
constexpr Key NUMPAD_2  = 322;
constexpr Key NUMPAD_3  = 323;
constexpr Key NUMPAD_4  = 324;
constexpr Key NUMPAD_5  = 325;
constexpr Key NUMPAD_6  = 326;
constexpr Key NUMPAD_7  = 327;
constexpr Key NUMPAD_8  = 328;
constexpr Key NUMPAD_9  = 329;

// arrows                           // 4 * 4 = 16 bytes
constexpr Key A_RIGHT     = 262;
constexpr Key A_LEFT      = 263;
constexpr Key A_DOWN      = 264;
constexpr Key A_UP        = 265;

// 30 bytes for all keys = 240 bits

// KeyState struct to track key states
struct KeyState {                   // 3 * 1 = 3 bytes
    bool pressed = false;
    bool released = false;
    bool held = false;
}; 

class Input
{
public:

    Input(GameWindow& window);

    bool isKeyPressed(int key);
    bool isKeyReleased(int key);
    bool isKeyHeld(int key); 

    void update();

private:

    GameWindow& pWindow;
    std::unordered_map<int, KeyState> keyStates; // 30

    void registerKey(int key);

};