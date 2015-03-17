#ifndef __GAMESTATE_H_DEFINED__
#define __GAMESTATE_H_DEFINED__

#include "BaseState.h"
#include "Window.h"
#include "Input.h"
#include "Font.h"
#include "Text.h"
#include "Color.h"

class GameState : public BaseState {

	public:
		GameState(Window *window);
		~GameState();

		stateStatus update();
		void render();

	private:
		Window *window;
		Font *font;
		Text menuText;
};

#endif // __GAMESTATE_H_DEFINED__