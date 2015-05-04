/*
 * DamageableEntity.cpp
 *
 */

#include "DamageableEntity.h"

DamageableEntity::DamageableEntity(int initialHitPoints):
	alive(true),
	hitpoints(initialHitPoints)
{
}

DamageableEntity::~DamageableEntity()
{
}

void DamageableEntity::heal(int amount)
{
	hitpoints += amount;
}

void DamageableEntity::damage(int amount)
{
	hitpoints -= amount;

	if (hitpoints <= 0)
	{
		hitpoints = 0;
		alive = false;
	}
}

bool DamageableEntity::isDead()
{
	if (alive == true)
	{
		return false;
	}

	return true;
}

float DamageableEntity::getHitpoints()
{
	return hitpoints;
}