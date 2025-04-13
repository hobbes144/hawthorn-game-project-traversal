#include "precompiled.h"

#include "LevelManager.h"

extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

#ifndef _DEBUG

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#endif

int main()
{

    LevelManager::Instance().SystemInitalization();
    LevelManager::Instance().MeshMatInitializations();

    LevelManager::Instance().DisplayLogos();

    //Main Loop
    while (!LevelManager::Instance().GameComplete()) {
        LevelManager::Instance().RunLevels();
    }
    LevelManager::Instance().ShutdownLevels();

    return 0;
}
