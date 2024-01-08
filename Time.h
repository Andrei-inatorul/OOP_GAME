#pragma once
#include <SDL.h>

class Time
{
public:
	Time();
	float DeltaTime;
	Uint64 currentTime;
	void Tick();
private:
	Uint64 t2;
};

