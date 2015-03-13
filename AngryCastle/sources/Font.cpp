/**
 * Font.cpp
 *
 */

#include "Font.h"

Font::Font():
	font(nullptr) {
}

Font::Font(std::string font_name, int font_size) {
	loadFromFile(font_name, font_size);
}

bool Font::loadFromFile(std::string font_name, int font_size) {
	font = TTF_OpenFont(font_name.c_str(), font_size);

	if (!font) {
		printf("Couldn't load font! %s\n", TTF_GetError());
		return false;
	}

	return true;
}

TTF_Font* Font::getFont() {
	return font;
}