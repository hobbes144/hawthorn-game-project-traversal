#pragma once
#include <Windows.h>
class FramerateController
{
public:
	static constexpr double DEFAULT_FIXED_TIME_STEP = 1.0 / 240.0;


public:
	static FramerateController* GetInstance();
	~FramerateController() = default;

	void SetTargetFramerate(unsigned int framerate);
	void SetFrameAtLevelStart(const int time);
	void FrameStart();
	void FrameEnd();
	void MarkTimeAtFrame(int frameNumber);
	float GetTimeAtFrameLastMarkedFrame();
	double GetFrameTime() const;
	float GetFPS() const;
	int GetFrameNumber() const;
	double GetElapsedTimeSinceLastMarkedFrame();
	void ResetFrameNummber();
	double GetRenderTime() const;
	double GetFrameAtLevelStart() const;
	double GetTime() const;
	double GetSeconds() const;

	float DeltaTime;

	bool ShouldUpdatePhysics();
	void ConsumePhysicsTime();
	double GetAccumulatorAlpha() const { return accumulator / DEFAULT_FIXED_TIME_STEP; }

	// test
	void Exaggerate() {
		if (GetFrameNumber() % 100 < 10) {
			Sleep(5);
		}
	}

private:

	FramerateController();
	static FramerateController* instance;

	int frameCount;
	double frameAtLevelStart;
	double timeAtFrameStart;
	double timeAtFrameEnd;
	double timeAtSpecificFrame;
	double lastFrameTime;
	double lastRenderTime;
	int targetFrameTime;

	double accumulator;

};

