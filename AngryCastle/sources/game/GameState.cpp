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
		entity = new MovingEntity(0, 0, 10, 10, 2, hitbox);
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

	if (Input::keyState(SDL_SCANCODE_W)) {
		//entity->move(MovingEntity::UP);
		entity->move(MovingEntity::UP);
	}
	
	if (Input::keyState(SDL_SCANCODE_A)) {
		entity->move(MovingEntity::LEFT);
		//camera->frame.x -= speed;
	}

	if (Input::keyState(SDL_SCANCODE_S)) {
		entity->move(MovingEntity::DOWN);
		//camera->frame.y += speed;
	}

	if (Input::keyState(SDL_SCANCODE_D)) {
		entity->move(MovingEntity::RIGHT);
		//camera->frame.x += speed;
	}

	//printf("Camera %d\\%d\n", camera->frame.x, camera->frame.y);

	entity->update();

	if (!level->collides(entity)) {
		printf("!\n");
		entity->commitMovement();
	}

	SDL_Rect playerhb = entity->getHitbox();
	printf("Player> x%d y%d\nHitbox> x%d y%d\nCamera> x%d y%d\n", entity->getX(), entity->getY(), playerhb.x, playerhb.y, camera->frame.x, camera->frame.y);

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
			camera->frame.x = 15;
			camera->frame.y = 0;
		}

	}

	if (camera->frame.x < 0 - (camera->frame.w/2)-8) {
		std::string leftLevel = level->getLeftmostLevel();
		
		if (!leftLevel.empty()) {
			level = new Level(window, camera, collection);
			level->load(leftLevel);
			camera->frame.x = 15;
			camera->frame.y = 0;
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