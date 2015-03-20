#ifndef __GAMESTATE_H_DEFINED__
#define __GAMESTATE_H_DEFINED__

#include "..//engine//BaseState.h"
#include "..//engine//Window.h"
#include "..//engine//Input.h"
#include "..//engine//Color.h"

class GameState : public BaseState {

	public:
		GameState(Window *window);
		~GameState();

		stateStatus update();
		void render();

	private:
		Window *window;
};

#endif // __GAMESTATE_H_DEFINED__