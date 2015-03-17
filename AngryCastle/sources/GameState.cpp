#include "GameState.h"

GameState::GameState(Window *window) :
	window(window),
	font(nullptr) {
		
		font = new Font("PressStart2P.ttf", 14);
		menuText.setFont(font);
		menuText.setColor(Color("white"));
}

GameState::~GameState() {
	delete font;
}

stateStatus GameState::update() {
	stateStatus status;
	status.status = STATE_CONTINUE;
	status.prepend = false;

	if (Input::keyState(SDL_SCANCODE_A)) {
		printf("Changing to Menu state..\n");
		status.status = STATE_MENU;
	}

	return status;
}

void GameState::render() {
	menuText.print(window, "Press A to menu:))\n", 10, 10);
}