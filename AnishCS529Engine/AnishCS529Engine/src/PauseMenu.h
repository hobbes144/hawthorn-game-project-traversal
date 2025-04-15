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
};

#endif