#ifndef __GAMESTATE_H_DEFINED__
#define __GAMESTATE_H_DEFINED__

#include "..//engine//BaseState.h"
#include "..//engine//Window.h"
#include "..//engine//Input.h"
#include "..//engine//Color.h"
#include "..//engine//Entity.h"
#include "..//engine//MovingEntity.h"
#include "..//engine//FallingEntity.h"
#include "..//engine//Level.h"

class GameState : public BaseState {

	public:
		GameState(Window *window);
		~GameState();

		stateStatus update();
		void render();

	private:
		Window *window;
		FallingEntity *entity;
		MovingEntity *jouni;
		Level *level;
};

#endif // __GAMESTATE_H_DEFINED__