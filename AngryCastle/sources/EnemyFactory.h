/**
 * EnemyFactory.h
 *
 * Description:
 * --
 *
 * Example:
 * --
 */

#ifndef __ENEMYFACTORY_H_DEFINED__
#define __ENEMYFACTORY_H_DEFINED__

#include "Window.h"
#include "Animation.h"
#include "Enemy.h"

#define DRONE  1
#define JET    2

class EnemyFactory {
public:
	EnemyFactory(Window *window);
	~EnemyFactory();
	Enemy spawn(int type, int spawn_height);

private:
	Window *window;

	struct enemy_definition {
		Animation *animation;
		SDL_Rect hitbox;
		int hitpoints;

		enemy_definition() {
			animation = nullptr;
			SDL_RectEmpty(&hitbox);
			hitpoints = 0;
		}
	} drone, jet;
};

#endif