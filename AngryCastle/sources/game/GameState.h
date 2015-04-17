#ifndef __GAMESTATE_H_DEFINED__
#define __GAMESTATE_H_DEFINED__

#include "..//engine//BaseState.h"
#include "..//engine//Window.h"
#include "..//engine//Input.h"
#include "..//engine//Color.h"
#include "..//engine//Entity.h"
#include "..//engine//MovingEntity.h"
#include "..//engine//FallingEntity.h"
#include "..//engine//Level.h"
#include "..//engine//Font.h"
#include "..//engine//Text.h"
#include "..//engine//Player.h"

#include "..//engine//Animation.h"

class GameState : public BaseState {

	public:
		GameState(Window *window);
		~GameState();

		stateStatus update();
		void render();

	private:
		Animation *test;
		Window *window;
		Level *level;
		Camera *camera;
		EntityCollection<Entity> *collection;

		Player *player;

		Font font;
		Text *tooltip, *signText;
		std::string tooltip_s, signText_s;

		SDL_Rect hilight_tile;
};

#endif // __GAMESTATE_H_DEFINED__