#include <SDL_image.h>
#include "Map.h"
#include "Spike.h"
#include "Enemy.h"

Map::Map(int level, int sizeX, int sizeY, float scale)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->level = level;
	this->scale = scale;
	switch (level)
	{
	case 1:
	{
		for (int i = 0; i < sizeY; ++i)
		{
			for (int j = 0; j < sizeX; ++j)
			{
				map[i][j] = Map1[i][j];
			}
		}
		this->spritePath = "./Assets/Maps/Map1Bg.png";
		break;
	}
	case 2:
	{
		for (int i = 0; i < sizeY; ++i)
		{
			for (int j = 0; j < sizeX; ++j)
			{
				map[i][j] = Map2[i][j];
			}
		}
		this->spritePath = "./Assets/Maps/Map1Bg.png";
		break;
	}
	case 3:
	{
		for (int i = 0; i < sizeY; ++i)
		{
			for (int j = 0; j < sizeX; ++j)
			{
				map[i][j] = Map3[i][j];
			}
		}
		this->spritePath = "./Assets/Maps/Map1Bg.png";
		break;
	default:
		for (int i = 0; i < sizeY; ++i)
		{
			for (int j = 0; j < sizeX; ++j)
			{
				map[i][j] = 0;
			}
		}
		break;
	}
	}
	objects = nullptr;
	background = new gameObject(Vector2(0, 0), Vector2(2880, 960), this->spritePath, 1, false);
	this->portal = nullptr;
}

void Map::Create(SDL_Renderer* renderer)
{
	objects = new gameObject*[sizeX * sizeY];
	int i, j, k = 0;
	int offset = 3*32;
	short treeOffset = 192;
	for (i = 0; i < sizeY; ++i)
	{
		for (j = 0; j < sizeX; ++j)
		{
			switch (map[i][j])
			{
			case 1:
				objects[k] = new gameObject(Vector2(j * 32 * scale, offset+i* 32 * scale), Vector2(32, 32), "./Assets/Maps/ground1.png", scale);
				objects[k]->setTexture(renderer);
				break;
			case 2:
				objects[k] = new gameObject(Vector2(j * 32 * scale, offset+i * 32 * scale), Vector2(32, 32), "./Assets/Maps/grass1.png", scale, false);
				objects[k]->setTexture(renderer);
				break;
			case 3:
				objects[k] = new Platform(Vector2(j * 32 * scale, offset + i * 32 * scale), Vector2(32, 12), "./Assets/Maps/ground1.png", 3, false);
				objects[k]->setTexture(renderer);
				break;
			case 4:
				objects[k] = new Spike(Vector2(j * 32 * scale, offset + i * 32 * scale), Vector2(32, 32), "./Assets/Maps/spikes3.png", scale, false);
				objects[k]->setTexture(renderer);
				break;
			case 5:
				objects[k] = new gameObject(Vector2(j * 32 * scale, offset+i * 32 * scale), Vector2(32, 32), NULL, scale, false);
				portal = objects[k];
				break;
			case 6:
				objects[k] = new gameObject(Vector2(j * 32 * scale - treeOffset + 32, offset + i * 32 * scale - treeOffset), Vector2(64, 64), "./Assets/Maps/TreePortal.png", scale * 2, false);
				objects[k]->setTexture(renderer);
				break;
			case 7: 
				objects[k] = new gameObject(Vector2(j * 32 * scale, offset + i * 32 * scale), Vector2(32, 32), "./Assets/Maps/pisicutaaa.png", scale, false);
				objects[k]->setTexture(renderer);
				portal = objects[k];
				break;
			case 8:
				objects[k] = new Enemy(Vector2(j * 32 * scale, offset + i * 32 * scale - 32*scale), Vector2(64, 64), "./Assets/Maps/Sprout.png", scale, 100, 300);
				objects[k]->setTexture(renderer);
				break;
			default:
				objects[k] = nullptr;
				break;
			}
			k++;
		}
	}
}

void Map::Update(Player* player)
{
	int i, j, k = 0;
	player->checkGroundCollision(objects, sizeX*sizeY);
	for (i = 0; i < sizeY; ++i)
	{
		for (j = 0; j < sizeX; ++j)
		{
			if (objects[k] != nullptr)
			{	
				player->checkCollision(objects[k]);
				objects[k]->Update(player);
			}
			k++;
		}
	}
}

void Map::Render(SDL_Renderer* renderer, Camera* camera)
{
	int i, j, k=0;
	k = sizeX * sizeY - 1;
	for (i = k; i > 0; i--)
	{
		if (objects[i] != nullptr)
		{
			objects[i]->Render(renderer, camera);
		}
	}
}

void Map::RenderBG(SDL_Renderer* renderer, Camera* camera)
{
	
	if (background->getTexture() == nullptr)
	{
		background->setTexture(renderer);
	}
	background->Render(renderer, camera);
}

void Map::Render(SDL_Renderer* renderer)
{
	int i, j, k = 0;
	for (i = 0; i < sizeY; ++i)
	{
		for (j = 0; j < sizeX; ++j)
		{
			if (objects[k] != nullptr)
			{
				objects[k]->setTexture(renderer);
				objects[k]->Render(renderer);
			}
			k++;
		}
	}
}


Map::~Map()
{
	if (background != nullptr)
	{
		delete background;
	}
	for (int i = 0; i < sizeX * sizeY; ++i)
	{
		if (objects[i] != nullptr)
		{
			delete objects[i];
		}
	}
	delete[] objects;
}
