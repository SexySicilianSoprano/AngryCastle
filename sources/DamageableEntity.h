/**
 * DamageableEntity.h
 *
 * Description:
 * --
 *
 * Example:
 * --
 */

#ifndef __DAMAGEABLEENTITY_H_DEFINED__
#define __DAMAGEABLEENTITY_H_DEFINED__

#include "Entity.h"

class DamageableEntity : public Entity {
public:
	DamageableEntity(Sprite *sprite, SDL_Rect hitbox, int initial_hitpoints);
	DamageableEntity(Animation *animation, SDL_Rect hitbox, int initial_hitpoints);
	~DamageableEntity();
	void heal(int amount);
	void damage(int amount);
	bool isDead();
	int getHitpoints();

private:
	bool alive;
	int hitpoints;
};

#endif