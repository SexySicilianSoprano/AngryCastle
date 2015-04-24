#include "Window.h"

Window::Window(int width, int height, int logical_width, int logical_height, std::string title, bool fullscreen):
	window(nullptr),
	renderer(nullptr),
	width(width),
	height(height),
	logical_width(logical_width),
	logical_height(logical_height),
	originalWidth(width),
	originalHeight(height),
	fullscreen(fullscreen),
	current_delta(0)
{
	resize(title, width, height, fullscreen);

	frametimeTimer.start();
	fpsTimer.start();

	current_delta = frametimeTimer.getTicks();

	clear();
	refresh();
}

Window::~Window()
{
	destroy();
}

void Window::destroy()
{
	if (this->renderer)
	{
		SDL_DestroyRenderer(this->renderer);
		this->renderer = nullptr;
	}

	if (this->window)
	{
		SDL_DestroyWindow(this->window);
		this->window = nullptr;
	}
}

void Window::resize(std::string title, int width, int height, bool fullscreen)
{
	destroy();

	Uint32 window_flag;

	this->fullscreen = fullscreen;

	if (fullscreen)	{
		window_flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
	} else {
		window_flag = SDL_WINDOW_SHOWN;
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  width, height, window_flag);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//SDL_CreateWindowAndRenderer(width, height, window_flag, &window, &renderer);

	// NOTE(jouni): Perus virhetarkistusta; jos window tai renderer ei ssaa arvoa,
	// ei anneta ohjelman vaan raa'asti kaatua vaan ilmotetaan siitä käyttäjälle.
	if (!window || !renderer)
	{
		printf("Window and or renderer failed\n");
		printf("SDL Error: %s\n", SDL_GetError());
		return;
	}

	// Nearest-neighbour resize
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	SDL_RenderSetLogicalSize(renderer, logical_width, logical_height);
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

	// Scaling test
	//SDL_RenderSetScale(renderer, 8, 8);

	// Asetetaan title
	//setTitle(title);

	this->width = width;
	this->height = height;
}

void Window::clear()
{
	fill(Color("black"));
}

void Window::fill(Color color)
{
	SDL_SetRenderDrawColor(renderer,
						   color.r(),
						   color.g(),
						   color.b(),
						   color.a());

	SDL_RenderClear(renderer);
}

void Window::refresh()
{
	SDL_RenderPresent(renderer);

	fps_current++;

	int ticks = frametimeTimer.getTicks();

	if (ticks < (1000 / FRAMERATE)) {
		SDL_Delay((1000 / FRAMERATE) - ticks);
	}

	current_delta = frametimeTimer.getTicks();
	frametimeTimer.start();
}

void Window::drawRect(int X, int Y, int W, int H, Color color)
{
	SDL_Rect fillRect = { X, Y, W, H };
	SDL_SetRenderDrawColor(renderer, color.r(), color.g(), color.b(), color.a());
	SDL_RenderFillRect(renderer, &fillRect );
}

void Window::setTitle(std::string title)
{
	if (window)
	{
		SDL_SetWindowTitle(window, title.c_str());
	}
}

void Window::minimize()
{
	if (window)
	{
		SDL_MinimizeWindow(window);
	}
}

void Window::maximize()
{
	if (window)
	{
		SDL_MaximizeWindow(window);
	}
}

void Window::restore()
{
	SDL_RestoreWindow(this->window);
}

bool Window::isFullscreen()
{
	return fullscreen;
}

SDL_Renderer* Window::getRenderer()
{
	return renderer;
}

Uint32 Window::getDelta()
{
	return current_delta;
}

int Window::getFramerate()
{
	if (fpsTimer.getTicks() >= FPS_INTERVAL) {
		fps = fps_current;
		fps_current = 0;
		fpsTimer.start();
	}

	return fps;
}