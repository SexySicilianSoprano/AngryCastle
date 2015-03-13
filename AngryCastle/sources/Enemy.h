/**
 * Enemy.h
 *
 * Description:
 * For creating enemies.
 *
 * Example:
 * --
 */

#ifndef __ENEMY_H_DEFINED__
#define __ENEMY_H_DEFINED__

#include "MovingEntity.h"
#include "Animation.h"

class Enemy : public MovingEntity
{
public:
	Enemy(Animation *animation, SDL_Rect hitbox, int initial_hitpoints);
	~Enemy();
	void render();
	void update();
	void linearPattern();
	void sinePattern(int index);

private:
	enum DIRECTION {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	int index;
	int chilltime;
	std::vector<int> pattern;
};

#endif