#include "precompiled.h"
#include "PauseMenu.h"

void PauseMenu::setState(bool state) {
	isPaused = state;
	return;
}

bool PauseMenu::gameIsPaused() {
	return isPaused;
}

void PauseMenu::run() {
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;

    // Set next window to cover the entire screen
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(displaySize);

    // Optional: dim the background
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddRectFilled(ImVec2(0, 0), displaySize, IM_COL32(0, 0, 0, 128));

    // Center the menu
    ImVec2 center = ImVec2(displaySize.x / 2, displaySize.y / 2);

    ImGui::Text("Paused");
    
    if (ImGui::Button("Resume", ImVec2(200, 200))) {
        isPaused = false;
    }
}
