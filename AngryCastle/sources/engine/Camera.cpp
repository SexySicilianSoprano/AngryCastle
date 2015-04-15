/*
 * Camera.cpp
 */

#include "Camera.h"

Camera::Camera(int width, int height):
	locked_entity(nullptr)
{
	SDL_Rect realcamera = {0, 0, width, height};
	frame = realcamera;
}

Camera::~Camera()
{
	
}

void Camera::lock(Entity *entity) {
	locked_entity = entity;
	frame.x = entity->getX() - frame.w/2;
	frame.y = entity->getY() - frame.h/2;
}

void Camera::update(int levelWidth, int levelHeight) {
	frame.x = locked_entity->getX() - frame.w/2;
	frame.y = locked_entity->getY() - frame.h/2;

	if (frame.x < 0) {
		frame.x = 0;
	}

	if (frame.y < 0) {
		frame.y = 0;
	}

	if (frame.x + frame.w > levelWidth) {
		frame.x = levelWidth - frame.w;
	}

	if (frame.y + frame.h > levelHeight) {
		frame.y = levelHeight - frame.h;
	}
}