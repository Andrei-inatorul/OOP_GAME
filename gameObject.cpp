#include <SDL.h>
#include <SDL_image.h>
#include "gameObject.h"
#include "Camera.h"


float yspeed = 7.0f;
float xspeed = 4.3f;

gameObject::gameObject()
{
	Position = Vector2(0, 0);
	Dimensions = Vector2(0, 0);
	spritePath = nullptr;
	texture = nullptr;
	scale = 1;
	Hitbox = {0, 0, 0, 0};
}

gameObject::gameObject(Vector2 position, Vector2 dims, SDL_FRect Collider , const char* spritePath, float scale, bool isSolid)
{
	this->Position = position;
	this->Dimensions = dims;
	this->Hitbox = Collider;
	this->spritePath = spritePath;
	this->scale = scale;
	this->isSolid = isSolid;
	texture = nullptr;
}

gameObject::gameObject(Vector2 position, Vector2 dims, const char* spritePath, float scale, bool isSolid)
{
	this->Position = position;
	this->Dimensions = dims;
	this->Hitbox = {position.x, position.y, dims.x*scale, dims.y*scale};
	this->spritePath = spritePath;
	this->scale = scale;
	texture = nullptr;
	this->isSolid = isSolid;
}

gameObject::gameObject(Vector2 position, Vector2 dims, SDL_FRect Collider, const char* spritePath, float scale)
{
	this->Position = position;
	this->Dimensions = dims;
	this->Hitbox = Collider;
	this->spritePath = spritePath;
	this->scale = scale;
	texture = nullptr;
	isSolid = true;
}

gameObject::gameObject(Vector2 position, Vector2 dims, const char* spritePath, float scale)
{
	this->Position = position;
	this->Dimensions = dims;
	this->Hitbox = {position.x, position.y, dims.x*scale, dims.y*scale};
	this->spritePath = spritePath;
	this->scale = scale;
	texture = nullptr;
	this->isSolid = true;                        
}

void gameObject::setTexture(SDL_Renderer* renderer)
{
	if (this->spritePath != NULL)
	{
		SDL_Surface* tmpSurface = nullptr;
		tmpSurface = IMG_Load(this->spritePath);
		if (tmpSurface == nullptr)
		{
			std::cerr << "Nu se poate dechide fisierul texturii localizat la: " << spritePath << "\n";
			exit(EXIT_FAILURE);
		}
		texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}
}

SDL_Texture* gameObject::getTexture()
{
	return texture;
}

void gameObject::Render(SDL_Renderer* renderer)
{
	if (renderer != NULL)
	{
		if (texture != nullptr)
		{
			SDL_Rect src = {0, 0, Dimensions.x, Dimensions.y};
			SDL_FRect dest = {Position.x, Position.y, src.w * scale, src.h * scale};
			if (SDL_RenderCopyF(renderer, texture, &src, &dest) != 0)
			{
				std::cout << "Cannot Load Texture!!";
				exit;
			}
		}
		else
		{
			SDL_RenderDrawRectF(renderer, &Hitbox);
		}
	}
	else
	{
		std::cout << "Cannot render gameobject, renderer and texture can't be NULL!";
	}
}

void gameObject::UpdateCamera(Camera* camera)
{
	if (camera->Position.x != this->Position.x - SCREEN_WIDTH/2 + this->Dimensions.x)
	{
		if (camera->Position.x > this->Position.x - SCREEN_WIDTH / 2 + this->Dimensions.x)
		{
			camera->Position.x -= xspeed;
		}
		if (camera->Position.x < this->Position.x - SCREEN_WIDTH / 2 + this->Dimensions.x)
		{
			camera->Position.x += xspeed;
		}
		if (xspeed <= 4.8f)
		{
			xspeed += 0.1;
		}
		else
		{
			xspeed = 4.3f;
		}
	}
	if (camera->Position.y != this->Position.y - SCREEN_HEIGHT / 2 + this->Dimensions.y)
	{
		if (camera->Position.y > this->Position.y - SCREEN_HEIGHT / 2 + this->Dimensions.y - camera->Offset.y)
		{
			camera->Position.y -= yspeed;
			
		}
		if (camera->Position.y < this->Position.y - SCREEN_HEIGHT / 2 + this->Dimensions.y)
		{
			camera->Position.y += yspeed;
		}
		if (yspeed <= 10)
		{
			yspeed += 0.1f;
		}
		else
		{
			yspeed = 7.0f;
		}
	}
	//camera->Position.y = this->Position.y + this->Dimensions.y - SCREEN_HEIGHT / 2;
	if (camera->Position.x + SCREEN_WIDTH > LEVEL_WIDTH)
	{
		camera->Position.x = LEVEL_WIDTH - SCREEN_WIDTH;
	}
	if (camera->Position.y + SCREEN_HEIGHT > LEVEL_HEIGHT)
	{
		camera->Position.y = LEVEL_HEIGHT - SCREEN_HEIGHT;
	}
	if (camera->Position.x < 0)
	{
		camera->Position.x = 0;
	}
	if (camera->Position.x < 0)
	{
		camera->Position.x = 0;
	}
	if (camera->Position.y < 0)
	{
		camera->Position.y = 0;
	}
	if (this->Position.x < camera->Position.x || this->Position.x > camera->Position.x + LEVEL_WIDTH)
	{
		camera->Position.x = this->Position.x;
	}
}

void gameObject::Update(gameObject* player)
{

}

void gameObject::Render(SDL_Renderer* renderer, Camera* camera)
{
	if (renderer != NULL)
	{
		if (this->texture != nullptr)
		{
			SDL_Rect src = {0, 0, this->Dimensions.x, this->Dimensions.y};
			SDL_FRect dest = {this->Position.x - camera->Position.x, this->Position.y - camera->Position.y, src.w * this->scale, src.h * this->scale};
			if (SDL_RenderCopyF(renderer, this->texture, &src, &dest) != 0)
			{
				std::cout << "Cannot render Texture!";
				exit;
			}
		}
		else
		{
			SDL_FRect temp = this->Hitbox;
			temp.x = temp.x - camera->Position.x;
			temp.y = temp.y - camera->Position.y;
			SDL_RenderDrawRectF(renderer, &temp);
		}
	}
	else
	{
		std::cout << "Cannot render gameobject, renderer and texture can't be NULL!";
	}
}
