#include "GameOverState.h"

GameOverState::GameOverState(Window *window) :
	window(window),
	background(window, "graphics//ui//gameover_screen.png") {
		
}

GameOverState::~GameOverState() {
}

stateStatus GameOverState::update() {
	stateStatus status;
	status.status = STATE_CONTINUE;
	status.prepend = false;

	if (Input::keyPressed(SDL_SCANCODE_A)) {
		printf("Changing to Menu state..\n");
		status.status = STATE_MENU;
	}

	return status;
}

void GameOverState::render() {
	background.render(0, 0);
}