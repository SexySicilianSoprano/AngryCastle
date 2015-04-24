#ifndef __VICTORYSTATE_H_DEFINED__
#define __VICTORYSTATE_H_DEFINED__

#include "..//..//engine//BaseState.h"
#include "..//..//engine//Window.h"
#include "..//..//engine//Input.h"
#include "..//..//engine//Font.h"
#include "..//..//engine//Text.h"
#include "..//..//engine//Color.h"
#include "..//..//engine//Texture.h"
#include "..//..//engine//Timer.h"

#define SLIDE_TIME 1000

class VictoryState : public BaseState {

	public:
		VictoryState(Window *window);
		~VictoryState();

		stateStatus update();
		void render();

	private:
		Window *window;

		Text slideShowText;
		int slide_index;
		std::vector<Texture *> backgrounds;
		std::vector<std::string> texts;

		Timer slideTimer;

};

#endif // __VICTORYSTATE_H_DEFINED__