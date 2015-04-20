/*
 * MovingEntity.cpp
 *
 */

#include "MovingEntity.h"

MovingEntity::MovingEntity(Rectangle hitbox, float speed):
	Entity(hitbox), boundbox(hitbox),
	acceleration(0.8), stoppedThreshold(acceleration/2),
	velocity_x(0), velocity_y(0),
	targetVx(0), in_air(false) {
}

MovingEntity::~MovingEntity() {}

void MovingEntity::update(float dt) {
	velocity_x += targetVx; //((targetVx - velocity_x) * acceleration ) * dt / 100.0f;

	if (fabs(velocity_x) <= stoppedThreshold) {
		velocity_x = 0;
	}

	if (fabs(velocity_x) > targetVx) {
		velocity_x = targetVx;
	}

	printf("Velocity X: %f\n", velocity_x);

	boundbox.x += velocity_x;
	targetVx = 0;
}

// NOTE(jouni): Do we even need this thing anymore?
void MovingEntity::commitMovement() {
	printf("hitboxy %d, boundboxy %d\n", hitbox.y, boundbox.y);
	hitbox.x = boundbox.x;
	hitbox.y = boundbox.y;
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