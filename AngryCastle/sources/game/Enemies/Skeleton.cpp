/**
 *
 *	Skeleton.cpp
 */

#include "Skeleton.h"

Skeleton::Skeleton(Window *window, Rectangle hitbox,
				   float speed, int hp) :
				   Enemy(window, hitbox, speed, hp) {

	render_offset.x = -20;
	render_offset.y = -6;

	/// Hitbox 13, 26

	Animation *tmp = nullptr;

	animations.resize(ANIMATION_MAX);

	tmp = new Animation(window, "graphics/enemies/skeleton2_walk.png", 64, 32, 0, 1, 1);
	animations[IDLE] = tmp;

	tmp = new Animation(window, "graphics/enemies/skeleton2_walk.png", 64, 32, 0, 4, 4);
	animations[WALK] = tmp;

	tmp = new Animation(window, "graphics/enemies/skeleton2_attack.png", 64, 32, 0, 3, 8);
	animations[ATTACK] = tmp;

	currentAnimation = animations[IDLE];
	currentAnimation->play(INFINITE_LOOP);
}

Skeleton::~Skeleton() { }

void Skeleton::update(Player *player) {
	//Enemy::update(player);

	weapon_hitbox.w = 0;
	weapon_hitbox.h = 0;

	if (facing_direction == 2) {
		weapon_hitbox.x = hitbox.x + (-16);
	} else {
		weapon_hitbox.x = hitbox.x + 16;
	}

	switch (currentState)
	{
	case ENEMY_STATE_IDLE:
		if (playerAtAggroRange(player)) {
			currentState = ENEMY_STATE_AGGRO;
		}
		break;

	case ENEMY_STATE_AGGRO:
		if(!playerAtAggroRange(player)) {
			currentState = ENEMY_STATE_IDLE;
		}

		if (playerAtHitRange(player) &&
			getPlayerDistanceY(player) < 10 &&
			getPlayerDistanceY(player) > -10) {
			currentState = ENEMY_STATE_ATTACK;
		}
		break;

	case ENEMY_STATE_ATTACK:
		if (currentAnimation == animations[ATTACK]
			&& currentAnimation->done()) {
			currentState = ENEMY_STATE_AGGRO;
		}
		break;

	default:
		currentState = ENEMY_STATE_IDLE;
		break;
	}

	if (currentState == ENEMY_STATE_IDLE) {
		currentAnimation = animations[IDLE];
	}

	if (currentState == ENEMY_STATE_AGGRO) {
		if (getPlayerDistanceX(player) < 0) {
			right();
		} else {
			left();
		}

		currentAnimation = animations[WALK];
		currentAnimation->play(INFINITE_LOOP);
	}

	if (currentState == ENEMY_STATE_ATTACK) {
		if (currentAnimation->getCurrentFrame() == 2) {
			weapon_hitbox.w = 30;
			weapon_hitbox.h = 14;
		}

		currentAnimation = animations[ATTACK];
		currentAnimation->play(1);
	}

	FallingEntity::update();
}

void Skeleton::render(Camera *camera) {
	if (facing_direction == 2) {
		currentAnimation->flip = true;
	} else {
		currentAnimation->flip = false;
	}

	currentAnimation->render((hitbox.x + render_offset.x) - camera->frame.x,
							 (hitbox.y + render_offset.y) - camera->frame.y);
}