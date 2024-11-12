#include "Input.h"

Input::Input(GameWindow& window) : pWindow(window),  keyStates{} {
    for (size_t i = 32; i <= 57; ++i)
        registerKey(i);
    
    for (size_t i = 65; i <= 90; ++i)
        registerKey(i);

    registerKey(256); // ESCAPE

    for (size_t i = 320; i <= 348; ++i)
        registerKey(i);
}

void Input::registerKey(int key) {
    if (keyStates.find(key) == keyStates.end()) {
        keyStates[key] = KeyState();
    }
}

bool Input::isKeyPressed(int key) {
    if (keyStates[key].pressed) {
        keyStates[key].pressed = false; // Reset after checking
        return true;
    }
    return false;
}

bool Input::isKeyReleased(int key) {
    if (keyStates[key].released) {
        keyStates[key].released = false; // Reset after checking
        return true;
    }
    return false;
}

bool Input::isKeyHeld(int key) {
    return keyStates[key].held;
}

void Input::update() {
    //std::cout << static_cast<int>(std::numeric_limits<uint8_t>::max());
    for (std::unordered_map<int, KeyState>::iterator it = keyStates.begin(); it != keyStates.end(); ++it) {
        it->second.pressed = false;
        it->second.released = false;

        int glfwState = glfwGetKey(pWindow.getNativeWindow(), it->first);
        if (glfwState == GLFW_PRESS) {
            if (!it->second.held) {
                it->second.pressed = true;
                it->second.held = true;
            }
        }
        else if (glfwState == GLFW_RELEASE) {
            if (it->second.held) {
                it->second.released = true;
                it->second.held = false;
            }
        }
    }
}