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
  static FramerateController * getController();

  void setTargetFramerate(const unsigned int framerate);

  void startFrame();
  void endFrame();
  float getFPS();
  float getRenderTime();
  float getFrameTime();
  float getTime();

  void setPhysicsTimestep(float timestep);
  bool shouldUpdatePhysics() const;
  void consumePhysicsTime();
  float getAccumulatorAlpha() const;


  /* Optional features */

#ifdef ENABLE_RATE_CONTROLLERS
  /* ToDo: Need to decide if we need this. */
  /*! \name Rate Controllers
   * @{
   */
  const unsigned int createRateController(const unsigned int rate);
  bool rateControllerShouldFire(const unsigned int rateControllerId);
  /*@}*/
#endif // ENABLE_RATE_CONTROLLERS

#ifdef ENABLE_ADDITIONAL_ACCUMULATORS
  /*! \name Additional Accumulators
   * @{
   */
  const unsigned int createAccumulator(const float timestep);
  bool accumulatorShouldFire(const unsigned int accumulatorId) const;
  void consumeAccumulator(const unsigned int accumulatorId);
  float getAccumulatorAlpha(const unsigned int accumulatorId) const;
  /*@}*/
#endif // ENABLE_ADDITIONAL_ACCUMULATORS

private:
  FramerateController();
  ~FramerateController() = default;

  /** Target frame time */
  float targetFrameTime;
  /** Time at the start of current frame */
  float timeAtFrameStart;
  /** Time at the end of current frame */
  float timeAtFrameEnd;
  /** Time taken for the last frame to render */
  float renderTime;
  /** Time between last frame start and frame end */
  float lastFrameTime;
  /** Number of frames elapsed since start of program */
  long int frameCount;
  /** Frame counter for FPS query */
  long int framesSinceLastFPSQuery;
  /** Time when last FPS query occurred */
  float timeOfLastFPSQuery;

  /** Physics accumulator timestep */
  float physicsAccumulatorTimestep;
  /** Accumulated Physics accumulator time */
  float physicsAccumulator;

#ifdef ENABLE_RATE_CONTROLLERS
  /*! \name Rate Controllers
   * @{
   */
  /** Number of registered rate controllers */
  unsigned int rateControllersRegistered;
  /** Target rate of controller */
  std::vector<float> rateControllerTargetRates;
  /** Time at last fire of rate controller */
  std::vector<float> rateControllerTimes;
  /*@}*/
#endif // ENABLE_RATE_CONTROLLERS

#ifdef ENABLE_ADDITIONAL_ACCUMULATORS
  /*! \name Additional Accumulators
   * @{
   */
  /** Number of registered accumulators */
  unsigned int accumulatorsRegistered;
  /** Timestep for the accumulators */
  std::vector<float> accumulatorTimesteps;
  /** Accumulated time of the accumulators */
  std::vector<float> accumulatorTimes;
  /*@}*/
#endif // ENABLE_ADDITIONAL_ACCUMULATORS
};

#endif // FRAMERATE_CONTROLLER_H
