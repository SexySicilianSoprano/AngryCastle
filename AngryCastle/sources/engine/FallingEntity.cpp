/*
 * FallingEntity.cpp
 *
 */

#include "FallingEntity.h"

FallingEntity::FallingEntity(int x, int y, int w, int h, int speed, SDL_Rect hitbox) :
	MovingEntity(x, y, w, h, speed, hitbox),
	velocity_x(0), velocity_y(0),
	acceleration_x(0), acceleration_y(0),
	in_air(false) {

}

FallingEntity::~FallingEntity() {

}

void FallingEntity::jump() {
	if (in_air == false) {
		velocity_y -= 2;
		in_air = true;
	}
}

void FallingEntity::update(float dt) {
	velocity_y += GRAVITY * (dt / 1000);
	printf("Velocity: %f\n", velocity_y);
	desiredY += velocity_y;
}