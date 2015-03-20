/*
 * Player.cpp
 *
 */

#include "player.h"

SDL_Rect Player::hitbox = {0, 0, 32, 32};

Player::Player(Window *window, EntityCollection<Projectile> *projectiles):
	window(window),
	currentAnimation(nullptr),
	DamageableEntity(3),
	MovingEntity(currentAnimation, hitbox),
	projectiles(projectiles),
	immune(false),
	immunityLength(0),
	norender(false),
	shot(false),
	piu("sounds//sound_gun_02.wav"),
	boom("sounds//sound_explosion02.wav")
{
	MovingEntity::speed(4);

	ammus = new Texture(window, "graphics//ammus.png");

	animations.push_back(new Animation(window, "graphics//player_spritesheet.png", 32, 32, 0, 4, 2));
	animations.push_back(new Animation(window, "graphics//player_spritesheet_damage.png", 32, 32, 0, 8, 4));
	animations.push_back(new Animation(window, "graphics//player_dead.png", 32, 32, 0, 10, 12));

	MovingEntity::animation = animations[0];
}

Player::~Player()
{
}

void Player::update()
{
	if (isDead()) {
		MovingEntity::speed(2);
		MovingEntity::move(LEFT);

		if (MovingEntity::animation != animations[2]) {
			MovingEntity::animation = animations[2];
			MovingEntity::animation->play(1);
			boom.play();
		}

		if (MovingEntity::animation->done()) {
			norender = true;
		}

		return;
	}

	if (Input::keyState(SDL_SCANCODE_K)) {
		DamageableEntity::damage(1);
		immunity(1500);
		isImmune();
	}

	if (Input::keyState(SDL_SCANCODE_W)) {
		move(0);
	}

	if (Input::keyState(SDL_SCANCODE_A)) {
		move(2);
	}

	if (Input::keyState(SDL_SCANCODE_S)) {
		move(1);
	}

	if (Input::keyState(SDL_SCANCODE_D)) {
		move(3);
	}

	if (Input::keyState(SDL_SCANCODE_SPACE)) {
		if (!shot) {
			Projectile projectile(ammus, 10, getX()+28, getY()+15, 0);
			projectiles->push(projectile);
			shot = true;
			piu.play();
		}
	} else {
		shot = false;
	}
	if (immune) {
		if (immunityLength > 0) {
			immunityLength -= window->getDelta();

			if (MovingEntity::animation != animations[1]) {
				MovingEntity::animation = animations[1];
				MovingEntity::animation->play(INFINITE_LOOP);
			}
		} else {
			immune = false;

			if (MovingEntity::animation != animations[0]) {
				MovingEntity::animation = animations[0];
				MovingEntity::animation->play(INFINITE_LOOP);
			}
		}
	}
}

void Player::render() {
	if (!norender) {
		MovingEntity::render();
	}
}

void Player::immunity(int length) {
	immunityLength += length;
	immune = true;
}

bool Player::isImmune() {
	return immune;
}