/**
 * Entity.h
 *
 * Description:
 * For creating players.
 *
 * Example:
 *		Player player = new Player();
 *		player->method();
 */

#ifndef __ENTITY_H_DEFINED__
#define __ENTITY_H_DEFINED__

#include "Animation.h"

class Entity {
public:
	Entity(Texture *texture, SDL_Rect hitbox, int x = 0, int y = 0);
	Entity(Sprite *sprite, SDL_Rect hitbox, int x = 0, int y = 0);
	Entity(Animation *animation, SDL_Rect hitbox, int x = 0, int y = 0);
	~Entity();
	void render();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	SDL_Rect hitbox;

protected:
	int x;
	int y;
	int frame;
	int index;
	Texture *texture;
	Sprite *sprite;
	Animation *animation;
};

#endif