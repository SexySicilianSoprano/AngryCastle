/**
 * MovingEntity.cpp
 *
 */

#include "MovingEntity.h"

MovingEntity::MovingEntity(Texture *sprite, SDL_Rect hitbox) :
	Entity(sprite, hitbox),
	speed(1) {
}

MovingEntity::MovingEntity(Sprite *sprite, SDL_Rect hitbox) :
	Entity(sprite, hitbox),
	speed(1) {
}

MovingEntity::MovingEntity(Animation *sprite, SDL_Rect hitbox) :
	Entity(sprite, hitbox),
	speed(1) {
}

MovingEntity::~MovingEntity()
{ }

void MovingEntity::move(int direction) {
	if (direction == UP) {
		y -= speed;
		hitbox.y = hitbox.y + y;
	}

	if (direction == DOWN) {
		y += speed;
		hitbox.y = hitbox.y + y;
	}

	if (direction == LEFT) {
		x -= speed;
		hitbox.x = hitbox.x + x;
	}

	if (direction == RIGHT) {
		x += speed;
		hitbox.x = hitbox.x + x;
	}
}

void MovingEntity::setSpeed(int new_speed) {
	speed = new_speed;
}

SDL_bool MovingEntity::collides(Entity *other) {
	SDL_Rect result;
	return SDL_IntersectRect(&hitbox, &other->hitbox, &result);
}

SDL_bool MovingEntity::collides(Level *level) {
	int hitbox_x;
	int hitbox_y;

	hitbox_x = hitbox.x;
	hitbox_y = hitbox.y;

	if (level->getTile(hitbox_x, hitbox_y) != 1) {
		return SDL_TRUE;
	}
	
	hitbox_x = hitbox.x + hitbox.w;
	hitbox_y = hitbox.y;

	if(level->getTile(hitbox_x, hitbox_y) != 1) {
		return SDL_TRUE;
	}

	hitbox_x = hitbox.x + hitbox.w;
	hitbox_y = hitbox.y + hitbox.h;

	if(level->getTile(hitbox_x, hitbox_y) != 1) {
		return SDL_TRUE;
	}

	hitbox_x = hitbox.x;
	hitbox_y = hitbox.y + hitbox.h;

	if(level->getTile(hitbox_x, hitbox_y) != 1) {
		return SDL_TRUE;
	}
	
	return SDL_FALSE;
}

int MovingEntity::getSpeed() {
	return speed;
}