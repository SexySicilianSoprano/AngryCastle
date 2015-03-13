/**
 * Sprite.h
 *
 * Description:
 * For creating sprites.
 *
 * Example:
 * // Renders the sprite to position 10, 10 from top left.
 * Sprite::render(10, 10);
 */

#ifndef __SPRITE_H_DEFINED__
#define __SPRITE_H_DEFINED__

#include <vector>
#include "Texture.h"
#include "Window.h"

class Sprite : public Texture {
public:
	Sprite(Window *window, std::string filename,
		   int sprite_width, int sprite_height);
	virtual ~Sprite();
	void render(int x, int y);
	void setIndex(int i);

private:
	Window *window;
	int width;
	int height;
	int index;
	std::vector<SDL_Rect> sprite_sheet;
};

#endif