#include "FramerateController.h"
#include "glfw3.h"

#define MILLISECOND 1000




FramerateController* FramerateController::instance = nullptr;

FramerateController* FramerateController::GetInstance()
{
	instance = new FramerateController;
	return instance;
}

FramerateController::FramerateController()
{
	frameCount = 0;
	timeAtSpecificFrame = 0.0;

	// example physics
	accumulator = 0.0;
}

void FramerateController::SetTargetFramerate(unsigned int framerate)
{
	targetFrameTime = (int)(MILLISECOND / framerate);
}

void FramerateController::SetFrameAtLevelStart(const int time)
{
	frameAtLevelStart = time;
}

void FramerateController::FrameStart()
{
	timeAtFrameStart = glfwGetTime();
}

void FramerateController::FrameEnd()
{
	lastRenderTime = glfwGetTime() - timeAtFrameStart;

	timeAtFrameEnd = glfwGetTime();
	double delta = timeAtFrameEnd - timeAtFrameStart;
	double tt = (targetFrameTime / 1000.0);
	while (timeAtFrameEnd - timeAtFrameStart < tt)
		timeAtFrameEnd = glfwGetTime();

	++frameCount;

	lastFrameTime = timeAtFrameEnd - timeAtFrameStart;
	DeltaTime = (float)lastFrameTime;

	// example physics
	accumulator += DeltaTime;
}

void FramerateController::MarkTimeAtFrame(int frameNumber)
{
	if (frameCount == frameNumber)
		timeAtSpecificFrame = glfwGetTime();
}

float FramerateController::GetTimeAtFrameLastMarkedFrame()
{
	return timeAtSpecificFrame;
}

double FramerateController::GetElapsedTimeSinceLastMarkedFrame()
{
	return glfwGetTime() - timeAtSpecificFrame;
}

double FramerateController::GetFrameTime() const
{
	return lastFrameTime;
}

float FramerateController::GetFPS() const
{
	return 1.0f / (float)lastFrameTime;
}

int FramerateController::GetFrameNumber() const
{
	return frameCount;
}

void FramerateController::ResetFrameNummber()
{
	frameCount = 0;
}

double FramerateController::GetRenderTime() const
{
	return lastRenderTime;
}

double FramerateController::GetFrameAtLevelStart() const
{
	return frameAtLevelStart;
}

double FramerateController::GetTime() const
{
	return targetFrameTime;
}

double FramerateController::GetSeconds() const
{
	return glfwGetTime();
}

bool FramerateController::ShouldUpdatePhysics()
{
	return accumulator >= DEFAULT_FIXED_TIME_STEP;
}

void FramerateController::ConsumePhysicsTime()
{
	accumulator -= DEFAULT_FIXED_TIME_STEP;
}