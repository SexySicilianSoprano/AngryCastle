#ifndef __MENUSTATE_H_DEFINED__
#define __MENUSTATE_H_DEFINED__

#include "..//engine//BaseState.h"
#include "..//engine//Window.h"
#include "..//engine//Input.h"
#include "..//engine//Font.h"
#include "..//engine//Text.h"
#include "..//engine//Color.h"
#include "..//engine//Texture.h"

class MenuState : public BaseState {

	public:
		MenuState(Window *window);
		~MenuState();

		stateStatus update();
		void render();

	private:
		Texture selector;
		int menu_index;

		std::vector<Text *> menu_items;
		Window *window;
		Font *font;
		int menu_x;
		int menu_y;
};

#endif // __MENUSTATE_H_DEFINED__