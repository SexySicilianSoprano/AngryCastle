#ifndef __GAMESTATE_H_DEFINED__
#define __GAMESTATE_H_DEFINED__

#include "..//..//engine//BaseState.h"
#include "..//..//engine//Window.h"
#include "..//..//engine//Input.h"
#include "..//..//engine//Color.h"
#include "..//..//engine//Entity.h"
#include "..//..//engine//MovingEntity.h"
#include "..//..//engine//FallingEntity.h"
#include "..//..//engine//Level.h"
#include "..//..//engine//Font.h"
#include "..//..//engine//Text.h"
#include "..//..//engine//Player.h"
#include "..//HUD.h"

#include "../Enemies/Enemy.h"
#include "../Enemies/Skeleton.h"

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
//		EntityCollection<Enemy> *collection;
		std::vector<Enemy*> enemies;

		Player *player;
		Skeleton *skeleton;

		HUD *hud;
		Texture *background;

		Font font;
		Text *tooltip, *signText;
		std::string tooltip_s, signText_s;

		SDL_Rect hilight;
};

#endif // __GAMESTATE_H_DEFINED__