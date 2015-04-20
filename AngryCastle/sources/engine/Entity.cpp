/*
 * Entity.cpp
 *
 */

#include "Entity.h"

Entity::Entity(int x, int y, int w, int h):
	hitbox(x, y, w, h)
{
	render_offset = {0, 0};
}

Entity::Entity(Rectangle hitbox):
	hitbox(hitbox)
{
	render_offset = {0, 0};
}

Entity::~Entity()
{

}

void Entity::update() {}
