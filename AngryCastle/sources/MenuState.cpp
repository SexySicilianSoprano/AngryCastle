#include "MenuState.h"

MenuState::MenuState(Window *window) :
	window(window),
	font(nullptr) {
		
		font = new Font("PressStart2P.ttf", 14);
		menuText.setFont(font);
		menuText.setColor(Color("white"));
}

MenuState::~MenuState() {
	delete font;
}

stateStatus MenuState::update() {
	stateStatus status;
	status.status = STATE_CONTINUE;
	status.prepend = false;

	if (Input::keyState(SDL_SCANCODE_S)) {
		printf("Changing to Game state..\n");
		status.status = STATE_GAME;
	}

	return status;
}

void MenuState::render() {
	menuText.print(window, "Press S to play!", 10, 10);
}