/**
 * Window.h
 *
 * Description:
 * Functionality for creating and manipulating a window.
 *
 * Example:
 * // Changes the title of the window to "My Application".
 * Window::setTitle("My Application");
 */

#ifndef __WINDOW_H_DEFINED__
#define __WINDOW_H_DEFINED__

#include "Timer.h"
#include "SDL.h"
#include <string>
#include "Color.h"

#define FRAMERATE 30
#define FPS_INTERVAL 1000

class Window {
public:
	Window(unsigned int new_width, unsigned int new_height,
		   unsigned int new_logical_width, unsigned int new_logical_height,
		   std::string new_title, bool is_fullscreen);
	~Window();
	void destroy();
	void resize(int new_width, int new_height, 
				std::string new_title, bool is_fullscreen);
	void refresh();
	void clear();
	void setTitle(std::string title);
	void fill(Color color);
	SDL_Renderer *getRenderer();
	Uint32 getDelta();
	int getFramerate();
	void minimize();
	void maximize();
	void restore();

private:
	unsigned int width;
	unsigned int height;
	unsigned int logical_width;
	unsigned int logical_height;
	SDL_Window *window;
	SDL_Renderer *renderer;

	Timer frametime_timer;
	Timer fpsTimer;
	Uint32 framerate;
	Uint32 frame_delay;
	Uint32 current_delta;
	int fps_current;
	int fps;
};

#endif