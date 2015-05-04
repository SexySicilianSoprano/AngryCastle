#include "Player.h"

Player::Player(Window *window, Rectangle hitbox, float speed, int hp):
	window(window),
	FallingEntity(hitbox, speed),
	DamageableEntity(hp),
	crouch(false),
	jumping(false),
	attacking(false),
	weapon_hitbox(0, 0, 0, 0)
{
	render_offset.x = -16;
	render_offset.y = -17;

	Animation *tmp = nullptr;

	animations.resize(ANIMATION_MAX);

	tmp = new Animation(window, "graphics/characters/player_idle.png",   46, 43, 0, 3, 4);
	animations[IDLE] = tmp;

	tmp = new Animation(window, "graphics/characters/player_walk.png",   46, 43, 0, 4, 4);
	animations[WALK] = tmp;

	tmp = new Animation(window, "graphics/characters/player_jump.png",   46, 43, 0, 4, 8);
	animations[JUMP] = tmp;

	tmp = new Animation(window, "graphics/characters/player_crouch.png", 46, 43, 0, 3, 8);
	animations[CROUCH] = tmp;

	tmp = new Animation(window, "graphics/characters/player_attack.png", 46, 43, 0, 4, 8);
	animations[ATTACK] = tmp;

	currentAnimation = animations[IDLE];
	currentAnimation->play(INFINITE_LOOP);
}

Player::~Player() {
	delete window;
	delete currentAnimation;
}

void Player::update() {
	weapon_hitbox.w = 0;
	weapon_hitbox.h = 0;
	weapon_hitbox.y = hitbox.y - 16;

	if (facing_direction == 2) {
		weapon_hitbox.x = hitbox.x + (-16);
	} else {
		weapon_hitbox.x = hitbox.x + 16;
	}

	if (!in_air) {
		jumping = false;
	}

	if (Input::keyState(SDL_SCANCODE_W)) {
			jump();
	}

	if (Input::keyState(SDL_SCANCODE_A)) {
		left();
	} else if (Input::keyState(SDL_SCANCODE_D)) {
		right();
	}

	if (Input::keyState(SDL_SCANCODE_S)) {
		crouch = true;
		targetVx = 0;
	} else {
		crouch = false;
	}

	if (Input::keyState(SDL_SCANCODE_SPACE)) {
		attacking = true;
		crouch = false;
		targetVx = 0;
	}

	if (currentAnimation == animations[ATTACK] &&
		currentAnimation->getCurrentFrame() == 3) {

		weapon_hitbox.w = 18;
		weapon_hitbox.h = 43;
	}

	if (jumping &&
		currentAnimation == animations[JUMP] &&
		currentAnimation->getCurrentFrame() > 0) {
		jump();
	} else if (jumping &&
				currentAnimation == animations[ATTACK]) {
					jump();
	}

	FallingEntity::update();
	updateAnimation();
	currentAnimation->play(INFINITE_LOOP);
}

void Player::render(Camera *camera) {
	if (facing_direction == 2) {
		currentAnimation->flip = true;
	} else {
		currentAnimation->flip = false;
	}

	currentAnimation->render((hitbox.x + render_offset.x) - camera->frame.x,
							 (hitbox.y + render_offset.y) - camera->frame.y);

}

void Player::updateAnimation() {
	//if (currentAnimation == animations[CROUCH] && !currentAnimation->done()) {
	//	currentAnimation->running = true;
	//} else {
		currentAnimation = animations[IDLE];
	//}

	if (velocity_x != 0) {
		currentAnimation = animations[WALK];
	}

	if (attacking) {
		currentAnimation = animations[ATTACK];
		if (currentAnimation->getCurrentFrame() == 0 && currentAnimation->times_played > 0) {
		 	attacking = false;
		 	currentAnimation->times_played = 0;
		}
	}


	if (jumping) {
		currentAnimation = animations[JUMP];
	}

	/* TODO(jouni): Korjaa in_air pudotessa */
	// if (in_air) {
	// 	currentAnimation = animations[JUMP];
	// 	currentAnimation->pause();

	// 	if (velocity_y < 0) {
	// 		currentAnimation->setCurrentFrame(2);
	// 	} else {
	// 	 	currentAnimation->setCurrentFrame(1);
	// 	}

	// 	// if (!jumping) {
	// 	// 	currentAnimation->setCurrentFrame(2);
	// 	// }

	// 	if (jumping && velocity_y > 0 && currentAnimation->getCurrentFrame() == 1) {
	// 		currentAnimation->pause();
	// 	}
	// }

	if (crouch) {
		currentAnimation = animations[CROUCH];

		 if (currentAnimation->getCurrentFrame() == 1) {
		 	currentAnimation->pause();
		 }
	}


}