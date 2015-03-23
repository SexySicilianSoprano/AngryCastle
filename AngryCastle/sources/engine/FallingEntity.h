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

class FallingEntity : public MovingEntity
{
	public:
		FallingEntity(int x, int y, int w, int h, int speed, SDL_Rect hitbox);
		~FallingEntity();

		// Makes entity suffer gravity
		void update(float dt);

	private:
		float velocity_x, velocity_y;
		float acceleration_x, acceleration_y;
};

#endif //__FALLINGENTITY_H_DEFINED__