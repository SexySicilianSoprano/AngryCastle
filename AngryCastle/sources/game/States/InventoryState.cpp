#include "InventoryState.h"

InventoryState::InventoryState(Window *window) :
	window(window),
	background(window, "graphics//ui//inventory_screen.png"),
	font(new Font("fonts/AveriaSerif-Bold.ttf", 28)),
	playername(new Text(font, Color("white"))) {
		
}

InventoryState::~InventoryState() {
	delete window;
}

stateStatus InventoryState::update() {
	stateStatus status;
	status.status = STATE_CONTINUE;
	status.prepend = false;

	if (Input::keyPressed(SDL_SCANCODE_A)) {
		printf("Changing to Menu state..\n");
		status.status = STATE_MENU;
	}

	return status;
}

void InventoryState::render() {
	background.render(0, 0);
	playername->print(window, "GRANT", 40, 25);
}