#pragma once
#include "UiElement.h"
class Button :public UiElement
{
public:
	Button(Vector2 Position, Vector2 Dimensions);
	Button(Vector2 Position, Vector2 Dimensions, const char* spritepath);
	void SetTexture(SDL_Renderer* renderer);
	~Button();
	void Render(SDL_Renderer* renderer);
	void Update(bool isOn);
};

