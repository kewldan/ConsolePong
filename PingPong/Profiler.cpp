#include "Profiler.h"

void Profiler::update()
{
	now = std::chrono::system_clock::now();
	std::chrono::duration <float> elapsedTime = now - priviousUpdate;
	priviousUpdate = now;
	delta = elapsedTime.count() * 1000.f;
	iterations++;
}

int Profiler::getFps()
{
	return fps;
}

float Profiler::getDelta()
{
	return delta;
}

Profiler::Profiler(int s)
{
	samples = s;
	now = std::chrono::system_clock::now(); // ѕеременные дл€ подсчета
	priviousUpdate = std::chrono::system_clock::now(); // пройденного времени

	thread = new std::thread([](Profiler* profiler) {
		while (profiler->active) {
			profiler->fps = profiler->iterations * (1 / profiler->samples);
			profiler->iterations = 0;
			std::this_thread::sleep_for(std::chrono::milliseconds(profiler->samples * 1000));
		}
		}, this);
}

Profiler::~Profiler()
{
	active = 0;
}
