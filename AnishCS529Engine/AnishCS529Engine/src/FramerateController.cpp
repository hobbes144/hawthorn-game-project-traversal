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

/*!****************************************************************************
 * \brief Singleton class object getter function
 * 
 * \return \b FramerateController& The Framerate Controller obejct.
 *****************************************************************************/
FramerateController& FramerateController::getController() {
  {
    static FramerateController controller;
    return controller;
  }
}

/*!****************************************************************************
 * \brief Constructor
 * 
 *****************************************************************************/
FramerateController::FramerateController() : 
  targetFrameTime(1.0 / 60.0),
  timeAtFrameStart(glfwGetTime()),
  timeAtFrameEnd(glfwGetTime()),
  renderTime(0.0),
  lastFrameTime(0.0),
  frameCount(0),
  framesSinceLastFPSQuery(0),
  timeOfLastFPSQuery(glfwGetTime()),
  physicsAccumulatorTimestep(1.0/120.0),
  physicsAccumulator(0.0)
#ifdef ENABLE_ADDITIONAL_ACCUMULATORS
  ,rateControllersRegistered(0),
  rateControllerTargetRates({}),
  rateControllerTimes({})
#endif // ENABLE_ADDITIONAL_ACCUMULATORS
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
void FramerateController::setTargetFramerate(const unsigned int framerate) {
  targetFrameTime = 1.0/framerate;
}

/*!****************************************************************************
 * \brief Starts the frame logic
 * 
 * Stores the frame start time so that endFrame() can correctly function.
 * 
 *****************************************************************************/
void FramerateController::startFrame() {
  timeAtFrameStart = glfwGetTime();
}

/*!****************************************************************************
 * \brief Runs the end of frame logic
 * 
 * Uses a busy-wait loop to check if frame has ended.
 * Also updates accumulators.
 * 
 *****************************************************************************/
void FramerateController::endFrame() {
  renderTime = glfwGetTime() - timeAtFrameStart;
  frameCount++; framesSinceLastFPSQuery++;
  /*double remainingTime = targetFrameTime - renderTime;
  if (remainingTime > 0) {
    std::this_thread::sleep_for(
      std::chrono::duration<double>(remainingTime * 0.9));
  }*/
  while ((glfwGetTime() - timeAtFrameStart) < targetFrameTime);
  timeAtFrameEnd = glfwGetTime();
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
 * \return \b double Current frames per second.
 *****************************************************************************/
double FramerateController::getFPS() {
  double lastQuery = timeOfLastFPSQuery;
  long int numFrames = framesSinceLastFPSQuery;
  timeOfLastFPSQuery = glfwGetTime();
  framesSinceLastFPSQuery = 0;
  return (numFrames / (glfwGetTime() - lastQuery));
}

/*!****************************************************************************
 * \brief Get last frame's render time
 * 
 * \return \b double Render time for last frame.
 *****************************************************************************/
double FramerateController::getRenderTime() {
  return renderTime;
}

/*!****************************************************************************
 * \brief Get frame time
 * 
 * \return \b double Time between start and end of last frame.
 *****************************************************************************/
double FramerateController::getFrameTime() {
  return lastFrameTime;
}

/*!****************************************************************************
 * \brief Get time
 * 
 * \return \b double Time.
 *****************************************************************************/
double FramerateController::getTime() {
  return glfwGetTime(); 
}

/*!****************************************************************************
 * \brief Set the timestep for the Physics Accumulator
 * 
 * \param timestep Timestep of the accumulator.
 *****************************************************************************/
void FramerateController::setPhysicsTimestep(double timestep) {
  physicsAccumulatorTimestep = timestep;
}

/*!****************************************************************************
 * \brief If physics should update
 * 
 * \return \b bool True if accumulated at least one timestep.
 *****************************************************************************/
bool FramerateController::shouldUpdatePhysics() const
{
  return physicsAccumulator >= physicsAccumulatorTimestep;
}

/*!****************************************************************************
 * \brief Consume one Physics timestep from accumulator
 * 
 *****************************************************************************/
void FramerateController::consumePhysicsTime()
{
  physicsAccumulator -= physicsAccumulatorTimestep;
}

double FramerateController::getAccumulatorAlpha() const {
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
const unsigned int FramerateController::createRateController(
  const unsigned int rate) {

  unsigned int rateControllerId = rateControllersRegistered;
  rateControllersRegistered++;
  rateControllerTimes.push_back(glfwGetTime());
  rateControllerTimes[rateControllerId] = glfwGetTime();
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
bool FramerateController::rateControllerShouldFire(
  const unsigned int rateControllerId) {

  if (rateControllerId >= rateControllersRegistered) {
    return true;
  }
  double currentTime = glfwGetTime();
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
const unsigned int FramerateController::createAccumulator(const double timestep) {
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
bool FramerateController::accumulatorShouldFire(const unsigned int accumulatorId) const {
  return (accumulatorTimes[accumulatorId] >= accumulatorTimesteps[accumulatorId]);
}

/*!****************************************************************************
 * \brief Consume the accumulator
 * 
 * \param accumulatorId ID of the accumulator.
 *****************************************************************************/
void FramerateController::consumeAccumulator(const unsigned int accumulatorId) {
  accumulatorTimes[accumulatorId] -= accumulatorTimesteps[accumulatorId];
}

/*!****************************************************************************
 * \brief Get the number of accumulated timesteps
 * 
 * \param accumulatorId ID of the accumulator.
 * \return \b double Number of accumulated timesteps.
 *****************************************************************************/
double FramerateController::getAccumulatorAlpha(const unsigned int accumulatorId) const {
  return accumulatorTimes[accumulatorId] / accumulatorTimesteps[accumulatorId];
}
#endif // ENABLE_ADDITIONAL_ACCUMULATORS

