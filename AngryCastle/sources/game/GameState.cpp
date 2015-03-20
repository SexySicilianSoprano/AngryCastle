#include "GameState.h"

GameState::GameState(Window *window) :
	window(window) {
		
}

GameState::~GameState() {
}

stateStatus GameState::update() {
	stateStatus status;
	status.status = STATE_CONTINUE;
	status.prepend = false;

	if (Input::keyPressed(SDL_SCANCODE_S)) {
		printf("Changing to Menu state..\n");
		status.status = STATE_MENU;
	}

	return status;
}

void GameState::render() {
}