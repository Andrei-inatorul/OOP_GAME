#pragma once
#include "UiElement.h"
class UiSprite : public UiElement
{
public:
	UiSprite(Vector2 Position, Vector2 Dimensions, const char* spritepath);
	void SetTexture(SDL_Renderer* renderer);
	void Render(SDL_Renderer* renderer);
	~UiSprite();
};

