#ifndef __MENUSTATE_H_DEFINED__
#define __MENUSTATE_H_DEFINED__

#include "BaseState.h"
#include "Window.h"
#include "Input.h"
#include "Font.h"
#include "Text.h"
#include "Color.h"

class MenuState : public BaseState {

	public:
		MenuState(Window *window);
		~MenuState();

		stateStatus update();
		void render();

	private:
		Window *window;
		Font *font;
		Text menuText;
};

#endif // __MENUSTATE_H_DEFINED__