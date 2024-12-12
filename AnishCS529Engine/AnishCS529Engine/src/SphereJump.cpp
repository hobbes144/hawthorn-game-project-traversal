#include "GameWindow.h"
#include "Renderer.h"
#include "FramerateController.h"
#include "Input.h"

int main() {
  const std::string GameTitle = "SphereJump";

  std::vector<Component*> gameComponents = {};

  /* Game Window setup */
  GameWindow* mainWindow = new GameWindow;
  mainWindow->setTitle(GameTitle)->setHeight(1280)->setHeight(720);
  mainWindow->initialize();

  gameComponents.push_back(mainWindow);

  /* Renderer setup */
  Renderer* mainRenderer = new Renderer;
  mainRenderer->setGameWindow(mainWindow)->setIs3D(true)
    ->setClearColor(0.5, 0.5, 0.5, 1.0);
  mainRenderer->initialize();

  gameComponents.push_back(mainRenderer);

  mainWindow->setVsync(true);

  /* Input setup */
  Input* mainInput = new Input;
  std::vector<Key> keysToMonitor = { KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE };
  mainInput->setGameWindow(mainWindow);

  gameComponents.push_back(mainInput);

}
