/**
 * Projectile.h
 *
 * Description:
 * For creating projectiles.
 *
 * Example:
 * --
 */

#ifndef __PROJECTILE_H_DEFINED__
#define __PROJECTILE_H_DEFINED__

#include "MovingEntity.h"

class Projectile
{
public:
	Projectile(Window *window);
	~Projectile();
	void spawn(int type, int x, int y, int radian);
	void update();
	void render();

private:
	Window *window;
	Sprite bullet_texture;

	struct bullet {
		MovingEntity entity;
		int radian;
		int type;
	};

	std::vector<bullet> container;
};

#endif