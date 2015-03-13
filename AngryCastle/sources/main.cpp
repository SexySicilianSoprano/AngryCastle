#include "Input.h"
#include "StateManager.h"
#include "GameState.h"
#include "Window.h"

#define SCREEN_TITLE "Escape From Earth"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_LOGICAL_WIDTH 256
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
	
	manager.changeState(GameState::instance());

	while (manager.isRunning()) {
		Input::update();

		manager.update();
		manager.render();
	}

	SDL::exit();
	return 0;
}