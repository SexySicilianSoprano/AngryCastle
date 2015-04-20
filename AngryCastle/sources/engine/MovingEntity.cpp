/*
 * MovingEntity.cpp
 *
 */

#include "MovingEntity.h"

MovingEntity::MovingEntity(int x, int y, int w, int h, float acceleration, SDL_Rect hitbox) :
	Entity(x, y, w, h, hitbox),
	acceleration(acceleration), stoppedThreshold(acceleration/2),
	targetVx(0) {
}

MovingEntity::~MovingEntity() {
}

void MovingEntity::update(float dt) {
	velocity_x += ((targetVx - velocity_x) * acceleration ) * dt / 100.0f;

	if (fabs(velocity_x) <= stoppedThreshold) {
		velocity_x = 0;
	}

	desiredX = x + roundf(velocity_x * 1) / 1;
	targetVx = 0;
}

void MovingEntity::commitMovement() {
	setPosition(desiredX, desiredY);
}

void MovingEntity::left() {
	targetVx = -3;
	facing_direction = FACING_LEFT;
}

void MovingEntity::right() {
	targetVx = 3;
	facing_direction = FACING_RIGHT;
}

void MovingEntity::jump() {
	if (in_air == false) {
		velocity_y -= 5;
		in_air = true;
	}
}