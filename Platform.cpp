#include "Platform.h"

Platform::Platform(Vector2 Position, Vector2 Dimensions, const char* spritePath, float scale)
	:gameObject(Position, Dimensions, spritePath, scale)
{
}

Platform::Platform(Vector2 Position, Vector2 Dimensions, const char* spritePath, float scale, bool solid)
	:gameObject(Position, Dimensions, spritePath, scale, solid)
{
}


Platform::~Platform()
{
}

void Platform::Update(gameObject* player)
{
	if (player->Position.y + player->Dimensions.y < this->Position.y)
	{
		isSolid = true;
	}
	else
	{
		isSolid = false;
	}
}
