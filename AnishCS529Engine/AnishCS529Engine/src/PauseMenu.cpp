#include "precompiled.h"
#include "PauseMenu.h"

void PauseMenu::setState(bool state) {
	activate = state;
	return;
}

bool PauseMenu::isPaused() {
	return activate;
}

void PauseMenu::run() {
    // Optionally center the pause menu.
    ImVec2 windowSize(300, 300);
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 windowPos((io.DisplaySize.x - windowSize.x) * 0.5f, (io.DisplaySize.y - windowSize.y) * 0.5f);
    ImGui::SetNextWindowPos(windowPos);
    ImGui::SetNextWindowSize(windowSize);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

    ImGui::Text("Game Paused");
}
