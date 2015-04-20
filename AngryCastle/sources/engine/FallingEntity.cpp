/*
 * FallingEntity.cpp
 *
 */

#include "FallingEntity.h"

FallingEntity::FallingEntity(int x, int y, int w, int h, float speed, SDL_Rect hitbox) :
	MovingEntity(x, y, w, h, speed, hitbox) {

}

FallingEntity::~FallingEntity() {

}

void FallingEntity::update(float dt) {
	velocity_y += GRAVITY * (16.f / 1000);
	if (velocity_y >= 7) {
		velocity_y = 7;
	}

	if (velocity_y != 0) {
		printf("Velocity Y: %f\n", velocity_y);
	}

	desiredY += velocity_y;
	MovingEntity::update(dt);
}