#include "precompiled.h"
#include "PauseMenu.h"

void PauseMenu::resetTimer() {
	time = 0.0f;
	return;
}

void PauseMenu::setInputSystem(Input* ip) {
	input = ip;
	return;
}

void PauseMenu::setFramerateController(FFramerateController* _frc) {
	frc = _frc;
	return;
}

void PauseMenu::setPlayer(std::shared_ptr<GameObject> pl) {
	player = pl;
	return;
}

void PauseMenu::setGamePad(GamePad* _gp) {
	gp = _gp;
	return;
}

void PauseMenu::setState(bool state) {
	isPaused = state;
	return;
}

bool PauseMenu::gameIsPaused() {
	return isPaused;
}

bool PauseMenu::isQuit() {
	return quit;
}

bool PauseMenu::isStart() {
	return toStart;
}

void PauseMenu::setStart(bool val) {
	toStart = val;
	return;
}

float PauseMenu::getMusicVolume() {
	return musicVolume;
}

float PauseMenu::getSFXVolume() {
	return SFXVolume;
}

void PauseMenu::testMenu() {
	//test stuffs
}

/*!****************************************************************************
 * \brief Main Pause menu function, shows the main pause screen
 * 
 *****************************************************************************/
void PauseMenu::mainPauseMenu() {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable gamepad controls
	io.FontGlobalScale = 2.0f;

	if (ImGui::IsKeyDown(KEY_ENTER)) {
		io.KeyMap[ImGuiKey_Space] = KEY_ENTER;
	}

	if (ImGui::IsKeyDown(KEY_SPACE)) {
		io.KeyMap[ImGuiKey_Space] = KEY_SPACE;
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Get the display size
	ImVec2 displaySize = ImGui::GetIO().DisplaySize;

	// Set next window to cover the entire screen
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(displaySize);

	ImGui::Begin("Pause Menu", nullptr,
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoBringToFrontOnFocus);

	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawList->AddRectFilled(ImVec2(0, 0), displaySize, IM_COL32(0, 0, 0, 96));

	// Center the menu
	ImVec2 center = ImVec2(displaySize.x / 2, displaySize.y / 2);
	ImGui::SetCursorPos(ImVec2(center.x - 100, center.y - 200));

	float windowWidth = ImGui::GetWindowSize().x;
	float textWidth = ImGui::CalcTextSize("Game Paused").x;
	ImGui::Text("Game Paused");

	float buttonWidth = 200.0f;
	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);

	if (ImGui::Button("Resume", ImVec2(buttonWidth, 40)) ||
		(ImGui::IsKeyPressed(KEY_ESCAPE) && time >= 0.4f)) {
		resetTimer();
		frc->clearPhysicsTime();
		isPaused = false;
		input->controlMouse(true);
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Back to Start", ImVec2(buttonWidth, 40))) {
		resetTimer();
		frc->clearPhysicsTime();
		isPaused = false;
		toStart = true;
		input->controlMouse(true);
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("How To Play", ImVec2(buttonWidth, 40))) {
		menuType = HowToPlay;
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Settings", ImVec2(buttonWidth, 40))) {
		menuType = Settings;
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Quit", ImVec2(buttonWidth, 40))) {
		menuType = Quit;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return;
}

/*!****************************************************************************
 * \brief How To Play function, shows how to play screen
 * 
 *****************************************************************************/
void PauseMenu::howToPlay() {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable gamepad controls
	io.FontGlobalScale = 2.0f;

	if (ImGui::IsKeyDown(KEY_ENTER)) {
		io.KeyMap[ImGuiKey_Space] = KEY_ENTER;
	}

	if (ImGui::IsKeyDown(KEY_SPACE)) {
		io.KeyMap[ImGuiKey_Space] = KEY_SPACE;
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Get the display size
	ImVec2 displaySize = ImGui::GetIO().DisplaySize;

	// Set next window to cover the entire screen
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(displaySize);

	ImGui::Begin("How To Play", nullptr,
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoBringToFrontOnFocus);

	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawList->AddRectFilled(ImVec2(0, 0), displaySize, IM_COL32(0, 0, 0, 96));

	// Center the menu
	ImVec2 center = ImVec2(displaySize.x / 2, displaySize.y / 2);
	ImGui::SetCursorPos(ImVec2(center.x - 250, center.y - 200));

	float windowWidth = ImGui::GetWindowSize().x;

	ImGui::Text("How To Play:");
	ImGui::SetCursorPosX(center.x - 250);
	ImGui::Text("Move: W-A-S-D/Left Joystick");
	ImGui::SetCursorPosX(center.x - 250);
	ImGui::Text("Jump: Space/A");
	ImGui::SetCursorPosX(center.x - 250);
	ImGui::Text("Sprint: LShift/Press Left joystick");
	ImGui::SetCursorPosX(center.x - 250);
	ImGui::Text("Slide: LCtrl/B");
	ImGui::SetCursorPosX(center.x - 250);
	ImGui::Text("Respawn: R/X");
	ImGui::SetCursorPosX(center.x - 250);
	ImGui::Text("Look around: Mouse/Right joystick");
	ImGui::SetCursorPosX(center.x - 250);
	ImGui::Text("Music on/off: M/Right shoulder");

	float buttonWidth = 200.0f;
	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Go Back", ImVec2(buttonWidth, 40)) ||
		(ImGui::IsKeyPressed(KEY_ESCAPE) && time >= 0.4f)) {
		menuType = MainPauseMenu;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return;
}

/*!****************************************************************************
 * \brief settings function, player can set their preferences
 * 
 *****************************************************************************/
void PauseMenu::settings() {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable gamepad controls
	io.FontGlobalScale = 2.0f;

	if (ImGui::IsKeyDown(KEY_ENTER)) {
		io.KeyMap[ImGuiKey_Space] = KEY_ENTER;
	}

	if (ImGui::IsKeyDown(KEY_SPACE)) {
		io.KeyMap[ImGuiKey_Space] = KEY_SPACE;
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Get the display size
	ImVec2 displaySize = ImGui::GetIO().DisplaySize;

	// Set next window to cover the entire screen
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(displaySize);

	ImGui::Begin("Settings", nullptr,
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoBringToFrontOnFocus);

	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawList->AddRectFilled(ImVec2(0, 0), displaySize, IM_COL32(0, 0, 0, 96));

	ImVec2 center = ImVec2(displaySize.x / 2, displaySize.y / 2);
	ImGui::SetCursorPos(ImVec2(center.x - 70, center.y - 300));

	float windowWidth = ImGui::GetWindowSize().x;
	float textWidth = ImGui::CalcTextSize("Settings").x;
	ImGui::Text("Settings");

	ImGui::Text(" ");

	float buttonWidth = 200.0f;

	ImGui::PushItemWidth(400.0f);

#pragma region Volume

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f - 100.0f);
	ImGui::SliderFloat("Music Volume", &musicVolume, 0.0f, 1.0f);

	if (ImGui::IsKeyPressed(KEY_LEFT) && ImGui::IsItemFocused()) {
		if (musicVolume > 0.01f) {
			musicVolume -= 0.05f;
		}
	}
	if (ImGui::IsKeyPressed(KEY_RIGHT) && ImGui::IsItemFocused()) {
		if (musicVolume < 0.99f) {
			musicVolume += 0.05f;
		}
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f - 100.0f);
	ImGui::SliderFloat("SFX Volume", &SFXVolume, 0.0f, 1.0f);

	if (ImGui::IsKeyPressed(KEY_LEFT) && ImGui::IsItemFocused()) {
		if (SFXVolume > 0.01f) {
			SFXVolume -= 0.05f;
		}
	}
	if (ImGui::IsKeyPressed(KEY_RIGHT) && ImGui::IsItemFocused()) {
		if (SFXVolume < 0.99f) {
			SFXVolume += 0.05f;
		}
	}

#pragma endregion

	ImGui::Text(" ");

#pragma region Mouse

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f - 100.0f);
	ImGui::SliderFloat("MouseX Sensivity", &mouseXSensivity, 0.0f, 0.2f);

	if (ImGui::IsKeyPressed(KEY_LEFT) && ImGui::IsItemFocused()) {
		if (mouseXSensivity > 0.005f) {
			mouseXSensivity -= 0.01f;
		}
	}
	if (ImGui::IsKeyPressed(KEY_RIGHT) && ImGui::IsItemFocused()) {
		if (mouseXSensivity < 0.195f) {
			mouseXSensivity += 0.01f;
		}
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f - 100.0f);
	ImGui::SliderFloat("MouseY Sensivity", &mouseYSensivity, 0.0f, 0.2f);

	if (ImGui::IsKeyPressed(KEY_LEFT) && ImGui::IsItemFocused()) {
		if (mouseYSensivity > 0.005f) {
			mouseYSensivity -= 0.01f;
		}
	}
	if (ImGui::IsKeyPressed(KEY_RIGHT) && ImGui::IsItemFocused()) {
		if (mouseYSensivity < 0.195f) {
			mouseYSensivity += 0.01f;
		}
	}

#pragma endregion

	ImGui::Text(" ");

#pragma region GamePad

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f - 100.0f);
	ImGui::SliderFloat("Left Joystick X Sensivity", &gpLXSensitivity, 0.0f, 6.0f);

	if (ImGui::IsKeyPressed(KEY_LEFT) && ImGui::IsItemFocused()) {
		if (gpLXSensitivity > 0.05f) {
			gpLXSensitivity -= 0.25f;
		}
	}
	if (ImGui::IsKeyPressed(KEY_RIGHT) && ImGui::IsItemFocused()) {
		if (gpLXSensitivity < 5.95f) {
			gpLXSensitivity += 0.25f;
		}
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f - 100.0f);
	ImGui::SliderFloat("Left Joystick Y Sensivity", &gpLYSensitivity, 0.0f, 6.0f);

	if (ImGui::IsKeyPressed(KEY_LEFT) && ImGui::IsItemFocused()) {
		if (gpLYSensitivity > 0.05f) {
			gpLYSensitivity -= 0.25f;
		}
	}
	if (ImGui::IsKeyPressed(KEY_RIGHT) && ImGui::IsItemFocused()) {
		if (gpLYSensitivity < 5.95f) {
			gpLYSensitivity += 0.25f;
		}
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f - 100.0f);
	ImGui::SliderFloat("Right Joystick X Sensivity", &gpRXSensitivity, 0.0f, 6.0f);

	if (ImGui::IsKeyPressed(KEY_LEFT) && ImGui::IsItemFocused()) {
		if (gpRXSensitivity > 0.05f) {
			gpRXSensitivity -= 0.25f;
		}
	}
	if (ImGui::IsKeyPressed(KEY_RIGHT) && ImGui::IsItemFocused()) {
		if (gpRXSensitivity < 5.95f) {
			gpRXSensitivity += 0.25f;
		}
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f - 100.0f);
	ImGui::SliderFloat("Right Joystick Y Sensivity", &gpRYSensitivity, 0.0f, 6.0f);

	if (ImGui::IsKeyPressed(KEY_LEFT) && ImGui::IsItemFocused()) {
		if (gpRYSensitivity > 0.05f) {
			gpRYSensitivity -= 0.25f;
		}
	}
	if (ImGui::IsKeyPressed(KEY_RIGHT) && ImGui::IsItemFocused()) {
		if (gpRYSensitivity < 5.95f) {
			gpRYSensitivity += 0.25f;
		}
	}

#pragma endregion

	ImGui::Text(" ");

	ImGui::PopItemWidth();

	AudioManager::instance().setVolume("music", musicVolume);
	player->findComponent<FirstPersonControllerComponent>()->setMouseXSensivity(mouseXSensivity);
	player->findComponent<FirstPersonControllerComponent>()->setMouseYSensivity(mouseYSensivity);
	gp->setLXSensivity(gpLXSensitivity);
	gp->setLYSensivity(gpLYSensitivity);
	gp->setRXSensivity(gpRXSensitivity);
	gp->setRYSensivity(gpRYSensitivity);

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Go Back", ImVec2(buttonWidth, 40)) ||
		(ImGui::IsKeyPressed(KEY_ESCAPE) && time >= 0.4f)) {
		menuType = MainPauseMenu;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return;
}

void PauseMenu::quitMenu() {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable gamepad controls
	io.FontGlobalScale = 2.0f;

	if (ImGui::IsKeyDown(KEY_ENTER)) {
		io.KeyMap[ImGuiKey_Space] = KEY_ENTER;
	}

	if (ImGui::IsKeyDown(KEY_SPACE)) {
		io.KeyMap[ImGuiKey_Space] = KEY_SPACE;
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Get the display size
	ImVec2 displaySize = ImGui::GetIO().DisplaySize;

	// Set next window to cover the entire screen
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(displaySize);

	ImGui::Begin("Quit Menu", nullptr,
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoBringToFrontOnFocus);

	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawList->AddRectFilled(ImVec2(0, 0), displaySize, IM_COL32(0, 0, 0, 96));

	// Center the menu
	ImVec2 center = ImVec2(displaySize.x / 2, displaySize.y / 2);
	ImGui::SetCursorPos(ImVec2(center.x - 200, center.y - 100));

	float windowWidth = ImGui::GetWindowSize().x;
	float textWidth = ImGui::CalcTextSize("Are you sure you want to quit?").x;
	ImGui::Text("Are you sure you want to quit?");

	float buttonWidth = 200.0f;

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Go Back", ImVec2(buttonWidth, 40)) ||
		(ImGui::IsKeyPressed(KEY_ESCAPE) && time >= 0.4f)) {
		menuType = MainPauseMenu;
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Quit", ImVec2(buttonWidth, 40))) {
		quit = true;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return;
}

void PauseMenu::run() {
	time += (1.0f / 60.0f);

	if (menuType == MainPauseMenu) {
		mainPauseMenu();
	}
	else if (menuType == HowToPlay) {
		howToPlay();
	}
	else if (menuType == Settings) {
		settings();
	}
	else if (menuType == Quit) {
		quitMenu();
	}
	else if (menuType == Test) {
		testMenu();
	}
	else {
		resetTimer();
		frc->clearPhysicsTime();
		isPaused = false;
		input->controlMouse(true);
	}
}
