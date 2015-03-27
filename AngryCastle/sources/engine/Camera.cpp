/*
 * Camera.cpp
 */

#include "Camera.h"

Camera::Camera(int width, int height):
	entity(nullptr)
{
	SDL_Rect realcamera = {0, 0, width, height};
	frame = realcamera;
}

Camera::~Camera()
{
	
}