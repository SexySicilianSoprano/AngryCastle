/**
 * Player.h
 *
 * Description:
 * For creating players.
 *
 * Example:
 *		Player player = new Player();
 *		player->method();
 */

#ifndef __PLAYER_H_DEFINED__
#define __PLAYER_H_DEFINED__

#include "Input.h"
#include "MovingEntity.h"
#include "DamageableEntity.h"

class Player : public DamageableEntity, public MovingEntity {
public:
	Player(Window *window);
	~Player();
	void update();
	virtual void render();
	virtual int getX() {return MovingEntity::getX();};
	virtual int getY() {return MovingEntity::getY();};

private:
	Animation animation;
	SDL_Rect hitbox;
};

#endif