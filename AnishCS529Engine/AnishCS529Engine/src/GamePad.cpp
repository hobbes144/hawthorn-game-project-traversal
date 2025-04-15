#include "precompiled.h"
#include "GamePad.h"

// Returns false if the controller has been disconnected
bool GamePad::update() {
	if (cId == -1)
		CheckConnection();

	if (cId != -1) {
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (XInputGetState(cId, &state) != ERROR_SUCCESS) {
			cId = -1;
			return false;
		}

		float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
		float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);

		leftStickX = (abs(normLX) < deadzoneX ? 0 : (abs(normLX) - deadzoneX) * (normLX / abs(normLX)));
		leftStickY = (abs(normLY) < deadzoneY ? 0 : (abs(normLY) - deadzoneY) * (normLY / abs(normLY)));

		if (deadzoneX > 0) leftStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) leftStickY *= 1 / (1 - deadzoneY);

		float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
		float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

		rightStickX = (abs(normRX) < deadzoneX ? 0 : (abs(normRX) - deadzoneX) * (normRX / abs(normRX)));
		rightStickY = (abs(normRY) < deadzoneY ? 0 : (abs(normRY) - deadzoneY) * (normRY / abs(normRY)));

		if (deadzoneX > 0) rightStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) rightStickY *= 1 / (1 - deadzoneY);

		leftTrigger = (float)state.Gamepad.bLeftTrigger / 255;
		rightTrigger = (float)state.Gamepad.bRightTrigger / 255;

		return true;
	}
	return false;
}

bool GamePad::isPressed(WORD button) {
	return (state.Gamepad.wButtons & button) != 0;
}

int GamePad::GetPort() {
	return cId + 1;
}

XINPUT_GAMEPAD* GamePad::GetState() {
	return &state.Gamepad;
}

bool GamePad::CheckConnection() {
	int controllerId = -1;

	for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &state) == ERROR_SUCCESS)
			controllerId = i;
	}

	cId = controllerId;

	return controllerId != -1;
}

/*!****************************************************************************
 * \brief If key was released while previously pressed
 *
 * \param k Key to be checked.
 * \return \b bool True if released in this cycle.
 *****************************************************************************/
bool GamePad::isReleased(WORD button) {
	if (keyStates[button].currentState == false &&
	  keyStates[button].prevState == true)
		return true;
	return false;
}

/*!****************************************************************************
 * \brief If key is held in pressed state
 *
 * \param k Key to be checked.
 * \return \b bool True if held.
 *****************************************************************************/
bool GamePad::isHeld(WORD button) {
	if (keyStates[button].currentState == true &&
	  keyStates[button].prevState == true)
		return true;
	return false;
}

void GamePad::registerKey(WORD button) {
	if (keyStates.find(button) == keyStates.end())
		keyStates[button] = KeyState();
}

void GamePad::registerKey() {
	registerKey(XINPUT_GAMEPAD_A);
	registerKey(XINPUT_GAMEPAD_B);
	registerKey(XINPUT_GAMEPAD_X);
	registerKey(XINPUT_GAMEPAD_Y);
	registerKey(XINPUT_GAMEPAD_DPAD_DOWN);
	registerKey(XINPUT_GAMEPAD_DPAD_LEFT);
	registerKey(XINPUT_GAMEPAD_DPAD_RIGHT);
	registerKey(XINPUT_GAMEPAD_DPAD_UP);
	registerKey(XINPUT_GAMEPAD_LEFT_SHOULDER);
	registerKey(XINPUT_GAMEPAD_LEFT_THUMB);
	registerKey(XINPUT_GAMEPAD_RIGHT_SHOULDER);
	registerKey(XINPUT_GAMEPAD_RIGHT_THUMB);
	registerKey(XINPUT_GAMEPAD_START);
	registerKey(XINPUT_GAMEPAD_BACK);
}

void GamePad::initialize() {
	registerKey();
}
