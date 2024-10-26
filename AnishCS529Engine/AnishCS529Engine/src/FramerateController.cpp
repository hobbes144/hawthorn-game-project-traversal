/*!****************************************************************************
 * \file   FramerateController.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-25-2024
 * 
 *****************************************************************************/
#include "FramerateController.h"


FramerateController::FramerateController() : 
  timeAtProgramStart(glfwGetTime()), 
  timeAtFrameStart(0.0), 
  renderTime(0.0),
  targetFrameTime(1.0 / 60.0), 
  frameCount(0),
  framesSinceLastFPSQuery(0) {}

void FramerateController::setTargetFramerate(const unsigned int framerate) {
  targetFrameTime = 1.0/framerate;
}

void FramerateController::frameStart() {
  timeAtFrameStart = glfwGetTime();
}

void FramerateController::frameEnd() {
  renderTime = glfwGetTime() - timeAtFrameStart;
  frameCount++; framesSinceLastFPSQuery++;
  /*double remainingTime = targetFrameTime - renderTime;
  if (remainingTime > 0) {
    std::this_thread::sleep_for(std::chrono::duration<double>(remainingTime * 0.9));
  }*/
  while ((glfwGetTime() - timeAtFrameStart) < targetFrameTime);
  timeAtFrameEnd = glfwGetTime();
}

double FramerateController::getFPS() {
  double lastQuery = timeOfLastFPSQuery;
  long int numFrames = framesSinceLastFPSQuery;
  timeOfLastFPSQuery = glfwGetTime();
  framesSinceLastFPSQuery = 0;
  return (numFrames / (glfwGetTime() - lastQuery));
}

double FramerateController::getRenderTime() {
  return renderTime;
}

double FramerateController::getTime() {
  return glfwGetTime(); 
}

double FramerateController::getSeconds() {
  return glfwGetTime() - timeAtProgramStart;
}
