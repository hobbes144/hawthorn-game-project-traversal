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
#ifndef FRAMERATECONTROLLER_INL
#define FRAMERATECONTROLLER_INL
#include "FramerateController.h"

/*!****************************************************************************
 * \brief Singleton class object getter function
 * 
 * \return \b FramerateController& The Framerate Controller obejct.
 *****************************************************************************/
template<typename T>
FramerateController<T> * FramerateController<T>::getController() {
  {
    static FramerateController controller;
    return &controller;
  }
}

/*!****************************************************************************
 * \brief Constructor
 * 
 *****************************************************************************/
template<typename T>
FramerateController<T>::FramerateController() : 
  targetFrameTime(1.0f / 60.0f),
  timeAtFrameStart(static_cast<T>(glfwGetTime())),
  timeAtFrameEnd(static_cast<T>(glfwGetTime())),
  renderTime(0.0f),
  lastFrameTime(0.0f),
  frameCount(0),
  framesSinceLastFPSQuery(0),
  timeOfLastFPSQuery(static_cast<T>(glfwGetTime())),
  physicsAccumulatorTimestep(1.0f/120.0f),
  physicsAccumulator(0.0f)
#ifdef ENABLE_RATE_CONTROLLERS
  ,rateControllersRegistered(0),
  rateControllerTargetRates({}),
  rateControllerTimes({})
#endif // ENABLE_RATE_CONTROLLERS
#ifdef ENABLE_ADDITIONAL_ACCUMULATORS
  ,accumulatorsRegistered(0),
  accumulatorTimesteps({}),
  accumulatorTimes({})
#endif // ENABLE_ADDITIONAL_ACCUMULATORS
{}

/*!****************************************************************************
 * \brief Sets the target framerate
 * 
 * Default is 60 fps.
 * 
 * \param framerate The target framerate in frames per second.
 *****************************************************************************/
template<typename T>
void FramerateController<T>::setTargetFramerate(const unsigned int framerate) {
  targetFrameTime = 1.0f/framerate;
}

/*!****************************************************************************
 * \brief Starts the frame logic
 * 
 * Stores the frame start time so that endFrame() can correctly function.
 * 
 *****************************************************************************/
template<typename T>
void FramerateController<T>::startFrame() {
  timeAtFrameStart = static_cast<T>(glfwGetTime());
}

/*!****************************************************************************
 * \brief Runs the end of frame logic
 * 
 * Uses a busy-wait loop to check if frame has ended.
 * Also updates accumulators.
 * 
 *****************************************************************************/
template<typename T>
void FramerateController<T>::endFrame() {
  renderTime = static_cast<T>(glfwGetTime()) - timeAtFrameStart;
  frameCount++; framesSinceLastFPSQuery++;
  /*T remainingTime = targetFrameTime - renderTime;
  if (remainingTime > 0) {
    std::this_thread::sleep_for(
      std::chrono::duration<T>(remainingTime * 0.9));
  }*/
  while ((static_cast<T>(glfwGetTime()) - timeAtFrameStart) < targetFrameTime);
  timeAtFrameEnd = static_cast<T>(glfwGetTime());
  lastFrameTime = timeAtFrameEnd - timeAtFrameStart;
  physicsAccumulator += lastFrameTime;

#ifdef ENABLE_ADDITIONAL_ACCUMULATORS
  for (unsigned int i = 0; i < accumulatorsRegistered; i++)
    accumulatorTimes[i] += lastFrameTime;
#endif // ENABLE_ADDITIONAL_ACCUMULATORS

}

/*!****************************************************************************
 * \brief Gets the FPS
 * 
 * This is calculated as the average of frames created per second since the
 * last getFPS() call.
 * 
 * \return \b T Current frames per second.
 *****************************************************************************/
template<typename T>
T FramerateController<T>::getFPS() {
  T lastQuery = timeOfLastFPSQuery;
  long int numFrames = framesSinceLastFPSQuery;
  timeOfLastFPSQuery = static_cast<T>(glfwGetTime());
  framesSinceLastFPSQuery = 0;
  return (numFrames / (static_cast<T>(glfwGetTime()) - lastQuery));
}

/*!****************************************************************************
 * \brief Get last frame's render time
 * 
 * \return \b T Render time for last frame.
 *****************************************************************************/
template<typename T>
T FramerateController<T>::getRenderTime() {
  return renderTime;
}

/*!****************************************************************************
 * \brief Get frame time
 * 
 * \return \b T Time between start and end of last frame.
 *****************************************************************************/
template<typename T>
T FramerateController<T>::getFrameTime() {
  return lastFrameTime;
}

/*!****************************************************************************
 * \brief Get time
 * 
 * \return \b T Time.
 *****************************************************************************/
template<typename T>
T FramerateController<T>::getTime() {
  return static_cast<T>(glfwGetTime());
}

template<typename T>
inline T FramerateController<T>::getPhysicsTimestep()
{
  return physicsAccumulatorTimestep;
}

/*!****************************************************************************
 * \brief Set the timestep for the Physics Accumulator
 * 
 * \param timestep Timestep of the accumulator.
 *****************************************************************************/
template<typename T>
void FramerateController<T>::setPhysicsTimestep(T timestep) {
  physicsAccumulatorTimestep = timestep;
}

/*!****************************************************************************
 * \brief If physics should update
 * 
 * \return \b bool True if accumulated at least one timestep.
 *****************************************************************************/
template<typename T>
bool FramerateController<T>::shouldUpdatePhysics() const
{
  return physicsAccumulator >= physicsAccumulatorTimestep;
}

/*!****************************************************************************
 * \brief Consume one Physics timestep from accumulator
 * 
 *****************************************************************************/
template<typename T>
void FramerateController<T>::consumePhysicsTime()
{
  physicsAccumulator -= physicsAccumulatorTimestep;
}

/*!****************************************************************************
 * \brief Clear Physics timestep from accumulator
 * 
 *****************************************************************************/
template<typename T>
void FramerateController<T>::clearPhysicsTime()
{
  physicsAccumulator = 0.0f;
}

template<typename T>
inline void FramerateController<T>::clearPhysicsTime()
{
    physicsAccumulator = 0.0f;
}

template<typename T>
T FramerateController<T>::getAccumulatorAlpha() const {
  return physicsAccumulator / physicsAccumulatorTimestep;
}


/* Optional features */

#ifdef ENABLE_RATE_CONTROLLERS
/*!****************************************************************************
 * \brief Creates a rate controller
 * 
 * \b Note: This feature is only enabled when the flag 
 * ENABLE_RATE_CONTROLLERS is set
 * 
 * Rate controllers are separate timers that are used to check if at least the
 * designated rate has elapsed since last successful fire.
 * 
 * This is low budget since it does not get updated every frame, and instead 
 * only calculates when asked.
 * 
 * This can be expanded to have the functionality of an accumulator.
 * Tradeoff: This method has longer calc time during checking, but it has
 * lesser impact on endFrame().
 * 
 * Possible direction: We could extend this to have a callback function that
 * we can trigger in the endFrame() loop.
 * 
 * \param rate
 * \return \b 
 *****************************************************************************/
template<typename T>
const unsigned int FramerateController<T>::createRateController(
  const unsigned int rate) {

  unsigned int rateControllerId = rateControllersRegistered;
  rateControllersRegistered++;
  rateControllerTimes.push_back(static_cast<T>(glfwGetTime()));
  rateControllerTimes[rateControllerId] = static_cast<T>(glfwGetTime());
  rateControllerTargetRates.push_back(1.0 / rate);
  rateControllerTargetRates[rateControllerId] = (1.0 / rate);

  return rateControllerId;
}

/*!****************************************************************************
 * \brief If the specified rate controller should fire
 * 
 * Checks if at least `1/rate` time has elapsed since last fire.
 * This also updates the last fire time.
 * 
 * \param rateControllerId
 * \return \b 
 *****************************************************************************/
template<typename T>
bool FramerateController<T>::rateControllerShouldFire(
  const unsigned int rateControllerId) {

  if (rateControllerId >= rateControllersRegistered) {
    return true;
  }
  T currentTime = static_cast<T>(glfwGetTime());
  if ((currentTime - rateControllerTimes[rateControllerId]) > 
    rateControllerTargetRates[rateControllerId]) {

    rateControllerTimes[rateControllerId] = currentTime;
    return true;
  }
  return false;
}
#endif // ENABLE_RATE_CONTROLLERS

#ifdef ENABLE_ADDITIONAL_ACCUMULATORS
/*!****************************************************************************
 * \brief Create an accumulator
 * 
 * \b Note: This feature is only enabled when the flag 
 * ENABLE_ADDITIONAL_ACCUMULATORS is set
 * 
 * Accumulators get updated on every endFrame() call. It can be used when we
 * need to know the number of times some logic should run asyncronously.
 * 
 * \param timestep
 * \return \b 
 *****************************************************************************/
template<typename T>
const unsigned int FramerateController<T>::createAccumulator(const T timestep) {
  unsigned int accumulatorId = accumulatorsRegistered;
  accumulatorsRegistered++;
  accumulatorTimesteps.push_back(timestep);
  accumulatorTimes.push_back(0.0);
  return accumulatorId;
}

/*!****************************************************************************
 * \brief If the accumulator should fire
 * 
 * \param accumulatorId ID of the accumulator.
 * \return \b bool True is should fire.
 *****************************************************************************/
template<typename T>
bool FramerateController<T>::accumulatorShouldFire(const unsigned int accumulatorId) const {
  return (accumulatorTimes[accumulatorId] >= accumulatorTimesteps[accumulatorId]);
}

/*!****************************************************************************
 * \brief Consume the accumulator
 * 
 * \param accumulatorId ID of the accumulator.
 *****************************************************************************/
template<typename T>
void FramerateController<T>::consumeAccumulator(const unsigned int accumulatorId) {
  accumulatorTimes[accumulatorId] -= accumulatorTimesteps[accumulatorId];
}

/*!****************************************************************************
 * \brief Get the number of accumulated timesteps
 * 
 * \param accumulatorId ID of the accumulator.
 * \return \b T Number of accumulated timesteps.
 *****************************************************************************/
template<typename T>
T FramerateController<T>::getAccumulatorAlpha(const unsigned int accumulatorId) const {
  return accumulatorTimes[accumulatorId] / accumulatorTimesteps[accumulatorId];
}
#endif // ENABLE_ADDITIONAL_ACCUMULATORS
#endif // FRAMERATECONTROLLER_INL
