#ifndef __STATEMANAGER_H_DEFINED__
#define __STATEMANAGER_H_DEFINED__

#include <vector>
#include "Window.h"
#include "Input.h"
#include "BaseState.h"
#include "Music.h"
#include "..//game//MenuState.h"
#include "..//game//GameState.h"
#include "..//game//VictoryState.h"
#include "..//game//GameOverState.h"
#include "..//game//OptionsState.h"

class StateManager {

	public:
		StateManager(Window *window);
		~StateManager();

		void pushState(BaseState *state);
		void popState();

		void run();

	protected:
		Window *window;
		Music *music;
		std::vector<BaseState*> states;
		bool love;
};

#endif // __STATEMANAGER_H_DEFINED__