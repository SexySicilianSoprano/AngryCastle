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
		level->load("levels/hamond_02.tmx");
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

	if (Input::keyState(SDL_SCANCODE_RETURN)) {
		
	}

	printf("Camera %d\\%d\n", camera->frame.x, camera->frame.y);

	entity->update();
	entity->commitMovement();

	//camera->update(entity->getX(), entity->getY());

	// 16 = tilesize
	// TODO(jouni): (camera->frame.w/2)+8 is only for testing, you need to change this in future!
	if (level->pointToTile(entity->getX()) > level->getLevelWidth() - (camera->frame.w/2)+8) {
		level = new Level(window, camera);
		level->load(level->getRightmostLevel());
		camera->frame.x = 15;
		camera->frame.y = 0;
	}

	if (level->pointToTile(entity->getX()) < 0 - (camera->frame.w/2)+8) {
		level = new Level(window, camera);
		level->load(level->getLeftmostLevel());
		camera->frame.x = 15;
		camera->frame.y = 0;
	}

	return status;
}

void GameState::render() {
	level->render(SIL_LAYER);
	level->render(BG_LAYER);
	level->render(GAME_LAYER);

	window->drawRect(entity->getX(),
					 entity->getY(),
					 entity->getW(),
					 entity->getH(),
					 Color("red"));

	level->render(FG_LAYER);
}