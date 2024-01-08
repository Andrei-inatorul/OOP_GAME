#include "Spike.h"

Spike::Spike(Vector2 position, Vector2 dims, const char* spritePath, float scale, bool isSolid)
	:gameObject(position, dims, spritePath, scale, isSolid)
{
	Hitbox = {position.x, position.y + 15*scale, dims.x*scale, dims.y-15};
}

void Spike::Update(gameObject* go)
{
	if (SDL_HasIntersectionF(&go->Hitbox, &this->Hitbox))
	{
		go->Position.x = 0;
		go->Position.y = 611;
	}
}