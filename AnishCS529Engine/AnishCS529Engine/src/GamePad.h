#ifndef GAMEPAD_H
#define GAMEPAD_H

#pragma once

#include "Xinput/Xinput.h"
#include <minwinbase.h>
#include <Windows.h>
#include <winerror.h>

class GamePad {
private:
	int cId;
	XINPUT_STATE state;
	float deadzoneX;
	float deadzoneY;
	void registerKey(WORD);
	void registerKey();

public:
	struct KeyState {
		bool currentState = false;
		bool prevState = false;
	};

	GamePad() : deadzoneX(0.02f), deadzoneY(0.02f),
		LXSensitivity(2.0f), LYSensitivity(2.0f),
		RXSensitivity(2.0f), RYSensitivity(2.0f) {}
	GamePad(float dzX, float dzY) : deadzoneX(dzX), deadzoneY(dzY) {}

	float leftStickX;
	float leftStickY;
	float rightStickX;
	float rightStickY;
	float LXSensitivity;
	float LYSensitivity;
	float RXSensitivity;
	float RYSensitivity;
	float leftTrigger;
	float rightTrigger;
	std::unordered_map<WORD, KeyState> keyStates;

	void initialize();
	int  GetPort();
	XINPUT_GAMEPAD* GetState();
	bool CheckConnection();
	bool update();
	bool isPressed(WORD);
	bool isHeld(WORD);
	bool isReleased(WORD);
};

#endif
