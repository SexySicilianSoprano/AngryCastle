/**
 * 
 * Skeleton.h
 */

#ifndef __SKELETON_H_DEFINED__
#define __SKELETON_H_DEFINED__

#include "Enemy.h"

class Skeleton : public Enemy
{
	public:
		Skeleton(Window *window, Player *player, Rectangle hitbox, float speed, int hp);
		~Skeleton();

		void update();

	private:
		
};

#endif //__SKELETON_H_DEFINED__