/*
 * Enemy.cpp
 *
 */

#include "Enemy.h"

Enemy::Enemy(Animation *animation, Animation *dyingAnimation, SDL_Rect hitbox, int initialHitPoints, SFX *sound):
	MovingEntity(animation, hitbox),
	DamageableEntity(1),
	dyingAnimation(dyingAnimation),
	index(0),
	norender(false),
	boom(sound)
{
	MovingEntity::speed(4);
	MovingEntity::setX(230);
	MovingEntity::setY(120);
}

Enemy::~Enemy()
{
}

void Enemy::render() {
	if (!norender) {
		MovingEntity::render();
	}
}

void Enemy::linearPattern()
{
	int linear[] = {LEFT};
	pattern.assign(linear, linear+1);
}

void Enemy::sinePattern(int index)
{
	int sine[] = {UP, UP, DOWN, DOWN};
	int shuf[4] = {};

	for (int i = 0; i < 4; i++) {
		shuf[i] = sine[i+index % 4];
	}

	pattern.assign(shuf, shuf+4);
}

void Enemy::update()
{
	if (isDead()) {
		MovingEntity::speed(2);
		MovingEntity::move(LEFT);

		if (MovingEntity::animation != dyingAnimation) {
			MovingEntity::animation = dyingAnimation;
			MovingEntity::animation->play(1);
			boom->play();
		}

		if (MovingEntity::animation->done()) {
			norender = true;
		}

		return;
	} else {
		chilltime = (++chilltime % 5);

		if (chilltime == 0) {
			index = ((++index) % pattern.size());
		}

		move(pattern[index]);
		move(LEFT);
		move(LEFT);
	}
}