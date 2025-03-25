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

public:
	GamePad() : deadzoneX(0.02f), deadzoneY(0.02f) {}
	GamePad(float dzX, float dzY) : deadzoneX(dzX), deadzoneY(dzY) {}

	float leftStickX;
	float leftStickY;
	float rightStickX;
	float rightStickY;
	float leftTrigger;
	float rightTrigger;

	int  GetPort();
	XINPUT_GAMEPAD* GetState();
	bool CheckConnection();
	bool Refresh();
	bool IsPressed(WORD);
};

#endif
