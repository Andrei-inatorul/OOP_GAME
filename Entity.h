#pragma once
#include "gameObject.h"

class Entity:public gameObject
{
public:
	Entity();
	Entity(Vector2 position, Vector2 dims,const SDL_FRect Collider,
		const char* spritePath,float scale, short hp);
	Entity(Vector2 position, Vector2 dims, const char* spritePath, float scale, short hp);
	Vector2 Velocity;
	void checkCollision(gameObject* go);
	void checkCollision(Entity* go);
	void checkCollision(SDL_FRect go);
	void Update();
	void Damage(int ammount);
	void Heal(int ammount);
	void setHp(int ammount);
	int getHp();
protected:
	enum states;
	int hp;
	int maxhp;
};

