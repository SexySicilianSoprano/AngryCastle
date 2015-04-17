/*
 * FallingEntity.h
 * 
 * Tämä luokka on yläluokka kaikille entityille, joita voi vahingoittaa, 
 * eli, joilla on health pointit.
 * 
 * Esimerkki:
 *		FallingEntity FallingEntity = new FallingEntity();
 *		FallingEntity->damage(100);
 */

#ifndef __FALLINGENTITY_H_DEFINED__
#define __FALLINGENTITY_H_DEFINED__

#include "Window.h"
#include "MovingEntity.h"

#define GRAVITY 13

class FallingEntity : public MovingEntity
{
	public:
		FallingEntity(int x, int y, int w, int h, float speed, SDL_Rect hitbox);
		~FallingEntity();

		// Makes entity suffer gravity
		void update(float dt);

};

#endif //__FALLINGENTITY_H_DEFINED__