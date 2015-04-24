#ifndef __GAMEOVERSTATE_H_DEFINED__
#define __GAMEOVERSTATE_H_DEFINED__

#include "..//..//engine//BaseState.h"
#include "..//..//engine//Window.h"
#include "..//..//engine//Input.h"
#include "..//..//engine//Color.h"
#include "..//..//engine//Texture.h"

class GameOverState : public BaseState {

	public:
		GameOverState(Window *window);
		~GameOverState();

		stateStatus update();
		void render();

	private:
		Window *window;
		Texture background;
};

#endif // __GAMEOVERSTATE_H_DEFINED__