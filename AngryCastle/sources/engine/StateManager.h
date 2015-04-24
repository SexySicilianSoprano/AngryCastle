#ifndef __STATEMANAGER_H_DEFINED__
#define __STATEMANAGER_H_DEFINED__

#include <vector>
#include "Window.h"
#include "Input.h"
#include "BaseState.h"
#include "Music.h"
#include "..//game//States//MenuState.h"
#include "..//game//States//GameState.h"
#include "..//game//States//VictoryState.h"
#include "..//game//States//GameOverState.h"
#include "..//game//States//OptionsState.h"
#include "..//game//States//InventoryState.h"

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