#include "precompiled.h"

#include <windows.h>

#include "LevelManager.h"

extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main() {

    LevelManager::Instance().SystemInitalization();
    LevelManager::Instance().MeshMatInitializations();

    //Main Loop
    while (!LevelManager::Instance().GameComplete()) {
        
    }
    LevelManager::Instance().RunLevels();
    LevelManager::Instance().ShutdownLevels();

    return 0;
}
