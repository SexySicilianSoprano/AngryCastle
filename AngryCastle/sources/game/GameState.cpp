#include "GameState.h"

GameState::GameState(Window *window) :
	window(window),
	entity(nullptr),
	level(nullptr),
	camera(nullptr),
	font("fonts/AveriaSerif-Bold.ttf", 12),
	tooltip(new Text(&font, Color("white"))),
	signText(new Text(&font, Color("white"))),
	tooltip_s(""),
	signText_s("") {
		SDL_Rect hitbox = {0, 0, 10, 10};
		entity = new FallingEntity(0, 0, 10, 10, 1, hitbox);
		camera = new Camera(400, 240);
		camera->lock(entity);

		collection = new EntityCollection<Entity>;

		level = new Level(window, camera, collection);
		level->load("levels/lumbroff_01.tmx");

		SDL_Point spawnpoint = level->getLeftSpawn();
		entity->setPosition(spawnpoint.x, spawnpoint.y - 10);
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

	entity->setSpeed(1);
	if (Input::keyState(SDL_SCANCODE_SPACE)) {
		//entity->move(MovingEntity::UP);
		//entity->jump();
		entity->setSpeed(15);
	}

	if (Input::keyState(SDL_SCANCODE_W)) {
		entity->jump();
	}

	if (Input::keyState(SDL_SCANCODE_S)) {
		entity->move(MovingEntity::DOWN);
	}

	if (Input::keyState(SDL_SCANCODE_A)) {
		entity->move(MovingEntity::LEFT);
		//camera->frame.y += speed;
	} else if (Input::keyState(SDL_SCANCODE_D)) {
		entity->move(MovingEntity::RIGHT);
		//camera->frame.x += speed;
	}

	///printf("DesiredX>\t%d\nPlayerX>\t%d\n", entity->desiredX, entity->getX());

	//printf("Camera %d\\%d\n", camera->frame.x, camera->frame.y);
	//entity->update();
	entity->update(window->getDelta());

	//printf("Player position: x%d y%d\nDesired position: x%d y%d\n", entity->getX(), entity->getY(), entity->desiredX, entity->desiredY);

	//if(level->collides(entity)) {
	//	entity->velocity_y = 0;
//		entity->in_air = 0;
	//}

	hilight_tile = level->collides(entity);

	//printf("DesiredX>\t%d\nPlayerX>\t%d\n", entity->desiredX, entity->getX());

	entity->commitMovement();

	//SDL_Rect playerhb = entity->getHitbox();
	//printf("Player> x%d y%d\nHitbox> x%d y%d\nCamera> x%d y%d\n", entity->getX(), entity->getY(), playerhb.x, playerhb.y, camera->frame.x, camera->frame.y);

	level->update(entity);
	camera->update();

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

			level = new Level(window, camera, collection);
			level->load(level_name);

			SDL_Point spawnpoint = level->getLeftSpawn();
			camera->frame.x = spawnpoint.x;
			camera->frame.y = spawnpoint.y + camera->frame.h/2;
		}
	}

	if (camera->frame.x > level->getLevelWidth() - (camera->frame.w/2)) {
		std::string rightLevel = level->getRightmostLevel();

		if (!rightLevel.empty()) {
			level = new Level(window, camera, collection);
			level->load(rightLevel);
			
			SDL_Point spawnpoint = level->getLeftSpawn();
			entity->setPosition(spawnpoint.x, spawnpoint.y - 10);
		}

	}

	if (camera->frame.x < 0 - (camera->frame.w/2)-8) {
		std::string leftLevel = level->getLeftmostLevel();
		
		if (!leftLevel.empty()) {
			level = new Level(window, camera, collection);
			level->load(leftLevel);
			
			SDL_Point spawnpoint = level->getRightSpawn();
			entity->setPosition(spawnpoint.x, spawnpoint.y - 10);
		}
	}

	return status;
}

void GameState::render() {
	level->render(SIL_LAYER);
	level->render(BG_LAYER);
	level->render(GAME_LAYER);

	window->drawRect(entity->getX() - camera->frame.x,
					 entity->getY() - camera->frame.y,
					 entity->getW(),
					 entity->getH(),
					 Color("red"));

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

	if (!SDL_RectEmpty(&hilight_tile)) {
		window->drawRect(hilight_tile.x - camera->frame.x,
					 hilight_tile.y - camera->frame.y,
					 hilight_tile.w,
					 hilight_tile.h,
					 Color("magenta"));

		hilight_tile.x = 0;
		hilight_tile.y = 0;
		hilight_tile.w = 0;
		hilight_tile.h = 0;
	}
	
	level->render(FG_LAYER);

	if (tooltip_s.length() > 0) {
		tooltip->print(window, tooltip_s, 10, 10);
	}

	if (signText_s.length() > 0) {
		tooltip->print(window, signText_s, 100, 20);
	}
}