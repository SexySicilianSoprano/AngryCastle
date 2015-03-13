/**
 * Texture.h
 *
 * Description:
 * For creating textures.
 *
 * Example:
 * 
 */

#ifndef __TEXTURE_H_DEFINED__
#define __TEXTURE_H_DEFINED__

#include "Window.h"

class Texture {
public:
	Texture(Window *window, std::string filename);
	~Texture();

	int getWidth();
	int getHeight();
	void crop(SDL_Rect rect);
	void render(int x, int y);
	void free();

private:
	SDL_Texture *loadImage(std::string filename);
	int width;
	int height;
	SDL_Rect clip_rect;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
};

#endif