/**
 * Input.h
 *
 * Description:
 * Input manager.
 *
 * Example:
 * Input::update();
 * Input::keyState(SDL_SCANCODE_A); // Will return true if 'A' key is pressed.
 * 
 * TODO(jouni):
 * - Switch the class from static to actually object-oriented
 */

#ifndef __INPUT_H_DEFINED__
#define __INPUT_H_DEFINED__

#define KEYBOARD_SIZE 282

#include "SDL.h"

class Input {
public:
	static void update();
	static bool keyState(int new_key);
	static bool shift();
	static bool ctrl();
	static bool alt();
	static void lock();
	static void unlock();

private:
	static bool key[KEYBOARD_SIZE];
	static bool is_locked;
	static const Uint8 *keyboard;
};

#endif