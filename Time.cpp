#include <SDL.h>
#include "Time.h"

Time::Time()
{
	DeltaTime = 0;
	t2 = 0;
	currentTime = 0;
}

void Time::Tick() // deltaTime (timpul de la ultima iteratie din game loop)
{
	currentTime = SDL_GetTicks();
	DeltaTime = currentTime - t2;
	DeltaTime = DeltaTime / 1000.0f;
	t2 = currentTime; 
}
