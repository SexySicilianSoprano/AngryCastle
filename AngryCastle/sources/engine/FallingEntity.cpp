/*
 * FallingEntity.cpp
 *
 */

#include "FallingEntity.h"

FallingEntity::FallingEntity(int x, int y, int w, int h, int speed, SDL_Rect hitbox) :
	MovingEntity(x, y, w, h, speed, hitbox),
	velocity_x(0), velocity_y(0),
	acceleration_x(0), acceleration_y(0) {

}

FallingEntity::~FallingEntity() {

}

void FallingEntity::update(float dt) {
	velocity_y += 9 * (dt / 1000);
	
	setPosition(x, y + velocity_y);
}