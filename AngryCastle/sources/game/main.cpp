#include "..//engine//SDL.h"
#include "..//engine//Input.h"
#include "..//engine//StateManager.h"
#include "GameState.h"
#include "..//engine//Window.h"

#define SCREEN_TITLE "Angry Castle - pre-release"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_LOGICAL_WIDTH 400
#define SCREEN_LOGICAL_HEIGHT 240

int main(int argc, char* args[]) {
	SDL::init();

	Window window(SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SCREEN_LOGICAL_WIDTH,
				SCREEN_LOGICAL_HEIGHT,
				SCREEN_TITLE,
				false);

	StateManager manager(&window);

	manager.run();

	SDL::exit();
	return 0;
}
