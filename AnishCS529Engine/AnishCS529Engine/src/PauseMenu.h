/*!****************************************************************************
 * \file   PauseMenu.h
 * \author Wang Daoming (KeitherJinn@outlook.com)
 * \par    **DigiPen Email**
 *    daoming.wang@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-14-2024
 * \brief  File conatining the custom Vector3 implementation for use with
 * OpenGL functions and other game logic.
 * 
 *****************************************************************************/
#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#pragma once

#include "GameObject.h"
#include "FirstPersonControllerComponent.h"
#include "GamePad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Input.h"
#include "stb/stb_image.h"
#include <variant>

class PauseMenu {
public:
	static PauseMenu& Instance() {
		static PauseMenu instance;
		return instance;
	}
	PauseMenu(const PauseMenu
		&) = delete;
	PauseMenu& operator=(const PauseMenu&) = delete;

	void resetTimer();
	void setInputSystem(Input* ip);
	void setFramerateController(FFramerateController* _frc);
	void setGamePad(GamePad* _gp);
	void setPlayer(std::shared_ptr<GameObject> pl);
	void setState(bool state);
	bool gameIsPaused();
	bool isQuit();
	bool isStart();
	void setStart(bool val);
	void run();
	float getMusicVolume();
	float getSFXVolume();

private:
	enum MenuType {
		MainPauseMenu,
		HowToPlay,
		Settings,
		Quit,
		Test
	};

	enum Action {
		MoveForward,
		MoveBackward,
		MoveLeft,
		MoveRight,
		Sprint,
		Slide,
		NUM_ACTIONS
	};
	const char* ActionNames[NUM_ACTIONS] = {
		"Move Forward", "Move Backward", "Move Left", "Move Right", "Sprint", "Slide"
	};

	using BindInput = std::variant<Key, int>; 

	// For each action, store the bind
	BindInput actionBinds[NUM_ACTIONS] = {
		KEY_W, KEY_S, KEY_A, KEY_D, KEY_LEFT_SHIFT, KEY_LEFT_CONTROL
	};

	// For remapping state
	int remapActionIndex = -1; // -1:not remapping, [0,NUM_ACTIONS)
	bool waitingForKey = false;

	PauseMenu() = default;

	void mainPauseMenu();
	void howToPlay();
	void settings();
	void quitMenu();
	void testMenu();

	bool isPaused = false;
	bool quit = false;
	bool toStart = false;

	float musicVolume = 0.15f;
	float SFXVolume = 1.0f;
	float mouseXSensivity = 0.1f;
	float mouseYSensivity = 0.1f;

	float gpLXSensitivity = 2.0f;
	float gpLYSensitivity = 2.0f;
	float gpRXSensitivity = 2.0f;
	float gpRYSensitivity = 2.0f;

	float time = 0.0f;
	Input* input;
	MenuType menuType = MainPauseMenu;
	FFramerateController* frc;
	GamePad* gp;
	std::shared_ptr<GameObject> player;

	static std::string GetBindName(const BindInput& bind)
	{
		if (std::holds_alternative<Key>(bind)) {
			Key key = std::get<Key>(bind);
			switch (key) {
			case KEY_W: return "W";
			case KEY_A: return "A";
			case KEY_S: return "S";
			case KEY_D: return "D";
			case KEY_LEFT_SHIFT: return "Shift";
			case KEY_LEFT_CONTROL: return "Ctrl";
			case KEY_SPACE: return "Space";
			default: return "Key " + std::to_string((int)key);
			}
		}
		else {
			int button = std::get<int>(bind);
			switch (button) {
			case GLFW_MOUSE_BUTTON_LEFT: return "Mouse Left";
			case GLFW_MOUSE_BUTTON_RIGHT: return "Mouse Right";
			default: return "Mouse " + std::to_string(button);
			}
		}
	}
};

#endif