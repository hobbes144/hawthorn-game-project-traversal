#include "precompiled.h"
#include "PauseMenu.h"

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

void PauseMenu::run() {
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
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoBringToFrontOnFocus);

	// Optional: dim the background
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawList->AddRectFilled(ImVec2(0, 0), displaySize, IM_COL32(0, 0, 0, 128));

	// Center the menu
	ImVec2 center = ImVec2(displaySize.x / 2, displaySize.y / 2);
	ImGui::SetCursorPos(ImVec2(center.x - 100, center.y - 50)); // Adjust as needed

	float windowWidth = ImGui::GetWindowSize().x;
	float textWidth = ImGui::CalcTextSize("Paused").x;
	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text("Game Paused");

	float buttonWidth = 200.0f;
	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	
	if (ImGui::Button("Resume", ImVec2(buttonWidth, 40))) {
		isPaused = false;
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Back to Start", ImVec2(buttonWidth, 40))) {
		toStart = true;
	}

	ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
	if (ImGui::Button("Quit", ImVec2(buttonWidth, 40))) {
		quit = true;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
