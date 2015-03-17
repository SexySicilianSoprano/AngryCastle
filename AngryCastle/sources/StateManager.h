#ifndef __STATEMANAGER_H_DEFINED__
#define __STATEMANAGER_H_DEFINED__

#include <vector>
#include "Window.h"
#include "Input.h"
#include "BaseState.h"
#include "MenuState.h"
#include "GameState.h"

class StateManager {

	public:
		StateManager(Window *window);
		~StateManager();

		void pushState(BaseState *state);
		void popState();

		void run();

	protected:
		Window *window;
		std::vector<BaseState*> states;
};

#endif // __STATEMANAGER_H_DEFINED__