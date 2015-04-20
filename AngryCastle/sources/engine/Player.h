/*
 * Player.h
 */

#ifndef __PLAYER_H_DEFINED__
#define __PLAYER_H_DEFINED__

#include "Window.h"
#include "FallingEntity.h"
#include "DamageableEntity.h"
#include "Rectangle.h"
#include "Input.h"
#include "Animation.h"
#include "Camera.h"

class Player : public FallingEntity, public DamageableEntity
{
	public:
		Player(Window *window, Rectangle hitbox, float speed, int hp);
		~Player();

		void update(float dt);
		void updateAnimation();

		void render(Camera *camera);

		enum possible_animations {
			IDLE=0,
			WALK,
			JUMP,
			CROUCH,
			ATTACK,

			ANIMATION_MAX
		};

	private:
		Window *window;

		// 46 43 = sprite
		// 12 21 = hitbox
		Animation *currentAnimation;
		std::vector<Animation*> animations;

		bool crouch;
		bool jumping;
		bool attacking;
};

#endif // __PLAYER_H_DEFINED__