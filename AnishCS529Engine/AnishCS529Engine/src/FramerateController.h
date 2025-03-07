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

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <thread>
#include <vector>

/*!****************************************************************************
 * \brief Framerate Controller
 * 
 * ## Usage:
 * 
 * The framerate controller is responsible for all things time. Ensure that
 * this is used to handle calculation of deltaTime, set up framerate limits,
 * and for physics update handling.
 * 
 * ## Pre-initialization calls:
 * 
 * N/A
 * 
 * ## General lifecycle of a FramerateController:
 * 
 * - Create the FramerateController object.
 * - Call setTargetFramerate() if a different framerate is required.
 * - Call setPhysicsTimestep() if a different physics timestep is required.
 * - In the main loop:
 *  - Start the main loop by calling startFrame().
 *  - Run physics update loop using shouldUpdatePhysics() as condition.
 *  - Call getPhysicsTimestep() to get the deltaTime for physics update.
 *  - Call consumePhysicsTime() in the physics update loop at the end of each
 *   iteration.
 *  - Call endFrame() at the end of the main loop iteration.
 *  - (Optional) call getFrameTime() for debugging or other reasons.
 * 
 * ## Defaults:
 * 
 * - targetFrameTime: 1/60
 * - physicsAccumulatorTimestep: 1/120
 * 
 * ## Notes:
 * 
 * Some optional features are available if needed, but documentation is not
 * yet ready for them.
 * 
 *****************************************************************************/
template<typename T = float>
class FramerateController {
public:
  static FramerateController * getController();

  void setTargetFramerate(const unsigned int framerate);

  void startFrame();
  void endFrame();
  T getFPS();
  T getRenderTime();
  T getFrameTime();
  T getTime();
  T getPhysicsTimestep();

  void setPhysicsTimestep(T timestep);
  bool shouldUpdatePhysics() const;
  void consumePhysicsTime();
  T getAccumulatorAlpha() const;


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
  const unsigned int createAccumulator(const T timestep);
  bool accumulatorShouldFire(const unsigned int accumulatorId) const;
  void consumeAccumulator(const unsigned int accumulatorId);
  T getAccumulatorAlpha(const unsigned int accumulatorId) const;
  /*@}*/
#endif // ENABLE_ADDITIONAL_ACCUMULATORS

private:
  FramerateController();
  ~FramerateController() = default;

  /** Target frame time */
  T targetFrameTime;
  /** Time at the start of current frame */
  T timeAtFrameStart;
  /** Time at the end of current frame */
  T timeAtFrameEnd;
  /** Time taken for the last frame to render */
  T renderTime;
  /** Time between last frame start and frame end */
  T lastFrameTime;
  /** Number of frames elapsed since start of program */
  long int frameCount;
  /** Frame counter for FPS query */
  long int framesSinceLastFPSQuery;
  /** Time when last FPS query occurred */
  T timeOfLastFPSQuery;

  /** Physics accumulator timestep */
  T physicsAccumulatorTimestep;
  /** Accumulated Physics accumulator time */
  T physicsAccumulator;

#ifdef ENABLE_RATE_CONTROLLERS
  /*! \name Rate Controllers
   * @{
   */
  /** Number of registered rate controllers */
  unsigned int rateControllersRegistered;
  /** Target rate of controller */
  std::vector<T> rateControllerTargetRates;
  /** Time at last fire of rate controller */
  std::vector<T> rateControllerTimes;
  /*@}*/
#endif // ENABLE_RATE_CONTROLLERS

#ifdef ENABLE_ADDITIONAL_ACCUMULATORS
  /*! \name Additional Accumulators
   * @{
   */
  /** Number of registered accumulators */
  unsigned int accumulatorsRegistered;
  /** Timestep for the accumulators */
  std::vector<T> accumulatorTimesteps;
  /** Accumulated time of the accumulators */
  std::vector<T> accumulatorTimes;
  /*@}*/
#endif // ENABLE_ADDITIONAL_ACCUMULATORS
};

using FFramerateController = FramerateController<float>;
using DFramerateController = FramerateController<double>;

#include "FramerateController.inl" // ERROR: you have a circular reference here.  

#endif // FRAMERATE_CONTROLLER_H
