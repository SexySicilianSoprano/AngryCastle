/**
 * 
 * InventoryState.h
 */

#ifndef __INVENTORYSTATE_H_DEFINED__
#define __INVENTORYSTATE_H_DEFINED__

#include "..//..//engine//BaseState.h"
#include "../../engine/Window.h"
#include "../../engine/Texture.h"
#include "../../engine/Input.h"
#include "../../engine/Font.h"
#include "../../engine/Text.h"

class InventoryState : public BaseState
{
	public:
		InventoryState(Window *window);
		~InventoryState();

		stateStatus update();
		void render();

	private:
		Window *window;
		Texture background;
		Font *font;

		Text *playername;
};

#endif //__INVENTORYSTATE_H_DEFINED__