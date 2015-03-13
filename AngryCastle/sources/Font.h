/**
 * Font.h
 *
 * Description:
 * Font manager.
 *
 * Example:
 * --
 */

#ifndef __FONT_H_DEFINED__
#define __FONT_H_DEFINED__

#include "SDL.h"
#include <string>

class Font {
public:
	Font();
	Font(std::string font_name, int font_size);

	bool loadFromFile(std::string font_name, int font_size);
	TTF_Font *getFont();

private:
	TTF_Font *font;
};

#endif