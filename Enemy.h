#pragma once

#include "Entity.h"

enum enemyAnimations{ATK_L=0, ATK_R, MOVE_R, MOVE_L};
class Enemy : public Entity
{
	bool isAttacking;
	float patrolOffset;
	Vector2 SpawnPos;
	bool facing;
	float Velocity;
	SDL_FRect attackHitbox;
	unsigned short delay;
	enemyAnimations animation;
	short animationFrame;
	float lastVel;
	const short animTotalFrames[4] = {6, 6, 5, 5};
	const short animConst[4] = {13, 13, 13, 13};
public:
	Enemy();
	Enemy(Vector2 position, Vector2 dims, const char* spritePath, float scale, short hp, float patrolOffset);
	~Enemy();
	void Update(gameObject* go);
	void Render(SDL_Renderer* renderer, Camera* camera);
};

