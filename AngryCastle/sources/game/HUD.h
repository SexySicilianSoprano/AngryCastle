/**
 * 
 * HUD.h
 */

#ifndef __HUD_H_DEFINED__
#define __HUD_H_DEFINED__

#include "../engine/Window.h"
#include "../engine/Texture.h"
#include "../engine/Player.h"

class HUD
{
	public:
		HUD(Window *window);
		~HUD();

		void render(Player *player);

	private:
		Texture *hud;
		Texture *subweapon;
		Window *window;
};

#endif //__HUD_H_DEFINED__