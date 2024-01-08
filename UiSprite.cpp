#include <SDL_image.h>
#include "UiSprite.h"

UiSprite::UiSprite(Vector2 Position, Vector2 Dimensions, const char* spritepath)
{
	this->Position = Position;
	this->Dimensions = Dimensions;
	this->spritepath = spritepath;
}

void UiSprite::SetTexture(SDL_Renderer* renderer)
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

void UiSprite::Render(SDL_Renderer* renderer)
{
	if (renderer != NULL && this->texture != nullptr)
	{
		SDL_Rect src = {0, 0 , this->Dimensions.x, this->Dimensions.y};
		SDL_FRect dest = {this->Position.x, this->Position.y, src.w, src.h};
		if (SDL_RenderCopyF(renderer, this->texture, &src, &dest) != 0)
		{
			std::cout << "rendering not working!";
			exit;
		}
	}
	else
	{
		std::cout << "Cannot render sprite, renderer and texture can't be NULL!";
	}
}

UiSprite::~UiSprite()
{

}

