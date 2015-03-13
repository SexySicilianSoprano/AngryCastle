/**
 * StateManager.cpp
 *
 */

#include "StateManager.h"
#include "State.h"

StateManager::StateManager(Window *window):
	love(true),
	window(window) {

}

StateManager::~StateManager() {
}

void StateManager::changeState(State *state) {
	states.push_back(state);
	states.back()->init(window);
}

void StateManager::pushState(State *state) {

}

void StateManager::popState() {

}

void StateManager::update() {
	states.back()->update(this);
}

void StateManager::render() {

}

bool StateManager::isRunning() {
	return love;
}

bool StateManager::quit() {
	return false;
}