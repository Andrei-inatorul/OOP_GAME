#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Time.h"

class Game{
public:
	Game();
	~Game();
	Time* time;
	/// <summary>
	/// Initialises everything the game window needs
	/// </summary>
	/// <param name="title">-> game window title </param>
	/// <param name="xpos">-> game window position on the x axis ,NULL for centered</param>
	/// <param name="ypos">-> game window position on the y axis ,NULL for centered</param>
	/// <param name="width">-> game window width</param>
	/// <param name="height">-> game window height</param>
	/// <param name="fullscreen">-> choose if the game window is fullscreen or not(true for fulscreen)</param>
	void init(const char title[50], int xpos, int ypos, int width, int height, bool fullscreen);
	/// <summary>
	/// Things that need to be set up before the game loop
	/// </summary>
	/// <param name=""></param>
	void Start(void);
	/// <summary>
	/// handles events like keypresses and such
	/// </summary>
	void handleEvents(void);
	/// <summary>
	/// for physics updates 
	/// </summary>
	void update(void);
	/// <summary>
	/// for rendering to the game window
	/// </summary>
	void render(void);
	/// <summary>
	/// clears everything up
	/// </summary>
	void cleanup(void);
	/// <summary>
	/// checks if the game is running
	/// </summary>
	/// <returns>true if the game is running, false otherwise</returns>
	bool running(void);
private:
	bool isRunning;
	SDL_Renderer* renderer;
	SDL_Window* window;
};

