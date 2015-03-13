/**
 * Input.cpp
 *
 */

#include "Input.h"

bool Input::key[KEYBOARD_SIZE] = {0};
bool Input::is_locked = false;
const Uint8 *Input::keyboard = NULL;


void Input::update() {
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN: {
				keyboard = SDL_GetKeyboardState(nullptr);
				int scancode = event.key.keysym.scancode;
				key[scancode] = true;
							  }
							  break;

			case SDL_KEYUP: {
				keyboard = SDL_GetKeyboardState(nullptr);
				int scancode = event.key.keysym.scancode;
				key[scancode] = false;
							}
							break;

			default:
				break;
		}
	}
}

bool Input::keyState(int new_key) {
	if (is_locked) {
		return false;
	}

	if (new_key < 0 || new_key >= KEYBOARD_SIZE) {
		return false;
	}

	return key[new_key];
}

bool Input::shift() {
	return keyState(SDL_SCANCODE_LSHIFT) || keyState(SDL_SCANCODE_RSHIFT);
}

bool Input::ctrl() {
	return keyState(SDL_SCANCODE_LCTRL) || keyState(SDL_SCANCODE_RCTRL);
}

bool Input::alt() {
	return keyState(SDL_SCANCODE_LALT) || keyState(SDL_SCANCODE_RALT);
}

void Input::lock() {
	is_locked = true;
}

void Input::unlock() {
	is_locked = false;
}