#include <SDL.h>
#include "Enemy.h"

Enemy::Enemy():Entity()
{
	this->Position = Vector2(0, 0);
	this->Dimensions = Vector2(64, 64);
	this->Velocity = 0;
	this->animation = MOVE_R;
	this->animationFrame = 0;
	this->patrolOffset = patrolOffset;
	this->SpawnPos = Vector2(0, 0);
	this->Velocity = 2.f;
	this->lastVel = Velocity;
	this->facing = 1;
	this->isAttacking = false;
	this->attackHitbox = {this->Position.x + this->Dimensions.x * scale , this->Position.y + 32 * scale , 64, 32};
}

Enemy::Enemy(Vector2 position, Vector2 dims, const char* spritePath,
	float scale, short hp, float patrolOffset)
	:Entity(position, dims, spritePath,scale, hp)
{
	this->isAttacking = false;
	this->animation = MOVE_R;
	this->animationFrame = 0;
	this->patrolOffset = patrolOffset;
	this->SpawnPos = position;
	this->Velocity = 2.f;
	this->facing = 1;
	this->lastVel = Velocity;
	this->attackHitbox = {this->Position.x + this->Dimensions.x * scale , this->Position.y + 32 * scale , 64, 32};
}

void Enemy::Update(gameObject* go)
{
	float attackLen = 20;
	if (Velocity != 0)
	{
		lastVel = Velocity;
	}
	if (isAttacking == true)
	{
		this->Velocity = 0;
	}
	else
	{
		this->Velocity = lastVel;
	}
	
	if (this->Position.x > SpawnPos.x + patrolOffset || this->Position.x < SpawnPos.x - patrolOffset) // change direction of enemy
	{
		facing = !facing;
		Velocity = -Velocity;
	}
	this->Position.x += Velocity;	// move enemy
	this->Hitbox.x = this->Position.x;	//update hitbox
	this->Hitbox.y = this->Position.y;	//  same here
	if (this->facing == 1 && isAttacking == false)	// set animations;
	{
		this->animation = MOVE_R;
		this->attackHitbox = {this->Position.x + this->Dimensions.x * this->scale , this->Position.y + 32 * this->scale , 32*this->scale, attackLen* this->scale};
	}
	if (this->facing == 0 && isAttacking == false)
	{
		this->animation = MOVE_L;
		this->attackHitbox = {this->Position.x - 32 * this->scale, this->Position.y + 32 * this->scale, 32*this->scale, attackLen* this->scale};
	}
	delay++; // coudn't use time as a parameter so this will do;
	if (SDL_HasIntersectionF(&this->attackHitbox, &go->Hitbox) == false) // reset if player out of attack range
	{
		isAttacking = false;
		this->animationFrame = 0;
	}
	if (isAttacking == true && this->animationFrame == this->animTotalFrames[this->animation]-1)// reset if already attacked
	{																			// kind of hack to change between animations
		go->Position = Vector2(0, 611);
		this->animationFrame = 0;
		isAttacking = false;
		// here the attack animation ends so if player is in range kill him
		// play
		
	}
	this->animationFrame = this->delay / this->animConst[this->animation] % this->animTotalFrames[this->animation]; // choose the animation frame pretty self explainatory
	if (this->delay % 50 == 0 && SDL_HasIntersectionF(&this->attackHitbox, &go->Hitbox))	
	{
		this->animationFrame = 0;
		isAttacking = true;		// if enough time has passed since last attack and player is in attack range
		if (this->facing == 1)			// we attack and set the animation for it
		{
			this->animation = ATK_L;
		}
		else
		{
			this->animation = ATK_R;
		}
	}
}

void Enemy::Render(SDL_Renderer* renderer, Camera* camera)
{
	if (renderer != NULL)
	{
		if (this->texture != nullptr)
		{
			SDL_Rect src = {64 * animationFrame, 64 * animation, this->Dimensions.x, this->Dimensions.y};
			SDL_FRect dest = {this->Position.x - camera->Position.x, this->Position.y - camera->Position.y, src.w * this->scale, src.h * this->scale};
			if (SDL_RenderCopyF(renderer, this->texture, &src, &dest) != 0)
			{
				std::cout << "Cannot render Texture!";
				exit;
			}
			//Debug purposes
			//SDL_FRect temp = {this->attackHitbox.x - camera->Position.x, this->attackHitbox.y - camera->Position.y, this->attackHitbox.w, this->attackHitbox.h};
			//SDL_RenderFillRectF(renderer, &temp);
		}
		else
		{
			SDL_FRect temp = this->Hitbox;
			temp.x = temp.x - camera->Position.x;
			temp.y = temp.y - camera->Position.y;
			SDL_RenderDrawRectF(renderer, &temp);
		}
	}
	else
	{
		std::cout << "Cannot render gameobject, renderer and texture can't be NULL!";
	}
}

