/*
 * MovingEntity.cpp
 *
 */

#include "MovingEntity.h"

MovingEntity::MovingEntity(int x, int y, int w, int h, int speed, SDL_Rect hitbox) :
	Entity(x, y, w, h, hitbox),
	speed(speed) {
}

MovingEntity::~MovingEntity() {
}

void MovingEntity::update() {
	
}

void MovingEntity::commitMovement() {
	setPosition(desiredX, desiredY);
}

void MovingEntity::move(int direction) {
	if (direction == UP) {
		desiredY = y - speed;
		//printf("Entity x%d\\y%d\tHitbox x%d\\y%d\n", x, y, hitbox.x, hitbox.y);
	}

	if (direction == DOWN) {
		desiredY = y + speed;
		//printf("Entity x%d\\y%d\tHitbox x%d\\y%d\n", x, y, hitbox.x, hitbox.y);
	}

	if (direction == LEFT) {
		desiredX = x - speed;
		//printf("Entity x%d\\y%d\tHitbox x%d\\y%d\n", x, y, hitbox.x, hitbox.y);
	}

	if (direction == RIGHT) {
		desiredX = x + speed;
		//printf("Entity x%d\\y%d\atHitbox x%d\\y%d\n", x, y, hitbox.x, hitbox.y);
	}

	printf("X:\t\t%d\nY:\t\t%d\nDesired X:\t%d\nDesired Y:\t%d\nHitbox X:\t%d\nHitbox Y:\t%d\n\n",
		x, y, desiredX, desiredY, desiredX + hitbox_offset.x, desiredY + hitbox_offset.y);
}

void MovingEntity::setSpeed(int new_speed) {
	speed = new_speed;
}

int MovingEntity::getSpeed() {
	return speed;
}