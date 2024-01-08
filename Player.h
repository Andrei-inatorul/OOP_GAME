#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Time.h"
enum player_animations{ IDLE_R = 0, IDLE_L, RUN_R, RUN_L, JUMP_R, JUMP_L, TELEPORT, DIE, ATTACK_R, ATTACK_L };
class Player :public Entity
{
public:
	bool direction;
	player_animations animation;
	short animationFrame;
	const short animTotalFrames[10] ={2, 2, 8, 8, 8, 8, 3, 8, 8, 8};
	const short animConst[10] ={150, 150, 100, 100, 150, 150, 100, 100, 100, 100};
	Player();
	Player(Vector2 Position, Vector2 Dimensions, const SDL_FRect Collider,
		const char* spritePath, float scale, short hp, float speed);
	Player(Vector2 Position, Vector2 Dimensions, const char* spritePath, float scale, short hp, float speed);
	void Jump();
	float speed;
	void Update();
	void checkGroundCollision(gameObject* go);
	void checkGroundCollision(gameObject** go, size_t arrsize);
	SDL_FRect groundCheck;
	short maxFallSpeed; // == gravity
//private:
	void Render(SDL_Renderer* renderer, Camera* camera);
	bool isGrounded; 
	short jumpAmmt;
	int jumpPower;
	short maxJumpPower;
	~Player();
};
