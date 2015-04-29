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

		collection = new EntityCollection<Entity>;

		level = new Level(window, camera, collection);
		level->load("levels/lumbroff_01.tmx");

		SDL_Point spawnpoint = level->getLeftSpawn();

		player->boundbox.x = spawnpoint.x;
		player->boundbox.y = spawnpoint.y - player->hitbox.h;
		player->commitMovement();

		collection->push(Skeleton(window, player, Rectangle(300, 100, 13, 26), 3, 100));
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

		player->update(collection);


		// skeleton->update(player);

		// Correct player position
		level->collides(player);
		// level->collides(skeleton);

		// Commit player movement
		player->commitMovement();
		// skeleton->commitMovement();

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
				delete collection;
				delete camera;

				camera = new Camera(400, 240);
				camera->lock(player);
				collection = new EntityCollection<Entity>;
				level = new Level(window, camera, collection);
				level->load(rightLevel);

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
				delete collection;
				delete camera;

				camera = new Camera(400, 240);
				camera->lock(player);
				collection = new EntityCollection<Entity>;
				level = new Level(window, camera, collection);
				level->load(leftLevel);

				SDL_Point spawnpoint = level->getRightSpawn();
				player->boundbox.x = spawnpoint.x - (player->hitbox.w);
				player->boundbox.y = spawnpoint.y - player->hitbox.h;
			}
		}

		if (Input::keyState(SDL_SCANCODE_RETURN)) {
			Exit *door = level->getCurrentDoor();

			if (door) {
				std::string level_name = door->level;

				// Clean up old level stuff
				delete level;
				delete collection;
				delete camera;

				camera = new Camera(400, 240);
				camera->lock(player);
				collection = new EntityCollection<Entity>;
				level = new Level(window, camera, collection);
				level->load(level_name);

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
/*
	SDL_Rect hitbox = (SDL_Rect) skeleton->hitbox;
	window->drawRect(hitbox.x - camera->frame.x,
					 hitbox.y - camera->frame.y,
					 hitbox.w,
					 hitbox.h,
					 Color("red"));
*/
	// skeleton->render(camera);
/*
	for (int i = 0; i < collection->length(); i++) {
		Entity *tmp = collection->get(i);

		window->drawRect(tmp->getX() - camera->frame.x,
						 tmp->getY() - camera->frame.y,
						 tmp->getW(),
						 tmp->getH(),
						 Color("blue"));
	}
*/
	level->render(FG_LAYER);

	if (tooltip_s.length() > 0) {
		tooltip->print(window, tooltip_s, 10, 10);
	}

	if (signText_s.length() > 0) {
		tooltip->print(window, signText_s, 100, 20);
	}

	hud->render(player);
}