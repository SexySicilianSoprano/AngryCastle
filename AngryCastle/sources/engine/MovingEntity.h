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

#define FACING_RIGHT 1
#define FACING_LEFT 2

class MovingEntity : public Entity
{
	public:
		MovingEntity(Rectangle hitbox, float speed);
		~MovingEntity();

		void jump();
		void left();
		void right();

		void commitMovement();
		void update(float dt);

		int facing_direction;
		bool in_air;
		float velocity_x, velocity_y;

		Rectangle boundbox;

	protected:
		float speed;
		float acceleration;
		float targetVx;
		float stoppedThreshold;
};

#endif // __MOVINGENTITY_H_DEFINED__