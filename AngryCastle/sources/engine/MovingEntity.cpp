/*
 * MovingEntity.cpp
 *
 */

#include "MovingEntity.h"

MovingEntity::MovingEntity(Rectangle hitbox, float speed):
	Entity(hitbox), boundbox(hitbox),
	acceleration(0.8), stoppedThreshold(acceleration/3),
	velocity_x(0), velocity_y(0),
	targetVx(0), in_air(false), speed(speed) {
}

MovingEntity::~MovingEntity() {}

void MovingEntity::update() {
	velocity_x += ((targetVx - velocity_x) * acceleration) * 0.16667f;
	// velocity_x = (targetVx * acceleration) + ((1 - acceleration) * velocity_x) * 0.166667f;

	if (fabs(velocity_x) > speed) {
		velocity_x = (velocity_x > 0) ? speed : -speed;
	}

	if (fabs(velocity_x) < stoppedThreshold) {
		velocity_x = 0;
	}

	boundbox.x += floorf(velocity_x);
	targetVx = 0;
}

// NOTE(jouni): Do we even need this thing anymore?
void MovingEntity::commitMovement() {
	hitbox.x = boundbox.x;
	hitbox.y = boundbox.y;
}

void MovingEntity::left() {
	targetVx = -(speed * acceleration);
	facing_direction = FACING_LEFT;
}

void MovingEntity::right() {
	targetVx = (speed * acceleration);
	facing_direction = FACING_RIGHT;
}

void MovingEntity::jump() {
	if (in_air == false) {
		velocity_y -= 5;
		in_air = true;
	}
}