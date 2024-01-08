#include <iostream>
#include "Entity.h"

Entity::Entity():gameObject()
{
	Position = Vector2(0,0);
	Dimensions = Vector2(0,0);
	spritePath = NULL;
	texture = nullptr;
	scale = 1;
	hp = 0;
	maxhp = 0;
	Velocity = Vector2(0, 0);
}

Entity::Entity(Vector2 position, Vector2 dims, const SDL_FRect Collider, const char* spritePath, float scale, short hp)
	:gameObject(position, dims, Collider, spritePath, scale)
{
	Velocity = Vector2(0, 0);
	this->hp = hp;
	maxhp = hp;
}

Entity::Entity(Vector2 position, Vector2 dims, const char* spritePath, float scale, short hp)
	:gameObject(position, dims, spritePath, scale)
{
	Velocity = Vector2(0, 0);
	this->hp = hp;
	maxhp = hp;
}

void Entity::checkCollision(gameObject* go)
{
	if (go->isSolid == true)
	{
		if (SDL_HasIntersectionF(&Hitbox, &go->Hitbox))
		{
			float overlapX = std::min(Hitbox.x + Hitbox.w, go->Hitbox.x + go->Hitbox.w) - std::max(Hitbox.x, go->Hitbox.x);
			float overlapY = std::min(Hitbox.y + Hitbox.h, go->Hitbox.y + go->Hitbox.h) - std::max(Hitbox.y, go->Hitbox.y);
			if (overlapX < overlapY)
			{
				if (Hitbox.x < go->Hitbox.x)
				{
					Hitbox.x = go->Hitbox.x - Hitbox.w;
				}
				else
				{
					Hitbox.x = go->Hitbox.x + go->Hitbox.w;
				}
				Position.x = Hitbox.x - 6 * scale;
			}
			else
			{
				if (Hitbox.y < go->Hitbox.y)
				{
					Hitbox.y = go->Hitbox.y - Hitbox.h;
				}
				else
				{
					Hitbox.y = go->Hitbox.y + go->Hitbox.h;
				}
				Position.y = Hitbox.y - 0 * scale;
			}
		}
	}
}

void Entity::Damage(int ammount)
{
	if (hp > 0)
	{
		hp = hp - ammount;
	}
	if (hp < 0)
	{
		hp = 0;
	}
}

int Entity::getHp()
{
	return hp;
}