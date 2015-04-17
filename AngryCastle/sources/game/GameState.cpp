#include "GameState.h"

GameState::GameState(Window *window) :
	window(window),
	player(nullptr),
	level(nullptr),
	camera(nullptr),
	font("fonts/AveriaSerif-Bold.ttf", 12),
	tooltip(new Text(&font, Color("white"))),
	signText(new Text(&font, Color("white"))),
	tooltip_s(""),
	signText_s(""),
	test(nullptr)
	{
		SDL_Rect hitbox = {15, 16, 13, 27};
		player = new Player(window, 0, 0, 46, 43, 100, 1.8, hitbox);
		camera = new Camera(400, 240);
		camera->lock(player);

		collection = new EntityCollection<Entity>;

		level = new Level(window, camera, collection);
		level->load("levels/lumbroff_01.tmx");

		SDL_Point spawnpoint = level->getLeftSpawn();
		player->setPosition(spawnpoint.x, spawnpoint.y - player->getH());

		//test = new Animation(window, "graphics/character/player_idle.png", 
}

GameState::~GameState() {
}

stateStatus GameState::update() {
	stateStatus status;
	status.status = STATE_CONTINUE;
	status.prepend = false;

	if (Input::keyPressed(SDL_SCANCODE_ESCAPE)) {
		status.status = STATE_MENU;
	}

	player->update(window->getDelta());

	///printf("DesiredX>\t%d\nPlayerX>\t%d\n", entity->desiredX, entity->getX());

	//printf("Camera %d\\%d\n", camera->frame.x, camera->frame.y);
	//entity->update();

	//printf("Player position: x%d y%d\nDesired position: x%d y%d\n", entity->getX(), entity->getY(), entity->desiredX, entity->desiredY);

	//if(level->collides(entity)) {
	//	entity->velocity_y = 0;
//		entity->in_air = 0;
	//}

	level->collides(player);

	//printf("DesiredX>\t%d\nPlayerX>\t%d\n", entity->desiredX, entity->getX());

	player->commitMovement();

	//SDL_Rect playerhb = entity->getHitbox();
	//printf("Player> x%d y%d\nHitbox> x%d y%d\nCamera> x%d y%d\n", entity->getX(), entity->getY(), playerhb.x, playerhb.y, camera->frame.x, camera->frame.y);

	level->update(player);
	camera->update(level->getLevelWidth(), level->getLevelHeight());

	// Update tooltip and sign text
	tooltip_s  = level->tooltip;
	signText_s = level->signText;

	// 16 = tilesize
	// TODO(jouni): (camera->frame.w/2)+8 is only for testing, you need to change this in future!

	//printf("RIGHT: %d > %d\nLEFT:  %d < %d\n", camera->frame.x, (level->getLevelWidth() - (camera->frame.w/2)), camera->frame.x, 0 - (camera->frame.w/2)-8);

	if (Input::keyState(SDL_SCANCODE_RETURN)) {
		Exit *door = level->getCurrentDoor();

		if (door) {
			std::string level_name = door->level;

			// Clean up old level stuff
			delete level;
			delete collection;

			collection = new EntityCollection<Entity>;
			level = new Level(window, camera, collection);
			level->load(level_name);

			SDL_Point spawnpoint = level->getLeftSpawn();
			camera->frame.x = spawnpoint.x;
			camera->frame.y = spawnpoint.y + camera->frame.h/2;
		}
	}

	if (player->getX() > level->getLevelWidth()) {
		std::string rightLevel = level->getRightmostLevel();

		printf("Entering %s\n", rightLevel.c_str());

		if (!rightLevel.empty()) {
			// Clean up old level stuff
			delete level;
			delete collection;

			collection = new EntityCollection<Entity>;

			level = new Level(window, camera, collection);
			level->load(rightLevel);
			
			SDL_Point spawnpoint = level->getLeftSpawn();
			player->setPosition(spawnpoint.x, spawnpoint.y);
		}

	}
	
	if (player->getX() < -player->getW()) {
		std::string leftLevel = level->getLeftmostLevel();
		
		printf("Entering %s\n", leftLevel.c_str());

		if (!leftLevel.empty()) {
			// Clean up old level stuff
			delete level;
			delete collection;

			collection = new EntityCollection<Entity>;
			level = new Level(window, camera, collection);
			level->load(leftLevel);
			
			SDL_Point spawnpoint = level->getRightSpawn();
			player->setPosition(spawnpoint.x, spawnpoint.y - 10);
		}
	}
	return status;
}

void GameState::render() {
	level->render(SIL_LAYER);
	level->render(BG_LAYER);
	level->render(GAME_LAYER);

	player->render(camera);
	/*
	SDL_Rect hitbox = player->getHitbox();
	window->drawRect(hitbox.x - camera->frame.x,
					 hitbox.y - camera->frame.y,
					 hitbox.w,
					 hitbox.h,
					 Color("red"));
	*/
	/*
	SDL_Rect p_hb = entity->getHitbox();

	window->drawRect(p_hb.x - camera->frame.x,
					 p_hb.y - camera->frame.y,
					 p_hb.w,
					 p_hb.h,
					 Color("blue"));
	*/
	for (int i = 0; i < collection->length(); i++) {
		Entity *tmp = collection->get(i);

		window->drawRect(tmp->getX() - camera->frame.x,
						 tmp->getY() - camera->frame.y,
						 tmp->getW(),
						 tmp->getH(),
						 Color("blue"));
	}
	
	level->render(FG_LAYER);

	if (tooltip_s.length() > 0) {
		tooltip->print(window, tooltip_s, 10, 10);
	}

	if (signText_s.length() > 0) {
		tooltip->print(window, signText_s, 100, 20);
	}
}