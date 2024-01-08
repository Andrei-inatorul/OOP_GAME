#pragma once
#include "gameObject.h"
#include "Player.h"
class Platform :public gameObject
{
public:
	bool passed;
	Platform(Vector2 Position, Vector2 Dimensions, const char* spritePath, float scale);
	Platform(Vector2 Position, Vector2 Dimensions, const char* spritePath, float scale, bool solid);
	~Platform();
	void Update(gameObject* player);
};

