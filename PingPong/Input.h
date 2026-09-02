#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

// Key is physically held down right now.
inline bool keyDown(int vk)
{
	return (GetAsyncKeyState(vk) & 0x8000) != 0;
}

// Key went from released to pressed since the previous call for that key.
// Own edge detection instead of GetAsyncKeyState's "pressed since last call" bit (& 1),
// which is shared by every process on the machine and is still set at startup by the
// Enter that launched the program.
inline bool keyPressed(int vk)
{
	static bool initialized = false;
	static bool held[256];
	if (!initialized) {
		for (bool& h : held) h = true; // keys already down at startup are ignored until released
		initialized = true;
	}
	const int index = vk & 0xFF;
	const bool down = keyDown(vk);
	const bool pressed = down && !held[index];
	held[index] = down;
	return pressed;
}
