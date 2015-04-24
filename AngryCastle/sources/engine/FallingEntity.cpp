/*
 * FallingEntity.cpp
 *
 */

#include "FallingEntity.h"

FallingEntity::FallingEntity(Rectangle hitbox, float speed) :
	MovingEntity(hitbox, speed) {

}

FallingEntity::~FallingEntity() {

}

void FallingEntity::update(float dt) {
	velocity_y += GRAVITY * (16.f / 1000);
	if (velocity_y >= 7) {
		velocity_y = 7;
	}

	// boundbox.y += velocity_y;

	MovingEntity::update(dt);
}