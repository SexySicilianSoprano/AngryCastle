/**
 * Texture.cpp
 *
 */

#include "Texture.h"

Texture::Texture(Window *window, std::string filename):
	clip_rect() {
	renderer = window->getRenderer();
	try {
		texture = loadImage(filename);
	} catch(char const* exception) {
		printf("Error %s", exception);
	}
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

Texture::~Texture() {

}

SDL_Texture *Texture::loadImage(std::string filename) {
	SDL_Surface *surface = IMG_Load(filename.c_str());

	if (!surface) {
		char msg [256];
		sprintf_s(msg, "loadImage: Texture could not be loaded\n"
					   "IMG_LoadTexture: %s\n", IMG_GetError());
		throw msg;
		return false;
	}

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,
												  0xFF, 0, 0xFF));
	SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, surface);

	if (!newTexture) {
		char msg [256];
		sprintf_s(msg, "loadImage: Unable to create texture from %s!\n"
					   "SDL Error: %s\n", filename.c_str(), SDL_GetError());
		throw msg;
		return false;
	}

	SDL_FreeSurface(surface);
	return newTexture;
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}

void Texture::crop(SDL_Rect rect) {
	clip_rect.x = rect.x;
	clip_rect.y = rect.y;
	clip_rect.w = rect.w;
	clip_rect.h = rect.h;
}

void Texture::render(int x, int y) {
	if (clip_rect.w <= 0 && clip_rect.h <= 0) {
		SDL_Rect clip = {0, 0, width, height};
		clip_rect = clip;
	}
	
	if (!renderer || !texture) {
		throw "render: Couldn't find renderer or texture.";
		return;
	}
	
	/* TODO(juha): Can't check if SDL_Rect exists or not.
	if (clipRect ==  || destination) {
		throw "render: No clipRect or destination.";
		return;
	}*/

	SDL_Rect destination = {x, y, clip_rect.w, clip_rect.h};
	SDL_RenderCopy(renderer, texture, &clip_rect, &destination);
}

void Texture::free() {
	SDL_DestroyTexture(texture);
}