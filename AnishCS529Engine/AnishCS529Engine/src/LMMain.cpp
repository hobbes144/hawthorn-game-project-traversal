#include "precompiled.h"

#include <windows.h>

#include "LevelManager.h"

extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main() {

    LevelManager levelManager;

    levelManager.SystemInitalization();
    levelManager.MeshMatInitializations();

    //Main Loop
    while (!levelManager.GameComplete()) {
        levelManager.RunLevels();
    }

    levelManager.ShutdownLevels();

    return 0;
}
