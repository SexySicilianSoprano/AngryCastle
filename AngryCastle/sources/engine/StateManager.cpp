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
				popState();
				break;

			case STATE_MENU:
				pushState(new MenuState(window));
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
			popState();
		}
		
		window->clear();
		currentState->render();
		window->refresh();
	}
}