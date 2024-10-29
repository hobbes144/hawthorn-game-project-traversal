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
  static FramerateController& getController();

  void setTargetFramerate(const unsigned int framerate);

  void startFrame();
  void endFrame();
  double getFPS();
  double getRenderTime();
  double getFrameTime();
  double getTime();

  void setPhysicsTimestep(double timestep);
  bool ShouldUpdatePhysics() const;
  void ConsumePhysicsTime();
  double GetAccumulatorAlpha() const;


  /* Optional features */

  /* ToDo: Need to decide if we need this. */
  /*! \name Rate Controllers
   * @{
   */
  const unsigned int createRateController(const unsigned int rate);
  bool rateControllerShouldFire(const unsigned int rateControllerId);
  /*@}*/

  /*! \name Additional Accumulators
   * @{
   */
  const unsigned int createAccumulator(const double timestep);
  bool accumulatorShouldFire(const unsigned int accumulatorId) const;
  void consumeAccumulator(const unsigned int accumulatorId);
  double getAccumulatorAlpha(const unsigned int accumulatorId) const;
  /*@}*/

private:
  FramerateController();
  ~FramerateController() = default;

  /** Target frame time */
  double targetFrameTime;
  /** Time at the start of current frame */
  double timeAtFrameStart;
  /** Time at the end of current frame */
  double timeAtFrameEnd;
  /** Time taken for the last frame to render */
  double renderTime;
  /** Time between last frame start and frame end */
  double lastFrameTime;
  /** Number of frames elapsed since start of program */
  long int frameCount;
  /** Frame counter for FPS query */
  long int framesSinceLastFPSQuery;
  /** Time when last FPS query occurred */
  double timeOfLastFPSQuery;

  /** Physics accumulator timestep */
  double physicsAccumulatorTimestep;
  /** Accumulated Physics accumulator time */
  double physicsAccumulator;

  /*! \name Rate Controllers
   * @{
   */
  /** Number of registered rate controllers */
  unsigned int rateControllersRegistered;
  /** Target rate of controller */
  std::vector<double> rateControllerTargetRates;
  /** Time at last fire of rate controller */
  std::vector<double> rateControllerTimes;
  /*@}*/

  /*! \name Additional Accumulators
   * @{
   */
  /** Number of registered accumulators */
  unsigned int accumulatorsRegistered;
  /** Timestep for the accumulators */
  std::vector<double> accumulatorTimesteps;
  /** Accumulated time of the accumulators */
  std::vector<double> accumulatorTimes;
  /*@}*/
};

#endif // FRAMERATE_CONTROLLER_H
