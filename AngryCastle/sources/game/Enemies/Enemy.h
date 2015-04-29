/**
 * 
 * Enemy.h
 */

#ifndef __ENEMY_H_DEFINED__
#define __ENEMY_H_DEFINED__

#include "../../engine/MovingEntity.h"
#include "../../engine/DamageableEntity.h"
#include "../../engine/Player.h"
#include "../../engine/Animation.h"
#include "../../engine/Camera.h"

#define ENEMY_STATE_IDLE	0
#define ENEMY_STATE_AGGRO	1
#define ENEMY_STATE_ATTACK	2

class Enemy : public FallingEntity, public DamageableEntity
{
	public:
		Enemy(Window *window, Player *player, Rectangle hitbox, float speed, int hp);
		~Enemy();

		bool playerAtAggroRange(Player *player);
		bool playerAtHitRange(Player *player);
		int getPlayerDistanceX();
		int getPlayerDistanceY();

		void update(Player *player);
		void render(Camera *camera);

	protected:
		Window *window;
		Player *player;

		Animation *currentAnimation;
		std::vector<Animation*> animations;

		enum possible_animations {
			IDLE=0,
			WALK,
			ATTACK,

			ANIMATION_MAX
		};

		int currentState;
};

#endif //__ENEMY_H_DEFINED__