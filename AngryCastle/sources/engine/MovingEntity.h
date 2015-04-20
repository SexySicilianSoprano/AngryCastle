/*
 * MovingEntity.h
 *
 * Tämä luokka on yläluokka kaikille entityille, joita voi vahingoittaa,
 * eli, joilla on health pointit.
 *
 * Esimerkki:
 *		MovingEntity movingEntity = new MovingEntity();
 *		movingEntity->metodi();
 */

#ifndef __MOVINGENTITY_H_DEFINED__
#define __MOVINGENTITY_H_DEFINED__

#include "Entity.h"

class MovingEntity : public Entity
{
	public:
		MovingEntity(int x, int y, int w, int h, float acceleration, SDL_Rect hitbox);
		~MovingEntity();

		void jump();
		void left();
		void right();

		void commitMovement();
		void update(float dt);

	protected:
		float acceleration;
		float targetVx;
		float stoppedThreshold;
};

#endif // __MOVINGENTITY_H_DEFINED__