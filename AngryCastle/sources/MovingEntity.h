/**
 * MovingEntity.h
 *
 * Description:
 * For creating entities that can move.
 *
 * Example:
 * --
 */

#ifndef __MOVINGENTITY_H_DEFINED__
#define __MOVINGENTITY_H_DEFINED__

#include "Entity.h"
#include "Level.h"

class MovingEntity : public Entity {
public:
	MovingEntity(Texture *sprite, SDL_Rect hitbox);
	MovingEntity(Sprite *sprite, SDL_Rect hitbox);
	MovingEntity(Animation *sprite, SDL_Rect hitbox);
	~MovingEntity();

	enum DIRECTION {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	void move(int direction);
	void setSpeed(int new_speed);
	int getSpeed();
	SDL_bool collides(Entity *other);
	SDL_bool collides(Level *level);

private:
	int speed;
};

#endif