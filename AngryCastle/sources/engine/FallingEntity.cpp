/*
 * FallingEntity.cpp
 *
 */

#include "FallingEntity.h"

FallingEntity::FallingEntity(int x, int y, int w, int h, int speed, SDL_Rect hitbox) :
	MovingEntity(x, y, w, h, speed, hitbox),
	acceleration_x(0), acceleration_y(0) {

}

FallingEntity::~FallingEntity() {

}

void FallingEntity::jump() {
	if (in_air == false) {
		velocity_y -= 4;
		in_air = true;
	}
}

void FallingEntity::update(float dt) {
	velocity_y += GRAVITY * (dt / 1000);
	//printf("Velocity: %f\n", velocity_y);
	desiredY += velocity_y;
}