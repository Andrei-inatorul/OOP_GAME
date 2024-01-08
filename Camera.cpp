#include "Camera.h"



Camera::Camera()
{
	Position = Vector2(0,0);
	Offset = Vector2(0,0);
}

Camera::Camera(Vector2 Pos, Vector2 Off, Vector2 Dam)
{
	Position = Pos;
	Offset = Off;
	Damping = Dam;
}

Camera::Camera(Vector2 Off, Vector2 Dam)
{
	Offset = Off;
	Damping = Dam;
}

Camera::~Camera()
{
	Position = Vector2();
	Offset = Vector2();
	Damping = Vector2();
}
