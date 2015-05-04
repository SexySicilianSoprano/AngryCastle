#include "GameState.h"

GameState::GameState(Window *window) :
	window(window),
	player(nullptr),
	hud(new HUD(window)),
	level(nullptr),
	camera(nullptr),
	font("fonts/AveriaSerif-Bold.ttf", 12),
	tooltip(new Text(&font, Color("white"))),
	signText(new Text(&font, Color("white"))),
	tooltip_s(""),
	signText_s(""),
	test(nullptr),
	background(new Texture(window, "graphics/levels/lumbroff_background.png"))
	{
		player = new Player(window, Rectangle(0, 0, 13, 26), 5, 100);
		camera = new Camera(400, 240);
		camera->lock(player);

		level = new Level(window, camera);
		level->load("levels/lumbroff_01.tmx", enemies);

		SDL_Point spawnpoint = level->getLeftSpawn();

		player->boundbox.x = spawnpoint.x;
		player->boundbox.y = spawnpoint.y - player->hitbox.h;
		player->commitMovement();
}

GameState::~GameState() {
}

stateStatus GameState::update() {
	stateStatus status;
	status.status = STATE_CONTINUE;
	status.prepend = false;

	if (player->isDead()) {
		status.status = STATE_GAMEOVER;
	} else {
		if (Input::keyPressed(SDL_SCANCODE_ESCAPE)) {
			status.prepend = true;
			status.status = STATE_MENU;
		}

		if (Input::keyPressed(SDL_SCANCODE_I)) {
			status.prepend = true;
			status.status = STATE_INVENTORY;
		}

		if (Input::keyPressed(SDL_SCANCODE_K)) {
			player->damage(1);
		}
		// Entity updates
		player->update();

		for(std::vector<Enemy*>::iterator it = enemies.begin();
			it != enemies.end(); it++) {

			SDL_Rect tmp_hb = (*it)->hitbox;
			SDL_Rect wep_hb = player->weapon_hitbox;

			if (SDL_HasIntersection(&tmp_hb, &wep_hb)) {
				(*it)->damage(10);
			}

			if ((*it)->isDead()) {
				it = enemies.erase(it);
			}

			SDL_Rect plr_hb = player->hitbox;
			SDL_Rect enemy_wep_hb = (*it)->weapon_hitbox;

			if (SDL_HasIntersection(&plr_hb, &enemy_wep_hb)) {
				player->damage(1);
			}

			(*it)->update(player);
		}

		// Correct player position
		level->collides(player);
		player->commitMovement();

		for(std::vector<Enemy*>::iterator it = enemies.begin();
			it != enemies.end(); it++) {
			level->collides((*it));
			(*it)->commitMovement();
		}

		level->update(player);
		camera->update(level->getLevelWidth(), level->getLevelHeight());

		// Update tooltip and sign text
		tooltip_s  = level->tooltip;
		signText_s = level->signText;

		// TODO(jouni): Move these to level->update();
		if ((player->boundbox.x+2) > level->getLevelWidth()) {
			std::string rightLevel = level->getRightmostLevel();

			printf("Entering %s\n", rightLevel.c_str());

			if (!rightLevel.empty()) {
				// Clean up old level stuff
				delete level;
				delete camera;

				camera = new Camera(400, 240);
				camera->lock(player);
				level = new Level(window, camera);
				level->load(rightLevel, enemies);

				SDL_Point spawnpoint = level->getLeftSpawn();
				player->boundbox.x = 4;
				player->boundbox.y = spawnpoint.y - player->hitbox.h;
			}

		}

		if (player->boundbox.x < -(player->boundbox.w+2)) {
			std::string leftLevel = level->getLeftmostLevel();

			printf("Entering %s\n", leftLevel.c_str());

			if (!leftLevel.empty()) {
				// Clean up old level stuff
				delete level;
				delete camera;

				camera = new Camera(400, 240);
				camera->lock(player);
				level = new Level(window, camera);
				level->load(leftLevel, enemies);

				SDL_Point spawnpoint = level->getRightSpawn();
				player->boundbox.x = spawnpoint.x - (player->hitbox.w+2);
				player->boundbox.y = spawnpoint.y - player->hitbox.h;
			}
		}

		if (Input::keyState(SDL_SCANCODE_RETURN)) {
			Exit *door = level->getCurrentDoor();

			if (door) {
				std::string level_name = door->level;

				// Clean up old level stuff
				delete level;
				delete camera;

				camera = new Camera(400, 240);
				camera->lock(player);
				level = new Level(window, camera);
				level->load(level_name	, enemies);

				SDL_Point spawnpoint = level->getLeftSpawn();
				player->boundbox.x = spawnpoint.x;
				player->boundbox.y = spawnpoint.y - player->hitbox.h;
				player->commitMovement();
			}
		}
	}

	return status;
}

void GameState::render() {
	background->render(0, 0);
	level->render(SIL_LAYER);
	level->render(BG_LAYER);
	level->render(GAME_LAYER);

	player->render(camera);

	SDL_Rect hitbox = (SDL_Rect) player->weapon_hitbox;
	window->drawRect(hitbox.x - camera->frame.x,
					 hitbox.y - camera->frame.y,
					 hitbox.w,
					 hitbox.h,
					 Color("red"));
	// skeleton->render(camera);
/*
	for (int i = 0; i < enemies.length(); i++) {
		Entity *tmp = enemies.get(i);

		window->drawRect(tmp->getX() - camera->frame.x,
						 tmp->getY() - camera->frame.y,
						 tmp->getW(),
						 tmp->getH(),
						 Color("blue"));
	}
*/

	for(std::vector<Enemy*>::iterator it = enemies.begin();
		it != enemies.end(); it++) {
		(*it)->render(camera);

		SDL_Rect hitbox = (SDL_Rect) (*it)->weapon_hitbox;
		window->drawRect(hitbox.x - camera->frame.x,
						 hitbox.y - camera->frame.y,
						 hitbox.w,
						 hitbox.h,
						 Color("red"));
	}

	level->render(FG_LAYER);

	if (tooltip_s.length() > 0) {
		tooltip->print(window, tooltip_s, 10, 10);
	}

	if (signText_s.length() > 0) {
		tooltip->print(window, signText_s, 100, 20);
	}

	hud->render(player);
}