#ifndef GAMEPAD_H
#define GAMEPAD_H

#pragma once

#include "Xinput/Xinput.h"
#include <minwinbase.h>
#include <Windows.h>
#include <winerror.h>

struct GPKeyState {
	bool currentState = false;
	bool prevState = false;
};

class GamePad {
private:
	int cId;
	XINPUT_STATE state;

	float deadzoneX;
	float deadzoneY;
	
	float gpLXSensitivity;
	float gpLYSensitivity;
	float gpRXSensitivity;
	float gpRYSensitivity;

	void registerKey(WORD);

public:
	GamePad() : deadzoneX(0.1f), deadzoneY(0.1f),
		gpLXSensitivity(2.0f), gpLYSensitivity(2.0f),
		gpRXSensitivity(2.0f), gpRYSensitivity(2.0f) {
	}
	GamePad(float dzX, float dzY) : deadzoneX(dzX), deadzoneY(dzY) {}

	float leftStickX;
	float leftStickY;
	float rightStickX;
	float rightStickY;

	float leftTrigger;
	float rightTrigger;
	std::unordered_map<WORD, GPKeyState> keyStates;

	void initialize();
	bool update();
	void shutdown();

	int  GetPort();
	XINPUT_GAMEPAD* GetState();
	bool CheckConnection();
	bool isPressed(WORD);
	bool isHeld(WORD);
	bool isReleased(WORD);

	void setLXSensivity(float val);
	void setLYSensivity(float val);
	void setRXSensivity(float val);
	void setRYSensivity(float val);
	void setDeadzoneX(float val);
	void setDeadzoneY(float val);

	float getLXSensitivity();
	float getLYSensitivity();
	float getRXSensitivity();
	float getRYSensitivity();
};

#endif
