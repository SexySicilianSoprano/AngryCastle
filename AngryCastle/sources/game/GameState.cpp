#include "GameState.h"

GameState::GameState(Window *window) :
	window(window),
	entity(nullptr),
	level(nullptr) {
		SDL_Rect hitbox = {0, 0, 10, 10};
		entity = new FallingEntity(110, 80, 10, 10, 1, hitbox);
		jouni = new MovingEntity(110, 110, 8, 8, 1, hitbox);
		level = new Level(window, new Camera(400, 240));
		level->load("");
}

GameState::~GameState() {
}

stateStatus GameState::update() {
	stateStatus status;
	status.status = STATE_CONTINUE;
	status.prepend = false;

	if (Input::keyPressed(SDL_SCANCODE_ESCAPE)) {
		printf("Changing to Menu state..\n");
		status.status = STATE_MENU;
	}

	/*
	if (Input::keyState(SDL_SCANCODE_W)) {
		entity->move(MovingEntity::UP);
	}
	
	if (Input::keyState(SDL_SCANCODE_A)) {
		entity->move(MovingEntity::LEFT);
	}

	if (Input::keyState(SDL_SCANCODE_S)) {
		entity->move(MovingEntity::DOWN);
	}

	if (Input::keyState(SDL_SCANCODE_D)) {
		entity->move(MovingEntity::RIGHT);
	}
	*/

	printf("Delta: %d\n", window->getDelta());

	entity->update(window->getDelta());

	if (!entity->collides(jouni)) {
		entity->commitMovement();
	}

	return status;
}

void GameState::render() {
	window->drawRect(entity->getX(),
					 entity->getY(),
					 entity->getW(),
					 entity->getH(),
					 Color("red"));
	
	window->drawRect(jouni->getX(),
					 jouni->getY(),
					 jouni->getW(),
					 jouni->getH(),
					 Color("green"));
}