#include "Player.h"

void Player::Jump()
{
	if (jumpAmmt > 0)
	{
		jumpAmmt--;
		Velocity.y = -(jumpPower);
	}
}

Player::Player():Entity()
{
	Position = Vector2(0, 0);
	Dimensions = Vector2(0, 0);
	spritePath = NULL;
	texture = nullptr;
	scale = 1;
	hp = 0;
	maxhp = 0;
	jumpAmmt = 2;
	maxFallSpeed = 10;
	jumpPower = 30;
	isGrounded = false;
	speed = 300;
	groundCheck = {0,0,0,0};
	animation = IDLE_R;
}

Player::Player(
	Vector2 Position,
	Vector2 Dimensions,
	const SDL_FRect Collider,
	const char* spritePath,
	float scale,
	short hp,
	float speed)
	:Entity(Position, Dimensions, Collider, spritePath, scale, hp), speed(speed)
{
	jumpAmmt = 2;
	isGrounded = false;
	Velocity = Vector2(0, 0);
	maxFallSpeed = 1;
	jumpPower = 20;
	Hitbox = {this->Position.x + 6 * scale, this->Position.y + 0 *scale, 18.f * scale, 31.f * scale};
	groundCheck = {this->Position.x + 10 * scale, this->Position.y + 30 * scale, 11.f * scale, 3.f * scale};
	animation = IDLE_R;
	animationFrame = 0;
	direction = 1;
}

Player::Player(
	Vector2 Position,
	Vector2 Dimensions,
	const char* spritePath,
	float scale,
	short hp,
	float speed)
	:Entity(Position, Dimensions, spritePath, scale, hp), speed(speed)
{	
	jumpAmmt = 2;
	isGrounded = false;
	Velocity = Vector2(0, 0);
	maxFallSpeed = 1;
	jumpPower = 20;
	animation = IDLE_R;
	animationFrame = 0;
	Hitbox = {this->Position.x + 6 * scale, this->Position.y + 0 * scale, 18.f * scale, 31.f * scale};
	groundCheck = {this->Position.x + 10 * scale, this->Position.y + 30 * scale, 11.f * scale, 3.f * scale};
	direction = 1;
}

void Player::Update()
{
	Hitbox = {this->Position.x + 6 * scale, this->Position.y + 0 * scale, 18.f *scale, 31.0f * scale};
	groundCheck = {this->Position.x + 10 * scale, this->Position.y + 30 * scale, 11.f * scale, 3.f * scale};
}

void Player::checkGroundCollision(gameObject* go)
{
	isGrounded = SDL_HasIntersectionF(&groundCheck, &go->Hitbox);
}

void Player::checkGroundCollision(gameObject** go, size_t arrsize)
{
	int i;
	bool check = false;
	for (i = 0; i < arrsize; ++i)
	{
		if (go[i] != nullptr)
		{
			if (go[i]->isSolid == true)
			{
				if (SDL_HasIntersectionF(&groundCheck, &go[i]->Hitbox) == 1)
					check = true;
			}
		}
	}
	isGrounded = check;
}

void Player::Render(SDL_Renderer* renderer, Camera* camera)
{
	if (renderer != NULL)
	{
		if (this->texture != nullptr)
		{
			SDL_Rect src = {Dimensions.x * animationFrame, Dimensions.x * animation, this->Dimensions.x, this->Dimensions.y};
			SDL_FRect dest = {this->Position.x - camera->Position.x, this->Position.y - camera->Position.y, src.w * this->scale, src.h * this->scale};
			if (SDL_RenderCopyF(renderer, this->texture, &src, &dest) != 0)
			{
				std::cout << "not working!";
				exit;
			}
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

Player::~Player()
{
	
}
