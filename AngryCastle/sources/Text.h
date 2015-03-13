/**
 * Text.h
 *
 * Description:
 * Text manager.
 *
 * Example:
 * --
 */

#ifndef __TEXT_H_DEFINED__
#define __TEXT_H_DEFINED__

#include <string>
#include "Window.h"
#include "Font.h"

class Text {
public:
	Text();
	~Text();
	void setFont(Font *new_font);
	void setColor(Color new_color);
	void print(Window *window, std::string text, int x, int y);

private:
	int x;
	int y;
	SDL_Texture *texture;
	Font *font;
	Color color;
};

#endif