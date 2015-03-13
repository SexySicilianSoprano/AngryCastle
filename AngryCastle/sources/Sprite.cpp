/**
 * Sprite.cpp
 *
 */

#include "Sprite.h"

Sprite::Sprite(Window *window,
			   std::string filename,
			   int sprite_width,
			   int sprite_height):
	Texture(window, filename),
	index(0) {
	try {
		int spriteItems = 0;
		int columns = getWidth() / sprite_width;
		int rows = getHeight() / sprite_height;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				SDL_Rect rect = {j*sprite_width, i*sprite_height,
					             sprite_width, sprite_height};
				sprite_sheet.push_back(rect);
			}
		}
	} catch(...) {
		printf("Sprite: Error creating sprite.\n");
		return;
	}
}

Sprite::~Sprite() {
}

void Sprite::render(int x, int y) {
	// Index defines the section of the sprite sheet that will be rendered.
	crop(sprite_sheet[index]);
	Texture::render(x, y);
}

void Sprite::setIndex(int i) {
	if (i < 0) {
		index = 0;
	} else {
		index = i;
	}
}