#include "MenuState.h"

MenuState::MenuState(Window *window) :
	window(window),
	menu_x(170),
	menu_y(110),
	selector(window, ""),
	font(nullptr) {
		font = new Font("fonts//AveriaSerif-Bold.ttf", 14);

		menu_items.push_back(new Text(font, Color("white")));
		menu_items.push_back(new Text(font, Color("white")));
		menu_items.push_back(new Text(font, Color("white")));
}

MenuState::~MenuState() {
	delete font;
}

stateStatus MenuState::update() {
	stateStatus status;
	status.status = STATE_CONTINUE;
	status.prepend = false;

	if (Input::keyPressed(SDL_SCANCODE_S)) {
		printf("Changing to Game state..\n");
		status.status = STATE_GAME;
	}

	if (Input::keyPressed(SDL_SCANCODE_V)) {
		printf("Changing to Game state..\n");
		status.status = STATE_VICTORY;
	}

	if (Input::keyPressed(SDL_SCANCODE_L)) {
		printf("Changing to Game state..\n");
		status.status = STATE_GAMEOVER;
	}

	return status;
}

void MenuState::render() {
	menu_items[0]->print(window, "Start", menu_x, menu_y + 0);
	menu_items[1]->print(window, "Options", menu_x, menu_y + 20);
	menu_items[2]->print(window, "Quit", menu_x, menu_y + 40);
}