#include "OptionsState.h"

OptionsState::OptionsState(Window *window, Music *music) :
	window(window),
	music(music),
	menu_x(170),
	menu_y(110),
	menu_index(0),
	selector(window, "graphics/ui/selector.png") {
		font = new Font("fonts/AveriaSerif-Bold.ttf", 14);

		menu_items.push_back(new Text(font, Color("white")));
		menu_items.push_back(new Text(font, Color("white")));
		menu_items.push_back(new Text(font, Color("white")));
		menu_items.push_back(new Text(font, Color("white")));
}

OptionsState::~OptionsState() {
}

stateStatus OptionsState::update() {
	stateStatus status;
	status.status = STATE_CONTINUE;
	status.prepend = false;

	if (Input::keyPressed(SDL_SCANCODE_UP) || Input::keyPressed(SDL_SCANCODE_W)) {
		if (menu_index > 0) {
			menu_index--;
		}
	}

	if (Input::keyPressed(SDL_SCANCODE_DOWN) || Input::keyPressed(SDL_SCANCODE_S)) {
		if (menu_index < menu_items.size() - 1) {
			menu_index++;
		}
	}

	if (Input::keyPressed(SDL_SCANCODE_RETURN) || Input::keyPressed(SDL_SCANCODE_SPACE)) {
		switch (menu_index)
		{
			case 0:
				if (window->isFullscreen()) {
					window->resize(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, false);
				} else {
					window->resize(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, true);
				}
				break;

			case 1:
				printf("Sound on off\n");
				break;

			case 2:
				if (music->isPlaying()) {
					music->pause();
				} else {
					music->play();
				}
				break;

			case 3:
				printf("Music volume \n");
				break;

			default:
				break;
		}
	}

	return status;
}

void OptionsState::render() {
	selector.render(menu_x - 25, menu_y + menu_index * 20);
	menu_items[0]->print(window, "Fullscreen", menu_x, menu_y + 0);
	menu_items[1]->print(window, "Sound", menu_x, menu_y + 20);
	menu_items[2]->print(window, "Music", menu_x, menu_y + 40);
	menu_items[3]->print(window, "Music volume", menu_x, menu_y + 60);
}