/*
 * Camera.cpp
 */

#include "Camera.h"

Camera::Camera(int width, int height):
	speed(0)
{
	SDL_Rect realcamera = {0, 0, width, height};
	frame = realcamera;
}

Camera::~Camera()
{
	
}