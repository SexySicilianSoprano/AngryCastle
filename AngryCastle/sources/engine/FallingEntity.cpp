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
	velocity_y += GRAVITY * (dt / 1000);
	desiredY += velocity_y;
	MovingEntity::update(dt);
}