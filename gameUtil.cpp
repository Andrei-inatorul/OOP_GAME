#include <iostream>
#include <fstream>
#include "gameUtil.h"
#include "gameObject.h"
#include "Player.h"
#include "Time.h"
#include "Camera.h"
#include "Platform.h"
#include "Map.h"
#include "gameUtil.h"
#include "Button.h"
#include "UiSprite.h"

Player* player;
Camera* camera;
Entity* enemy;
Map* map;


std::fstream file("./savegame.txt", std::ios::in | std::ios::out);
short lvl;
const int TOTAL_KEYS = 256;
bool keyState[TOTAL_KEYS] = { false };

Game::Game()
{
	isRunning = false;
	window = nullptr;
	renderer = nullptr;
	time = nullptr;
}

Game::~Game()
{
	window = nullptr;
	renderer = nullptr;
}

void Game::init(const char title[50], int xpos, int ypos, int width, int height, bool fullscreen) // initialise widow and all game subsystems
{
	int flags = 0; // used to set fullscreenmode on/off when initialising the game						
	if (fullscreen)						
	{									
		flags = SDL_WINDOW_FULLSCREEN;
	}													
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // test if SDL systems are initialised before doing anything			
	{
		std::cout << "Sdl systems initialised...\n";
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Successfully created window...\n";
		}
		else
		{
			std::cerr << "Failed to create window! :((\n";
			exit(EXIT_FAILURE);
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Successfully created renderer...\n";
		}
		else
		{
			std::cerr << "Failed to create renderer! :((\n";
			exit(EXIT_FAILURE);
		}
		if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
		{
			std::cout << "Successfully initialised SDL_Image for png files...\n";
		}
		else
		{
			std::cerr << "Failed to initialise SDL_Image for png files! :((" << IMG_GetError << "\n";
			exit(EXIT_FAILURE);
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
		std::cerr << "Sdl systems failed to initialise! :(( " << SDL_GetError() <<"\n";
		exit(EXIT_FAILURE);
	}
	SDL_Surface* icon = SDL_LoadBMP("./Assets/icon.bmp");
	// Set the window icon
	SDL_SetWindowIcon(window, icon);
	// Free the icon surface
	SDL_FreeSurface(icon);
	time = new Time;
}

bool Game::running() 
{
	return isRunning;	// returns true if the game is running properly
}

void Game::Start() //things that are set up at the beginning of the game loop
{
	short choice = 0;
	UiSprite* menuBg = new UiSprite(Vector2(0, 0), Vector2(1280, 720), "./Assets/Ui/TitleScreen.png");
	Button* loadgameBtn = new Button(Vector2(440, 300), Vector2(400, 120), "./Assets/Ui/TitleBtnLoad.png");
	Button* newgameBtn = new Button(Vector2(440, 470), Vector2(400, 120), "./Assets/Ui/TitleBtnNew.png");
	
	SDL_RenderClear(renderer);
	menuBg->SetTexture(renderer);
	loadgameBtn->SetTexture(renderer);
	newgameBtn->SetTexture(renderer);
	int mouseX, mouseY;
	SDL_FRect mouseHover;
	while (choice == 0)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		int mouseX, mouseY;
		Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
		mouseHover = {(float)mouseX, (float)mouseY, 1, 1};
		if (SDL_HasIntersectionF(&mouseHover, &loadgameBtn->Hitbox))
		{
			loadgameBtn->Update(true);
		}
		else
		{
			loadgameBtn->Update(false);
		}
		
		if (SDL_HasIntersectionF(&mouseHover, &newgameBtn->Hitbox))
		{
			newgameBtn->Update(true);
		}
		else
		{
			newgameBtn->Update(false);
		}
		
		switch (event.type)
		{
			case SDL_QUIT:
				isRunning = false;
				choice = -1;
			break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					//SDL_Log("Left mouse button pressed at (%d, %d)", event.button.x, event.button.y);
					if (SDL_HasIntersectionF(&mouseHover, &loadgameBtn->Hitbox))
					{
						choice = 1;
					}
					if (SDL_HasIntersectionF(&mouseHover, &newgameBtn->Hitbox))
					{
						choice = 2;
					}
				}
			break;
		}
		menuBg->Render(renderer);
		newgameBtn->Render(renderer);
		loadgameBtn->Render(renderer);
		SDL_RenderPresent(renderer);
	}
	delete menuBg;
	delete loadgameBtn;
	delete newgameBtn;
	if (!file.is_open()) {
		// File doesn't exist, so create it
		try{
			file.open("./savegame.txt", std::ios::out);
			if (file.is_open()) {
				file << 1;
				throw "File created new savefile successfully.";
			}
			else
			{
				throw "Failed to create the savefile.";
				exit(-1);
			}
		}
		catch(const char* e)
		{
			std::cout << e << "\n";
		}
	}
	try
	{
		file >> lvl;
		if (lvl == 0 || choice == 2)
		{
			throw "CREATING NEW SAVEFILE...";
		}
		if (lvl < 0 or lvl > 3)
		{
			throw "CORRUPTED SAVEFILE...CREATING NEW SAVEFILE";
		}
		std::cout << "LOADED LEVEL " << lvl << " SUCCESSFULLY\n";
	}
	catch (const char* e)
	{
		std::cout << e << "\n";
		file.close();
		file.open("./savegame.txt", std::ios::out | std::ios::trunc);
		lvl = 1;
		file << lvl;
	}
	player = new Player(Vector2(0.f, 0.f), Vector2(32, 32), "./Assets/Player/PlayerSprites.png", 3.f, 100, 300.0f);
	player->setTexture(renderer); 
	camera = new Camera(Vector2(0,150), Vector2(10,10));
	map = new Map(lvl, 30, 10, 3.f);
	map->Create(renderer);
}

void Game::handleEvents(){	
	// Manage events
	SDL_Event event; 
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_a)
		{
			keyState[event.key.keysym.sym] = true;
		}
		if (event.key.keysym.sym == SDLK_d)
		{
			keyState[event.key.keysym.sym] = true;
		}
		/*if (event.key.keysym.sym == SDLK_s)
		{
			camera->Position.y += 30;
		}*/
		if (event.key.keysym.sym == SDLK_k)
		{
			std::cout << player->Position << "\n";
		}
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			std::cout << "quit by keypress\n";
			isRunning = false;
		}
		if (event.key.keysym.sym == SDLK_w)
		{
			player->Jump();
			if (player->direction == 0)
			{
				player->animation = JUMP_L;
			}
			else
			{
				player->animation = JUMP_R;
			}
		}
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			player->Jump();
			if (player->direction == 0)
			{
				player->animation = JUMP_L;
			}
			else
			{
				player->animation = JUMP_R;
			}
		}
		break;
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d)
		{
			keyState[event.key.keysym.sym] = false;
			player->Velocity.x = 0;
		}
		break;
	};
}
void Game::update()
{

	time->Tick();
	player->animationFrame = time->currentTime / player->animConst[player->animation] % player->animTotalFrames[player->animation];
	if (player->Velocity.x == 0)
	{
		if (player->direction == 1)
		{
			player->animation = IDLE_R;
		}
		else
		{
			player->animation = IDLE_L;
		}
	}
	if (player->isGrounded == false)
	{
		if (player->direction == 0)
		{
			player->animation = JUMP_L;
		}
		else
		{
			player->animation = JUMP_R;
		}
	}
	if (keyState[SDLK_a])
	{
		player->Velocity.x = -player->speed * time->DeltaTime;
		if (player->isGrounded == true)
		{
			player->animation = RUN_L;
		}
		player->direction = 0;
	}
	if (keyState[SDLK_d])
	{
		player->Velocity.x = player->speed * time->DeltaTime;
		if (player->isGrounded == true)
		{
			player->animation = RUN_R;
		}
		player->direction = 1;
	}
	player->Velocity.y += player->maxFallSpeed;
	if (player->isGrounded == true)
	{
		player->jumpAmmt = 1;
		if (player->Velocity.y > 0)
		{
			player->Velocity.y = 0;
		}
	}
	player->UpdateCamera(camera);
	player->Position.x = player->Position.x + player->Velocity.x;
	player->Position.y = player->Position.y + player->Velocity.y;
	player->Update();
	map->Update(player);
	player->Update();
	if (player->Position.y < 0)
	{
		player->Position.y = 0;
	}
	if (player->Position.x < 0)
	{
		player->Position.x = 0;
	}
	if (player->Position.x > LEVEL_WIDTH - player->Dimensions.x * player->scale)
	{
		player->Position.x = LEVEL_WIDTH - player->Dimensions.x * player->scale;
	}
	
	if (map->portal != nullptr)
	{
		if (SDL_HasIntersectionF(&player->Hitbox, &map->portal->Hitbox))
		{
			if (lvl < 3)
			{
				delete map;
				map = nullptr;
				lvl++;
				map = new Map(lvl, 30, 10, 3);
				map->Create(renderer);
				player->Position.x = 0;
				player->Position.y = 661;
				file.close();
				file.open("./savegame.txt", std::ios::out | std::ios::trunc);
				file << lvl;
			}
			else
			{
				UiSprite* endgame = new UiSprite(Vector2(0, 0), Vector2(1280, 720), "./Assets/Ui/EndScreen.png");
				endgame->SetTexture(renderer);
				endgame->Render(renderer);
				SDL_RenderPresent(renderer);
				SDL_Delay(3000);
				isRunning = false;
				delete endgame;
			}
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->RenderBG(renderer, camera);
	player->Render(renderer, camera);
	//SET RENDERER DRAW COLOR TO RED FOR THINGS THAT DON T HAVE TEXURES (they are the same color as the background now) 
	// uncomment for debugging
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	map->Render(renderer, camera);
	//SET RENDERER DRAW COLOR TO BACKGROUND COLOR (DARK GREEN)
	SDL_SetRenderDrawColor(renderer, 3, 42, 50, 255);
	//UPDATE WINDOW
	SDL_RenderPresent(renderer);
}

void Game::cleanup()
{
	file.close();
	delete map;
	delete camera;
	delete time;
	delete player;
	player = nullptr;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit(); // Destroys all SDL_Related stuff
	std::cout << "Cleared Everything!\n";
}