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

class GameState : public BaseState {

	public:
		GameState(Window *window);
		~GameState();

		stateStatus update();
		void render();

	private:
		Window *window;
		Level *level;
		Camera *camera;
		EntityCollection<Entity> *collection;

		FallingEntity *entity;

		Font font;
		Text *tooltip, *signText;
		std::string tooltip_s, signText_s;

		SDL_Rect hilight_tile;
};

#endif // __GAMESTATE_H_DEFINED__