#include "StateManager.h"

StateManager::StateManager(Window *window) :
	window(window) {
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
	while (states.size() > 0) {
		BaseState *currentState = states.back();
		stateStatus newStatus;
		
		Input::update();
		
		newStatus = currentState->update();

		switch (newStatus.status)
		{
			case STATE_CONTINUE:
				break;

			case STATE_QUIT:
				popState();
				break;

			case STATE_MENU:
				if (!newStatus.prepend) {
					popState();
				}

				pushState(new MenuState(window));
				break;
		
			case STATE_GAME:
				if (!newStatus.prepend) {
					popState();
				}

				pushState(new GameState(window));
				break;

			default:
				break;
		}

		if (Input::keyState(SDL_SCANCODE_ESCAPE)) {
			popState();
		}
		
		window->clear();
		currentState->render();
		window->refresh();
	}
}