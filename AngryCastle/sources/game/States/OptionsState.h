#ifndef __OPTIONSSTATE_H_DEFINED__
#define __OPTIONSSTATE_H_DEFINED__

#include "..//..//engine//BaseState.h"
#include "..//..//engine//Window.h"
#include "..//..//engine//Input.h"
#include "..//..//engine//Color.h"
#include "..//..//engine//Text.h"
#include "..//..//engine//Texture.h"
#include "..//..//engine//Music.h"

#define SCREEN_TITLE "Angry Castle - pre-release"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_LOGICAL_WIDTH 400
#define SCREEN_LOGICAL_HEIGHT 240

class OptionsState : public BaseState {

	public:
		OptionsState(Window *window, Music *music);
		~OptionsState();

		stateStatus update();
		void render();

	private:
		Window *window;
		Texture selector;
		Font *font;
		Music *music;

		int menu_index;
		std::vector<Text *> menu_items;
		int menu_x;
		int menu_y;
};

#endif // __OPTIONSSTATE_H_DEFINED__