/**
 * Window.cpp
 *
 */

#include "Window.h"

Window::Window(unsigned int new_width, unsigned int new_height,
			   unsigned int new_logical_width, unsigned int new_logical_height,
			   std::string new_title, bool is_fullscreen):
	window(nullptr),
	renderer(nullptr),
	width(new_width),
	height(new_height),
	logical_width(new_logical_width),
	logical_height(new_logical_height) {
	resize(width, height, new_title, is_fullscreen);
	frametime_timer.start();
	fpsTimer.start();
	current_delta = frametime_timer.getTicks();
	clear();
	refresh();
}

Window::~Window() {
	destroy();
}

void Window::destroy() {
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}

void Window::resize(int new_width, int new_height, 
					std::string new_title,
					bool is_fullscreen) {
	destroy();
	Uint32 window_flag;

	if (is_fullscreen) {
		window_flag = SDL_WINDOW_FULLSCREEN;
	} else {
		window_flag = SDL_WINDOW_SHOWN;
	}

	SDL_CreateWindowAndRenderer(new_width, new_height, 
								window_flag, 
								&window, &renderer);
	
	// Basic error handling that informs the user in the
	// case a window or a renderer could not be created.
	if (!window || !renderer) {
		throw "resize: Couldn't create SDL_Window or SDL_Renderer.";
		return;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	SDL_RenderSetLogicalSize(renderer, logical_width, logical_height);
	setTitle(new_title);

	width = new_width;
	height = new_height;
	
	if (width == 0 || height == 0) {
		throw "Window size is 0.";
	}

	setTitle(new_title);
}

void Window::refresh() {
	SDL_RenderPresent(renderer);
	fps_current++;
	int ticks = frametime_timer.getTicks();

	if (ticks < (1000 / FRAMERATE)) {
		SDL_Delay((1000 / FRAMERATE) - ticks);
	}

	current_delta = frametime_timer.getTicks();
	frametime_timer.start();
}

void Window::clear() {
	fill(Color("black"));
}

void Window::fill(Color color) {
	if (!renderer) {
		throw "fill: Renderer could not be found.";
		return;
	}

	SDL_SetRenderDrawColor(renderer,
						   color.r(),
						   color.g(),
						   color.b(),
						   color.a());

	SDL_RenderClear(renderer);
}

void Window::setTitle(std::string title) {
	if (!window) {
		throw "setTitle: Window could not be found.";
		return;
	}
	
	SDL_SetWindowTitle(window, title.c_str());
}

SDL_Renderer *Window::getRenderer() {
	if (!renderer) {
		throw "getRenderer: Renderer could not be found.";
		return nullptr;
	}

	return renderer;
}

Uint32 Window::getDelta() {
	return current_delta;
}

int Window::getFramerate() {
	if ( fpsTimer.getTicks() >= FPS_INTERVAL) {
		fps = fps_current;
		fps_current = 0;
		fpsTimer.start();
	}

	return fps;
}

void Window::minimize() {
	if (!window) {
		throw "minimize: Window could not be found";
		return;
	}

	SDL_MinimizeWindow(window);
}

void Window::maximize() {
	if (!window) {
		throw "maximize: Window could not be found";
		return;
	}

	SDL_MaximizeWindow(window);
}

void Window::restore() {
	if (!window) {
		throw "restore: Window could not be found";
		return;
	}

	SDL_RestoreWindow(window);
}
