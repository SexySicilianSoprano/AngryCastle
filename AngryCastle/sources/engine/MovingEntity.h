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
		MovingEntity(int x, int y, int w, int h, int speed, SDL_Rect hitbox);
		~MovingEntity();

		void move(int direction);
		void commitMovement();
		void update();

		void setSpeed(int speed);
		int getSpeed();

	private:
		int speed;
		bool inAir;
};

#endif // __MOVINGENTITY_H_DEFINED__