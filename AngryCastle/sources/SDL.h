/**
 * SDL.h
 *
 * Description:
 * Wrapper class to implementing SDL
 *
 * Example:
 * SDL::init(); // Initializes the SDL
 */

#ifndef __SDL_H_DEFINED__
#define __SDL_H_DEFINED__

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define UNUSED(x) ((void)(x))

namespace SDL {
	bool init();
	void exit();
};

#endif