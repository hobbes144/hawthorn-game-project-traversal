#include "precompiled.h"
#include "PauseMenu.h"

void PauseMenu::setInputSystem(Input* ip) {
	input = ip;
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
	static int selected = 0;
	const char* items[] = { "Play", "Options", "Exit" };
	int itemCount = IM_ARRAYSIZE(items);

	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Get the display size
	ImVec2 displaySize = ImGui::GetIO().DisplaySize;

	// Set next window to cover the entire screen
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(displaySize);

	// Make it fullscreen, without decorations or inputs leaking through
	ImGui::Begin("Test Menu", nullptr,
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoBringToFrontOnFocus);

	// Optional: dim the background
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawList->AddRectFilled(ImVec2(0, 0), displaySize, IM_COL32(0, 0, 0, 128));

	// Center the menu
	float windowWidth = ImGui::GetWindowSize().x;
	float buttonWidth = 200.0f;
	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);

	if (ImGui::IsWindowFocused()) {
		if (ImGui::IsKeyPressed(ImGuiKey_UpArrow)) {
			selected = (selected - 1 + itemCount) % itemCount;
		}
		if (ImGui::IsKeyPressed(ImGuiKey_DownArrow)) {
			selected = (selected + 1) % itemCount;
		}
		if (ImGui::IsKeyPressed(ImGuiKey_Enter)) {
			ImGui::Text("You selected: %s", items[selected]);
		}
	}

	for (int i = 0; i < itemCount; ++i) {
		ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
		if (i == selected) {
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.5f, 1.0f, 1.0f));
		}
		if (ImGui::Button(items[i], ImVec2(200, 40))) {
			selected = i;
		}
		if (i == selected) {
			ImGui::PopStyleColor();
		}
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return;
}

void PauseMenu::mainPauseMenu() {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable gamepad controls

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Get the display size
	ImVec2 displaySize = ImGui::GetIO().DisplaySize;

	// Set next window to cover the entire screen
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(displaySize);

	// Make it fullscreen, without decorations or inputs leaking through
	ImGui::Begin("Pause Menu", nullptr,
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoBringToFrontOnFocus);

	// Optional: dim the background
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawList->AddRectFilled(ImVec2(0, 0), displaySize, IM_COL32(0, 0, 0, 128));

	// Center the menu
	ImVec2 center = ImVec2(displaySize.x / 2, displaySize.y / 2);
	ImGui::SetCursorPos(ImVec2(center.x - 100, center.y - 50)); // Adjust as needed

	float windowWidth = ImGui::GetWindowSize().x;
	float textWidth = ImGui::CalcTextSize("Game Paused").x;
	ImGui::Text("Game Paused");

	float buttonWidth = 200.0f;
	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);

	if (ImGui::Button("Resume", ImVec2(buttonWidth, 40))) {
		isPaused = false;
		input->controlMouse(true);
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Back to Start", ImVec2(buttonWidth, 40))) {
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

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Test", ImVec2(buttonWidth, 40))) {
		menuType = Test;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return;
}

void PauseMenu::howToPlay() {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable gamepad controls

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Get the display size
	ImVec2 displaySize = ImGui::GetIO().DisplaySize;

	// Set next window to cover the entire screen
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(displaySize);

	// Make it fullscreen, without decorations or inputs leaking through
	ImGui::Begin("How To Play", nullptr,
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoBringToFrontOnFocus);

	// Optional: dim the background
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawList->AddRectFilled(ImVec2(0, 0), displaySize, IM_COL32(0, 0, 0, 128));

	// Center the menu
	ImVec2 center = ImVec2(displaySize.x / 2, displaySize.y / 2);
	ImGui::SetCursorPos(ImVec2(center.x - 100, center.y - 50)); // Adjust as needed

	float windowWidth = ImGui::GetWindowSize().x;
	float textWidth = ImGui::CalcTextSize("How To Play").x;
	ImGui::Text("How To Play");

	float buttonWidth = 200.0f;
	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Go Back", ImVec2(buttonWidth, 40))) {
		menuType = MainPauseMenu;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return;
}

void PauseMenu::settings() {
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable gamepad controls

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Get the display size
	ImVec2 displaySize = ImGui::GetIO().DisplaySize;

	// Set next window to cover the entire screen
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(displaySize);

	// Make it fullscreen, without decorations or inputs leaking through
	ImGui::Begin("Settings", nullptr,
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoBringToFrontOnFocus);

	// Optional: dim the background
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawList->AddRectFilled(ImVec2(0, 0), displaySize, IM_COL32(0, 0, 0, 128));

	// Center the menu
	ImVec2 center = ImVec2(displaySize.x / 2, displaySize.y / 2);
	ImGui::SetCursorPos(ImVec2(center.x - 100, center.y - 50)); // Adjust as needed

	float windowWidth = ImGui::GetWindowSize().x;
	float textWidth = ImGui::CalcTextSize("Settings").x;
	ImGui::Text("Settings");

	float buttonWidth = 200.0f;

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Music Volume-", ImVec2(buttonWidth, 40))) {
		if (musicVolume > 0.01f) {
			musicVolume -= 0.05f;
			AudioManager::instance().setVolume("music", musicVolume);
		}
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Music Volume+", ImVec2(buttonWidth, 40))) {
		if (musicVolume < 1.0f) {
			musicVolume += 0.05f;
			AudioManager::instance().setVolume("music", musicVolume);
		}
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("SFX Volume-", ImVec2(buttonWidth, 40))) {
		if (SFXVolume > 0.01f) {
			SFXVolume -= 0.05f;
		}
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("SFX Volume+", ImVec2(buttonWidth, 40))) {
		if (SFXVolume < 1.0f) {
			SFXVolume += 0.05f;
		}
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Go Back", ImVec2(buttonWidth, 40))) {
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

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Get the display size
	ImVec2 displaySize = ImGui::GetIO().DisplaySize;

	// Set next window to cover the entire screen
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(displaySize);

	// Make it fullscreen, without decorations or inputs leaking through
	ImGui::Begin("Quit Menu", nullptr,
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoBringToFrontOnFocus);

	// Optional: dim the background
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawList->AddRectFilled(ImVec2(0, 0), displaySize, IM_COL32(0, 0, 0, 128));

	// Center the menu
	ImVec2 center = ImVec2(displaySize.x / 2, displaySize.y / 2);
	ImGui::SetCursorPos(ImVec2(center.x - 100, center.y - 50)); // Adjust as needed

	float windowWidth = ImGui::GetWindowSize().x;
	float textWidth = ImGui::CalcTextSize("Are you sure you want to quit?").x;
	ImGui::Text("Are you sure you want to quit?");

	float buttonWidth = 200.0f;

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Go Back", ImVec2(buttonWidth, 40))) {
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
		isPaused = false;
		input->controlMouse(true);
	}
}
