#include "Button.h"
#include <SDL_image.h>

Button::Button(Vector2 Position, Vector2 Dimensions)
{
	this->Position = Position;
	this->Dimensions = Dimensions;
	this->spritepath = NULL;
}

Button::Button(Vector2 Position, Vector2 Dimensions, const char* spritepath)
{
	this->Position = Position;
	this->Dimensions = Dimensions;
	this->spritepath = spritepath;
	this->Hitbox = {Position.x, Position.y, Dimensions.x, Dimensions.y};
}

void Button::SetTexture(SDL_Renderer* renderer)
{
	if (this->spritepath != NULL)
	{
		SDL_Surface* tmpSurface = nullptr;
		tmpSurface = IMG_Load(this->spritepath);
		if (tmpSurface == nullptr)
		{
			std::cerr << "Nu se poate dechide fisierul texturii localizat la: " << this->spritepath << "\n";
			exit(EXIT_FAILURE);
		}
		texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}
}

Button::~Button()
{
}

void Button::Render(SDL_Renderer* renderer)
{
	if (renderer != NULL)
	{
		if (this->texture != nullptr)
		{
			SDL_Rect src = {0, 0, this->Dimensions.x, this->Dimensions.y};
			SDL_FRect dest = {this->Position.x, this->Position.y, src.w, src.h};
			if (SDL_RenderCopyF(renderer, this->texture, &src, &dest) != 0)
			{
				std::cout << "not working!";
				exit;
			}
		}
		else
		{
			SDL_RenderFillRectF(renderer, &this->Hitbox);
		}
	}
	else
	{
		std::cout << "Cannot render button, renderer and texture can't be NULL!";
	}
}

void Button::Update(bool isOn)
{
	if (isOn)
	{
		SDL_SetTextureAlphaMod(texture, 128);
	}
	else
	{
		SDL_SetTextureAlphaMod(texture, 255);
	}
}

