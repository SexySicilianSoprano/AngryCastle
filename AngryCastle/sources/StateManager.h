/**
 * StateManager.h
 *
 * Description:
 * For managing states.
 *
 * Example:
 * --
 */

#ifndef __STATEMANAGER_H_DEFINED__
#define __STATEMANAGER_H_DEFINED__

#include <vector>
#include "Window.h"

class State;

class StateManager {
public:
	StateManager(Window *window);
	~StateManager();
	
	void changeState(State *state);
	void pushState(State *state);
	void popState();

	void update();
	void render();
	bool isRunning();
	bool quit();

private:
	bool love;
	Window *window;
	std::vector<State*> states;
};

#endif