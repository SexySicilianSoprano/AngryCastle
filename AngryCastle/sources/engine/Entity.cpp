/*
 * Entity.cpp
 *
 */

#include "Entity.h"

Entity::Entity(int x, int y, int w, int h, SDL_Rect hitbox_offset) :
	x(x), y(y), w(w), h(h),
	hitbox_offset(hitbox_offset),
	desiredX(x),
	desiredY(y)
{
	if (SDL_RectEmpty(&hitbox_offset)) {
		hitbox_offset.x = 0;
		hitbox_offset.y = 0;
		hitbox_offset.w = w;
		hitbox_offset.h = h;
	}
}

Entity::~Entity()
{

}

void Entity::setPosition(int new_x, int new_y) {
	// Move entity
	x = new_x;
	y = new_y;

	// Reset desiredX, desiredY
	desiredX = x;
	desiredY = y;

	//printf("X:\t\t%d\nY:\t\t%d\nDesired X:\t%d\nDesired Y:\t%d\nHitbox X:\t%d\nHitbox Y:\t%d\n\n",
		//x, y, desiredX, desiredY, desiredX + hitbox_offset.x, desiredY + hitbox_offset.y);
}

bool Entity::collides(Entity *other) {
	SDL_Rect primary_hitbox, secondary_hitbox, result;

	// Primary hitbox (this entity)
	primary_hitbox.x = desiredX + hitbox_offset.x;
	primary_hitbox.y = desiredY + hitbox_offset.y;
	primary_hitbox.w = hitbox_offset.w;
	primary_hitbox.h = hitbox_offset.h;

	// Secondary hitbox (other entity)
	secondary_hitbox.x = other->x + other->hitbox_offset.x;
	secondary_hitbox.y = other->y + other->hitbox_offset.y;
	secondary_hitbox.w = other->hitbox_offset.w;
	secondary_hitbox.h = other->hitbox_offset.h;

	//printf("Primary:\tw%d h%d x%d y%d\n", primary_hitbox.w, primary_hitbox.h, primary_hitbox.x, primary_hitbox.y);
	//printf("Secondary:\tw%d h%d x%d y%d\n", secondary_hitbox.w, secondary_hitbox.h, secondary_hitbox.x, secondary_hitbox.y);

	if (SDL_IntersectRect(&primary_hitbox, &secondary_hitbox, &result)) {
		//printf("Result:\tw%d h%d x%d y%d\n\n", result.w, result.h, result.x, result.y);

		desiredX = x;
		desiredY = y;

		return true;
	}

	return false;
}

int Entity::getX() {
	return x;
}

int Entity::getY() {
	return y;
}

int Entity::getW() {
	return w;
}

int Entity::getH() {
	return h;
}