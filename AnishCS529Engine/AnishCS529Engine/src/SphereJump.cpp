#include "GameWindow.h"
#include "Renderer.h"
#include "FramerateController.h"
#include "Input.h"
#include "SceneGraph.h"

int main() {
  const std::string GameTitle = "SphereJump";

  /* Game Window setup */
  GameWindow* mainWindow = new GameWindow;
  mainWindow->setTitle(GameTitle)->setHeight(1280)->setHeight(720);
  mainWindow->initialize();

  /* Renderer setup */
  Renderer* mainRenderer = new Renderer;
  mainRenderer->setGameWindow(mainWindow)->setIs3D(true)
    ->setClearColor(0.5, 0.5, 0.5, 1.0);
  mainRenderer->initialize();

  mainWindow->setVsync(true);

  /* Input setup */
  Input* mainInput = new Input;
  std::vector<Key> keysToMonitor = { KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE };
  mainInput->setGameWindow(mainWindow);

  FFramerateController* mainFramerateController = FFramerateController::getController();
  
  SceneGraph mainSceneGraph;

}
