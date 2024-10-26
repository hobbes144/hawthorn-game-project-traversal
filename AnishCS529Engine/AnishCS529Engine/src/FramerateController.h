/*!****************************************************************************
 * \file   FramerateController.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-25-2024
 * \brief  Framerate Controller
 * 
 *****************************************************************************/
#ifndef FRAMERATE_CONTROLLER_H
#define FRAMERATE_CONTROLLER_H

#pragma once

#include "GLFW/glfw3.h"
#include <thread>
#include <vector>

class FramerateController {
public:
  static FramerateController& getController() {
    static FramerateController controller;
    return controller;
  }

  void setTargetFramerate(const unsigned int framerate);

  void frameStart();
  void frameEnd();
  double getFPS();
  double getRenderTime();
  double getTime();
  double getSeconds();

  unsigned int createRateController(const unsigned int rate);
  bool rateControllerShouldFire(const unsigned int rateControllerId);

private:
  FramerateController();
  ~FramerateController() = default;

  double targetFrameTime;
  double timeAtProgramStart;
  double timeAtFrameStart;
  double timeAtFrameEnd;
  double renderTime;
  long int frameCount;
  long int framesSinceLastFPSQuery;
  double timeOfLastFPSQuery;

  unsigned int rateControllersRegistered;
  std::vector<double> rateControllerTargetTimes;
  std::vector<double> rateControllerTimes;

};

#endif // !FRAMERATE_CONTROLLER_H
