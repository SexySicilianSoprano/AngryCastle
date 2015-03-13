/**
 * HUD.cpp
 *
 */

#include "HUD.h"

HUD::HUD(Window *window):
	window(window),
	weapons(window, "hud_icons_bw.png"),
	selected_weapon(window, "hud_icons.png", 20, 20),
	weapon_index(0),
	is_hidden(false),
	score_text(),
	highscore_text(),
	current_score(0),
	highscore(0),
	font("PressStart2P.ttf", 7),
	text_color("black") {
		score_text.setFont(&font);
		score_text.setColor(text_color);
		highscore_text.setFont(&font);
		highscore_text.setColor(text_color);
		score_value.setFont(&font);
		score_value.setColor(text_color);
		highscore_value.setFont(&font);
		highscore_value.setColor(text_color);
		selected_weapon.setIndex(weapon_index);
}

HUD::~HUD() {

}

void HUD::setWeapon(int weapondID) {
	weapon_index = weapondID;
	selected_weapon.setIndex(weapon_index);
}

void HUD::setScore(int score) {
	score = 0;
	current_score = score;
}

void HUD::render() {
	if (is_hidden) {
		return;
	}

	score_text.print(window, "SCORE", 10, 10);
	highscore_text.print(window, "HI SCORE", 150, 10);

	char buffer[64];
	_itoa_s(current_score, buffer, 64);
	score_value.print(window, buffer, 60, 10);

	_itoa_s(highscore, buffer, 64);
	highscore_value.print(window, buffer, 220, 10);

	weapons.render(48, 220);
	selected_weapon.render(48 + (weapon_index * 20), 220);
}

void HUD::show() {
	is_hidden = false;
}

void HUD::hide() {
	is_hidden = true;
}