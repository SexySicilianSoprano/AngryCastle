/**
 * State.h
 *
 * Description:
 * Abstract base class for all the states.
 *
 * Example:
 * --
 */

#ifndef __STATE_H_DEFINED__
#define __STATE_H_DEFINED__

#include "StateManager.h"

class State {
public:
	virtual void init(Window *window) = 0;
	virtual void update(StateManager *manager) = 0;
	/*virtual void cleanup() = 0;
	virtual void pause() = 0;
	virtual void unpause() = 0;
	virtual void render(StateManager *manager) = 0;
	virtual void handleEvents(StateManager *manager) = 0; */

	void changeState(StateManager *manager, State *state) {
		manager->changeState(state);
	}

protected:
	State() {
	}
};

#endif