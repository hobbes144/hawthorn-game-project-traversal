#include "GameWindow.h"
#include "Renderer.h"
#include "FramerateController.h"
#include "Input.h"
#include "SceneGraph.h"
#include "Camera.h"

int main() {
  const std::string GameTitle = "SphereJump";

  /* Game Window setup */
  GameWindow* mainWindow = new GameWindow;
  mainWindow->setTitle(GameTitle)->setHeight(1280)->setWidth(720);
  mainWindow->initialize();

  /* Renderer setup */
  Renderer* mainRenderer = new Renderer;
  mainRenderer->setGameWindow(mainWindow);
  mainRenderer->initialize();
  mainRenderer->setClearColor(0.5, 0.5, 0.5, 1.0)->setIs3D(true);

  mainWindow->setVsync(true);

  /* Input setup */
  Input* mainInput = new Input;
  std::vector<Key> keysToMonitor = { KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE };
  mainInput->setGameWindow(mainWindow);

  FFramerateController* mainFramerateController = FFramerateController::getController();
  
  SceneGraph mainSceneGraph;

  std::shared_ptr<Camera> camera = std::make_shared<Camera>("mainCamera");
  mainSceneGraph.addNode(camera);

  camera->update(0.0f);
  std::cout << camera->getViewMatrix();

  mainInput->shutdown();
  mainRenderer->shutdown();
  mainWindow->shutdown();
}
