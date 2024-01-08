#pragma once
#include "gameObject.h"

class Spike :public gameObject
{
public:
	Spike(Vector2 position, Vector2 dims, const char* spritePath, float scale, bool isSolid);
	void Update(gameObject* go);
};

