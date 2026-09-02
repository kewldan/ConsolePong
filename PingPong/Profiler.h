#pragma once
#include <chrono>

class Profiler
{
	std::chrono::steady_clock::time_point priviousUpdate;
	float delta = 0.f;       // last frame time, ms
	float accumulated = 0.f; // ms since the fps counter was last sampled
	int fps = 0, iterations = 0, samples = 1;
public:
	void update();
	void reset();
	int getFps() const;
	float getDelta() const;
	explicit Profiler(int samples);
};
