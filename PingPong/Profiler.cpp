#include "Profiler.h"

void Profiler::update()
{
	const auto now = std::chrono::steady_clock::now();
	delta = std::chrono::duration<float, std::milli>(now - priviousUpdate).count();
	priviousUpdate = now;
	iterations++;
	accumulated += delta;
	// FPS is sampled on the game loop itself: no background thread, no data races.
	if (accumulated >= samples * 1000.f) {
		fps = static_cast<int>(iterations * 1000.f / accumulated + 0.5f);
		iterations = 0;
		accumulated = 0.f;
	}
}

void Profiler::reset()
{
	priviousUpdate = std::chrono::steady_clock::now(); // Переменные для подсчета пройденного времени
	delta = 0.f;
}

int Profiler::getFps() const
{
	return fps;
}

float Profiler::getDelta() const
{
	return delta;
}

Profiler::Profiler(int s) : samples(s > 0 ? s : 1)
{
	reset();
}
