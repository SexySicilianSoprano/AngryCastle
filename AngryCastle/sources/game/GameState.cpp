#include "GameState.h"

GameState::GameState(Window *window) :
	window(window),
	entity(nullptr),
	level(nullptr),
	camera(nullptr) {
		SDL_Rect hitbox = {0, 0, 10, 10};
		entity = new MovingEntity(200, 120, 10, 10, 5, hitbox);
		camera = new Camera(400, 240);

		level = new Level(window, camera);
		level->load("levels/lumbroff_01.tmx");
}

GameState::~GameState() {
}

stateStatus GameState::update() {
	stateStatus status;
	status.status = STATE_CONTINUE;
	status.prepend = false;

	int speed = 3;

	if (Input::keyPressed(SDL_SCANCODE_ESCAPE)) {
		status.status = STATE_MENU;
	}

	if(Input::shift()) {
		speed = 15;
	}

	if (Input::keyState(SDL_SCANCODE_W)) {
		//entity->move(MovingEntity::UP);
		camera->frame.y -= speed;
	}
	
	if (Input::keyState(SDL_SCANCODE_A)) {
		//entity->move(MovingEntity::LEFT);
		camera->frame.x -= speed;
	}

	if (Input::keyState(SDL_SCANCODE_S)) {
		//entity->move(MovingEntity::DOWN);
		camera->frame.y += speed;
	}

	if (Input::keyState(SDL_SCANCODE_D)) {
		//entity->move(MovingEntity::RIGHT);
		camera->frame.x += speed;
	}

	entity->update();
	entity->commitMovement();

	//camera->update(entity->getX(), entity->getY());

	// 16 = tilesize
	if (level->pointToTile(entity->getX()) > level->getLevelWidth()) {
		level = new Level(window, camera);
		level->load(level->getRightmostLevel());
		camera->frame.x = 15;
		camera->frame.y = 0;
	}

	if (level->pointToTile(entity->getX()) < 0) {
		printf("Level at left\n");
	}

	return status;
}

void GameState::render() {
	
	level->render();

	window->drawRect(entity->getX(),
					 entity->getY(),
					 entity->getW(),
					 entity->getH(),
					 Color("red"));
}