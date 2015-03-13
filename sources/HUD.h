/**
 * HUD.h
 *
 * Description:
 * HUD manager.
 *
 * Example:
 * --
 */

#ifndef __HUD_H_DEFINED__
#define __HUD_H_DEFINED__

#include "Window.h"
#include "Sprite.h"
#include "Text.h"

class HUD {
public:
	HUD(Window *window);
	~HUD();	
	Sprite *weapon;	
	void setWeapon(int weapon_id);
	void setScore(int score);
	void render();
	void show();
	void hide();

private:	
	Text score_text;
	Text highscore_text;
	Text score_value;
	Text highscore_value;
	Font font;
	Color text_color;
	bool is_hidden;
	int current_score;
	int highscore;
	Window *window;
	Texture weapons;
	Sprite selected_weapon;
	int weapon_index;
};

#endif