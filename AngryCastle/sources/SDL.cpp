/**
 * SDL.cpp
 *
 */

#include "SDL.h"

bool SDL::init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf ("SDL couldn't initialize Video or Audio, SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	if (TTF_Init() == -1) {
		printf("SDL couldn't initialize TTF, SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		printf("SDL couldn't initialize OpenAudio, SDL Error: %s\n", Mix_GetError());
		success = false;
	}
	
	Mix_AllocateChannels(64);
	return success;
}

void SDL::exit() {
	Mix_AllocateChannels(0);
	Mix_CloseAudio();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}