#include "StateManager.h"

StateManager::StateManager(Window *window) :
	window(window),
	love(true),
	music(nullptr) {
		pushState(new MenuState(window));
}

StateManager::~StateManager() {

}

void StateManager::pushState(BaseState *state) {
	states.push_back(state);
}

void StateManager::popState() {
	states.pop_back();
}

void StateManager::run() {
	music = new Music("music//ost.wav");
	//music->play();

	while (love) {
		BaseState *currentState = states.back();
		stateStatus new_status;
		
		Input::update();
		
		new_status = currentState->update();

		if (new_status.status != STATE_CONTINUE && !new_status.prepend) {
			popState();
		}

		switch (new_status.status)
		{
			case STATE_CONTINUE:
				break;

			case STATE_QUIT:
				love = false;
				break;

			case STATE_MENU:
				pushState(new MenuState(window));
				break;

			case STATE_OPTIONS:
				pushState(new OptionsState(window, music));
				break;
		
			case STATE_GAME:
				pushState(new GameState(window));
				break;

			case STATE_VICTORY:
				pushState(new VictoryState(window));
				break;

			case STATE_GAMEOVER:
				pushState(new GameOverState(window));
				break;

			default:
				break;
		}

		if (Input::keyPressed(SDL_SCANCODE_ESCAPE)) {
			if (states.size() > 1) {
				popState();
			} else {
				love = false;
			}
		}
		
		window->clear();
		currentState->render();
		window->refresh();
	}
}