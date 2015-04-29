/**
 *
 *	Skeleton.cpp
 */

#include "Skeleton.h"

Skeleton::Skeleton(Window *window, Player *player, Rectangle hitbox,
				   float speed, int hp) :
				   Enemy(window, player, hitbox, speed, hp) {

	render_offset.x = -20;
	render_offset.y = -6;

	/// Hitbox 13, 26

	Animation *tmp = nullptr;

	animations.resize(ANIMATION_MAX);

	tmp = new Animation(window, "graphics/enemies/skeleton2_walk.png", 64, 32, 0, 1, 1);
	animations[IDLE] = tmp;

	tmp = new Animation(window, "graphics/enemies/skeleton2_walk.png", 64, 32, 0, 4, 4);
	animations[WALK] = tmp;

	tmp = new Animation(window, "graphics/enemies/skeleton_attack.png", 64, 32, 0, 3, 8);
	animations[ATTACK] = tmp;

	currentAnimation = animations[IDLE];
	currentAnimation->play(INFINITE_LOOP);
}

Skeleton::~Skeleton() { }

void Skeleton::update() {
	Enemy::update(player);
	
	if (currentState == ENEMY_STATE_IDLE) {
		currentAnimation = animations[IDLE];
	}

	if (currentState == ENEMY_STATE_AGGRO) {
		if (getPlayerDistanceX() < 0) {
			right();
		} else {
			left();
		}

		currentAnimation = animations[WALK];
		currentAnimation->play(INFINITE_LOOP);
	}

	if (currentState == ENEMY_STATE_ATTACK) {
		currentAnimation = animations[ATTACK];
		currentAnimation->play(1);
	}

	FallingEntity::update();
}