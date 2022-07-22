#pragma once
#include <chrono>
#include <thread>

class Profiler
{
	std::chrono::system_clock::time_point priviousUpdate, now;
	std::thread* thread;
	float delta;
	int fps, iterations, samples;
	bool active = true;
public:
	void update();
	int getFps();
	float getDelta();
	Profiler(int samples);
	~Profiler();
};

