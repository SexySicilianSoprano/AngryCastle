#include "Player.h"

Player::Player(Window *window, Rectangle hitbox, float speed, int hp):
	window(window),
	FallingEntity(hitbox, speed),
	DamageableEntity(hp),
	crouch(false),
	jumping(false),
	attacking(false)
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

void Player::update(float dt) {
	if (!in_air) {
		jumping = false;
	}

	if (Input::keyState(SDL_SCANCODE_W)) {
		boundbox.y += -4;
			// jump();
	}

	if (Input::keyState(SDL_SCANCODE_A)) {
		left();
	} else if (Input::keyState(SDL_SCANCODE_D)) {
		right();
	}

	if (Input::keyState(SDL_SCANCODE_S)) {
		boundbox.y += 4;
		crouch = true;
		targetVx = 0;
	} else {
		crouch = false;
	}

	if (Input::keyState(SDL_SCANCODE_SPACE)) {
		attacking = true;
		crouch = false;
	}

	// if (jumping &&
	// 	currentAnimation == animations[JUMP] &&
	// 	currentAnimation->getCurrentFrame() > 0) {
	// 	jump();
	// } else if (jumping &&
	// 			currentAnimation == animations[ATTACK]) {
	// 				jump();
	// }

	FallingEntity::update(dt);
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

	if (jumping) {
		currentAnimation = animations[JUMP];
	}

	/* TODO(jouni): Korjaa in_air pudotessa */
	if (in_air) {
		currentAnimation = animations[JUMP];
		// currentAnimation->pause();

		// if (velocity_y < 0) {
		// 	currentAnimation->setCurrentFrame(2);
		// } else {
		// 	currentAnimation->setCurrentFrame(1);
		// }

		/*
		if (!jumping) {
			currentAnimation->setCurrentFrame(2);
		}

		if (jumping && velocity_y > 0 && currentAnimation->getCurrentFrame() == 1) {
			currentAnimation->pause();
		}
		*/
	}

	if (crouch) {
		currentAnimation = animations[CROUCH];

		// if (currentAnimation->getCurrentFrame() == 1) {
		// 	currentAnimation->pause();
		// }
	}

	if (attacking) {

		currentAnimation = animations[ATTACK];
		// if (currentAnimation->getCurrentFrame() == 0 && currentAnimation->times_played > 0) {
		// 	attacking = false;
		// 	currentAnimation->times_played = 0;
		// }
	}
}