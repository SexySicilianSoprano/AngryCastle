/*
 * Entity.h
 * 
 * T�m� luokka on yl�luokka kaikille pelin entiteeteille, joita voivat olla
 * esimerkiksi, pelaaja, viholliset ja ammukset.
 * 
 * Esimerkki:
 *		Entity entity = new Entity();
 *		entity->metodi();
 */

#ifndef __ENTITY_H_DEFINED__
#define __ENTITY_H_DEFINED__

#include "SDL.h"

class Entity
{
	public:
		Entity(int x, int y, int w, int h, SDL_Rect hitbox_offset);
		~Entity();

		virtual void update() = 0;

		bool collides(Entity *other);
		void setPosition(int x, int y);

		int getX();
		int getY();
		int getW();
		int getH();

	protected:
		int x, y, w, h;
		int desiredX, desiredY;
		SDL_Rect hitbox_offset;

};

#endif //__ENTITY_H_DEFINED__