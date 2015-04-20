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

#include "Rectangle.h"

class Entity
{
	public:
		Entity(int x, int y, int w, int h);
		Entity(Rectangle hitbox);
		~Entity();

		virtual void update();

		SDL_Point render_offset;
		Rectangle hitbox;
};

#endif //__ENTITY_H_DEFINED__