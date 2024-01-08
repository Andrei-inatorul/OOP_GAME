#pragma once
#include "Vector2.h"
 
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int LEVEL_WIDTH = 2880;
const int LEVEL_HEIGHT = 1100;

class Camera
{
public:
	Vector2 Position;
	Vector2 Offset;
	Vector2 Damping;
	Camera();
	Camera(Vector2 Pos, Vector2 Off, Vector2 Dam);
	Camera(Vector2 Off, Vector2 Dam);
	~Camera();
};

