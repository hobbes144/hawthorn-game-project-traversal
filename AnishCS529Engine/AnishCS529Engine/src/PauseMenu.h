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

	void setInputSystem(Input* ip);
	void setState(bool state);
	bool gameIsPaused();
	bool isQuit();
	bool isStart();
	void setStart(bool val);
	void run();
	void mainPauseMenu();
	void howToPlay();
	void settings();
	void quitMenu();

private:
	enum MenuType {
		MainPauseMenu,
		HowToPlay,
		Settings,
		Quit
	};

	PauseMenu() = default;
	bool isPaused = false;
	bool quit = false;
	bool toStart = false;
	Input* input;
	MenuType menuType = MainPauseMenu;
};

#endif