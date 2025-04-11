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
#include "Input.h"

class PauseMenu {
public:
	static PauseMenu& Instance() {
		static PauseMenu instance;
		return instance;
	}
	PauseMenu(const PauseMenu
		&) = delete;
	PauseMenu& operator=(const PauseMenu&) = delete;

	void setState(bool state);
	bool isPaused();
	void run();

private:
	PauseMenu() = default;
	bool activate = false;
};

#endif