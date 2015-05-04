#include "Enemy.h"

Enemy::Enemy(Window *window, Rectangle hitbox, float speed, int hp):
	FallingEntity(hitbox, speed),
	DamageableEntity(hp),
	window(window),
	currentState(ENEMY_STATE_IDLE),
	currentAnimation(nullptr),
	weapon_hitbox(hitbox.x, hitbox.y, 0, 0)
{

}

Enemy::~Enemy() {

}

bool Enemy::playerAtAggroRange(Player *player) {
	int distance = abs(hitbox.Center().x - player->hitbox.Center().x) +
				   abs(hitbox.Center().y - player->hitbox.Center().y);

	if (distance < 250) {
		return true;
	}

	return false;
}

bool Enemy::playerAtHitRange(Player *player) {
	SDL_Point distance = {
		abs(hitbox.Center().x - player->hitbox.Center().x),
		abs(hitbox.Center().y - player->hitbox.Center().y)
	};

	if (distance.x < (hitbox.w * 2)) {
		return true;
	}

	return false;
}

int Enemy::getPlayerDistanceX(Player *player) {
	return hitbox.Center().x - player->hitbox.Center().x;
}

int Enemy::getPlayerDistanceY(Player *player) {
	return hitbox.Center().y - player->hitbox.Center().y;
}
/*
void Enemy::update(Player *player) {
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
}
*/
/*
void Enemy::render(Camera *camera) {
	if (facing_direction == 2) {
		currentAnimation->flip = true;
	} else {
		currentAnimation->flip = false;
	}

	currentAnimation->render((hitbox.x + render_offset.x) - camera->frame.x,
							 (hitbox.y + render_offset.y) - camera->frame.y);
}
*/