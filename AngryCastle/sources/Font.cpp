#include "Font.h"

Font::Font():
	font(nullptr)
{ }

Font::~Font() {
	TTF_CloseFont(font);
	font = NULL;
}

Font::Font(std::string fontName, int fontSize) {
	loadFromFile(fontName, fontSize);
}

bool Font::loadFromFile(std::string fontName, int fontSize) {
	font = TTF_OpenFont(fontName.c_str(), fontSize);

	if (!font) {
		printf("Couldn't load font! %s\n", TTF_GetError());
		return false;
	}

	return true;
}

TTF_Font* Font::getFont() {
	return font;
}