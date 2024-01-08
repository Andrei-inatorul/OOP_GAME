#include "gameUtil.h"
#include "gameObject.h"
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // hide console ( comment this if debugging)
int main(int argc,char* argv[])
{
	Game* game = new Game();

	const int FPS = 60;
	const int FrameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game->init("Spirit Of The Forest - Lefter Andrei 1208A", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);
	game->Start();
	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (FrameDelay > frameTime)
		{
			SDL_Delay(FrameDelay - frameTime);
		}

	}
	game->cleanup();
	return 0;
}
