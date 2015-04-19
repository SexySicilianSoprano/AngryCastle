/*
 * Entity.h
 *
 * Tämä luokka on yläluokka kaikille pelin entiteeteille, joita voivat olla
 * esimerkiksi, pelaaja, viholliset ja ammukset.
 *
 * Esimerkki:
 *		Entity entity = new Entity();
 *		entity->metodi();
 */

#ifndef __ENTITY_H_DEFINED__
#define __ENTITY_H_DEFINED__

#include "SDL.h"

#define FACING_RIGHT 1
#define FACING_LEFT 2

class Entity
{
	public:
		Entity(int x, int y, int w, int h, SDL_Rect hitbox_offset);
		~Entity();

		void update();

		bool collides(Entity *other);
		bool collides(SDL_Rect *other);
		void setPosition(int x, int y);

		int getX();
		int getY();
		int getW();
		int getH();
		SDL_Rect getHitbox();
		int desiredX, desiredY;
		SDL_Rect hitbox_offset;

		int facing_direction;
		bool in_air;
		float velocity_x, velocity_y;

	protected:
		int x, y, w, h;
};

#endif //__ENTITY_H_DEFINED__