/*
 * MovingEntity.cpp
 *
 */

#include "MovingEntity.h"

MovingEntity::MovingEntity(int x, int y, int w, int h, float speed, SDL_Rect hitbox) :
	Entity(x, y, w, h, hitbox),
	acceleration(speed), stoppedThreshold(acceleration/10),
	targetVx(0) {
}

MovingEntity::~MovingEntity() {
}

void MovingEntity::update(float dt) {
	velocity_x = (acceleration * targetVx) + ((1 - acceleration) * acceleration) * (dt/1000.f);
	
	if (fabs(this->velocity_x) < stoppedThreshold) {
		velocity_x = 0;
	}

	desiredX = x + velocity_x;
	targetVx = 0;
}

void MovingEntity::commitMovement() {
	setPosition(desiredX, desiredY);
}

void MovingEntity::left() {
	targetVx = (-1 * acceleration);
}

void MovingEntity::right() {
	targetVx = acceleration;
}

void MovingEntity::jump() {
	if (in_air == false) {
		velocity_y -= 5;
		in_air = true;
	}
}