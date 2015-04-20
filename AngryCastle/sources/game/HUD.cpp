/**
 *
 *	HUD.cpp
 */

#include "HUD.h"

HUD::HUD(Window *window):
	hud(new Texture(window, "graphics/ui/hud.png")),
	subweapon(nullptr),
	window(window)
{

}

HUD::~HUD() {
	delete hud;
	delete subweapon;
	delete window;
}

void HUD::render(Player *player) {
	// TODO(jouni): Get HP
	int hp = 100;
	// TODO(jouni): Get Mana
	int mana = 100;
	
	// TODO(jouni): Get Sanity
	int sanity = 100;
	
	// TODO(jouni): Get Subweapon, switch case, default to VOID
	int current_subweapon = 0;

	// HP					MAX
	//						___
	window->drawRect(17, 6, 118, 6, Color(172, 50, 50));
	
	// MANA					 MAX
	//						 ___
	window->drawRect(24, 13, 107, 5, Color(118, 66, 138));
	
	// SANITY				 MAX
	//						 ___
	window->drawRect(14, 20, 120, 5, Color(132, 126, 135));

	hud->render(2, 2);

	switch (current_subweapon)
	{
		case 1:
			subweapon = new Texture(window, "");
			subweapon->render(135, 4);
			break;
			
		case 2:
			subweapon = new Texture(window, "");
			subweapon->render(135, 4);
			break;

		case 3:
			subweapon = new Texture(window, "");
			subweapon->render(135, 4);
			break;

		case 4:
			subweapon = new Texture(window, "");
			subweapon->render(135, 4);
			break;

		default:
			break;
	}
}