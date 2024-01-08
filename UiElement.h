#pragma once
#include <SDL.h>
#include "Vector2.h"

class UiElement
{
protected:
	SDL_Texture* texture;
	const char* spritepath;
public:
	Vector2 Position;
	Vector2 Dimensions;
	SDL_FRect Hitbox;
	virtual void SetTexture(SDL_Renderer* renderer) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
};

