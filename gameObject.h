#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Camera.h"

class gameObject
{
public:
	bool isSolid;
	gameObject();
	gameObject(Vector2 position, Vector2 dims, SDL_FRect Collider, const char* spritePath, float scale, bool isSolid);
	gameObject(Vector2 position, Vector2 dims, const char* spritePath, float scale, bool isSolid);
	gameObject(Vector2 position, Vector2 dims, const SDL_FRect Collider, const char* spritePath, float scale);
	gameObject(Vector2 position, Vector2 dims, const char* spritePath, float scale);
	~gameObject()
	{
		if (texture != nullptr)
		{
			SDL_DestroyTexture(texture);
			texture = nullptr;
		}
	}
	void setTexture(SDL_Renderer* renderer);
	SDL_Texture* getTexture();
	Vector2 Position;
	Vector2 Dimensions;
	SDL_FRect Hitbox;
	//void Render(SDL_Renderer* renderer);
	void UpdateCamera(Camera* camera);
	virtual void Update(gameObject* go);
	void Render(SDL_Renderer* renderer, Camera* camera);
	void Render(SDL_Renderer* renderer);
	float scale;
protected:
	SDL_Texture* texture;
	const char* spritePath;
};

