#include "Level.h"

Level::Level(Window *window, Camera *camera, EntityCollection<Entity> *collection):
	window(window),
	camera(camera),
	collection(collection),
	currentDoor(nullptr),
	leftExit(nullptr),
	rightExit(nullptr)
{
}

Level::~Level()
{/*
	delete window;
	delete camera;
	delete collection;

	delete currentDoor;
	delete leftExit;
	delete rightExit;

	delete levelTileSheet;
*/
}

void Level::load(std::string level_name)
{
	// Loads the level document
	result = levelDocument.load_file(level_name.c_str());

	if (!result) {
		printf("Failed to load level %s.\n", level_name.c_str());
		return;
	}

	// Level size stuff
	tileSize = atoi(levelDocument.child("map").attribute("tilewidth").value());
	levelWidth = atoi(levelDocument.child("map").attribute("width").value());
	levelHeight = atoi(levelDocument.child("map").attribute("height").value());

	leftExit = new Exit();
	rightExit = new Exit();

	// Parse map data
	pugi::xml_node map_properties = levelDocument.child("map").child("properties");
	for(pugi::xml_node_iterator iterator = map_properties.begin();
		iterator != map_properties.end();
		++iterator)
	{
		std::string propertyName  = iterator->attribute("name").value();
		std::string propertyValue = iterator->attribute("value").value();

		if (propertyName.compare("exitLeft") == 0) {
			leftExit->level = propertyValue;
		}

		if (propertyName.compare("exitRight") == 0) {
			rightExit->level = propertyValue;
		}

		if (propertyName.compare("spawnLeft") == 0) {
			leftExit->spawnpoint = atoi(propertyValue.c_str());
		}

		if (propertyName.compare("spawnRight") == 0) {
			rightExit->spawnpoint = atoi(propertyValue.c_str());
		}
	}

	// Get layer and object nodes
	SilhouetteLayer = levelDocument.child("map").find_child_by_attribute("name", "SilhouetteLayer").child("data");
	BackgroundLayer = levelDocument.child("map").find_child_by_attribute("name", "BackgroundLayer").child("data");
	GameLayer		= levelDocument.child("map").find_child_by_attribute("name", "GameLayer").child("data");
	ForegroundLayer = levelDocument.child("map").find_child_by_attribute("name", "ForegroundLayer").child("data");
	triggerNode		= levelDocument.child("map").find_child_by_attribute("name", "Triggers");
	actorNode		= levelDocument.child("map").find_child_by_attribute("name", "Actors");

	// Load level tileset
	std::string tileSet = levelDocument.child("map").child("tileset").child("image").attribute("source").value();
	// Correct tileset path
	std::string prefix("../");
	if (!tileSet.compare(0, prefix.size(), prefix)) {
		tileSet = tileSet.substr(prefix.size()).c_str();
	}

	levelTileSheet = new Sprite(window, tileSet, tileSize, tileSize);

	int iteratorCount = 0;
	std::vector<int> levelRow;

	// Parse layers
	for(int i = 0; i < LAYER_COUNT; i++) {
		pugi::xml_node *tempLayer;
		std::vector<std::vector<int>> *tempData;

		switch (i)
		{
			case SIL_LAYER:
				tempLayer = &SilhouetteLayer;
				tempData = &SilhouetteData;
				break;

			case BG_LAYER:
				tempLayer = &BackgroundLayer;
				tempData = &BackgroundData;
				break;

			case GAME_LAYER:
				tempLayer = &GameLayer;
				tempData = &GameData;
				break;

			case FG_LAYER:
				tempLayer = &ForegroundLayer;
				tempData = &ForegroundData;
				break;

			default:
				break;
		}

		for(pugi::xml_node_iterator iterator = tempLayer->begin();
			iterator != tempLayer->end();
			++iterator)
		{
			iteratorCount++;

			// Add tile id to
			int gid = atoi(iterator->attribute("gid").value());
			levelRow.push_back(gid);

			// NOTE(juha): Kun päästään kentän loppuun, vaihdetaan riviä.
			if (iteratorCount % levelWidth == 0)
			{
				tempData->push_back(levelRow);
				levelRow.clear();
			}
		}
	}

	// Parse actors
	for(pugi::xml_node_iterator iterator = actorNode.begin();
		iterator != actorNode.end();
		++iterator)
	{
		std::string type = iterator->attribute("type").value();

		if (type.compare("spawn") == 0) {
			std::string spawn_type = iterator->attribute("name").value();
			int spawn_x = atoi(iterator->attribute("x").value());
			int spawn_y = atoi(iterator->attribute("y").value());

			if (spawn_type.compare("playerSpawnLeft") == 0) {
				leftSpawn.x = spawn_x;
				leftSpawn.y = spawn_y;
			}

			if (spawn_type.compare("playerSpawnRight") == 0) {
				rightSpawn.x = spawn_x;
				rightSpawn.y = spawn_y;
			}

			if (spawn_type.compare("playerSpawnStart") == 0) {
				startSpawn.x = spawn_x;
				startSpawn.y = spawn_y;
			}
		}

		if (type.compare("npcSpawn") == 0) {
			std::string type   = iterator->child("properties").find_child_by_attribute("name", "npcType").attribute("value").value();
			std::string script = iterator->child("properties").find_child_by_attribute("name", "script").attribute("value").value();

			int npc_x = atoi(iterator->attribute("x").value());
			int npc_y = atoi(iterator->attribute("y").value());

			// NOTE(jouni): **Factory creates entity of given type**
			// int x, int y, int w, int h, SDL_Rect hitbox_offset
			Entity entity(Rectangle(npc_x, npc_y, 10, 10));
			collection->push(entity);
		}

		if (type.compare("enemySpawn") == 0) {
			std::string type   = iterator->child("properties").find_child_by_attribute("name", "enemyType").attribute("value").value();

			int enemy_x = atoi(iterator->attribute("x").value());
			int enemy_y = atoi(iterator->attribute("y").value());

			// NOTE(jouni): **Factory creates entity of given type**
			// int x, int y, int w, int h, SDL_Rect hitbox_offset
			Entity entity(Rectangle(enemy_x, enemy_y, 20, 20));
			collection->push(entity);
		}

		if (type.compare("item") == 0) {
			std::string type   = iterator->child("properties").find_child_by_attribute("name", "itemType").attribute("value").value();

			int npc_x = atoi(iterator->attribute("x").value());
			int npc_y = atoi(iterator->attribute("y").value());

			// NOTE(jouni): **Factory creates entity of given type**
			// int x, int y, int w, int h, SDL_Rect hitbox_offset
			Entity entity(Rectangle(npc_x, npc_y, 5, 5));
			collection->push(entity);
		}
	}
}

void Level::update(Entity *entity) {
		tooltip = "";
		signText = "";
		currentDoor = nullptr;

		for(pugi::xml_node_iterator iterator = triggerNode.begin();
			iterator != triggerNode.end();
			++iterator)
		{
			int x = atoi(iterator->attribute("x").value());
			int y = atoi(iterator->attribute("y").value());
			int w = atoi(iterator->attribute("width").value());
			int h = atoi(iterator->attribute("height").value());

			SDL_Rect trigger_area = {x, y, w, h};
			SDL_Rect entity_area  = (SDL_Rect) entity->hitbox;
			SDL_Rect result_area  = {0, 0, 0, 0};

			if (SDL_IntersectRect(&trigger_area, &entity_area, &result_area)) {
				std::string type = iterator->attribute("type").value();

				if (type.compare("sign") == 0) {
					signText = iterator->child("properties").child("property").attribute("value").value();
					printf("%s\n", signText.c_str());
				}

				if (type.compare("door") == 0) {
					tooltip = "Press [W] to good luck";
					std::string levelName = iterator->child("properties")
											.find_child_by_attribute("name", "changeLevel").
											attribute("value").value();
					std::string levelPath = "levels/" + levelName;
					currentDoor = new Exit;

					currentDoor->level = levelPath;
					currentDoor->spawnpoint = SPAWN_LEFT;
				}
			}
		}
}

// TODO(jouni): Muuttujaksi kameran X
void Level::render(int layer)
{
	std::vector<std::vector<int>>::iterator row;
	std::vector<int>::iterator col;
	std::vector<std::vector<int>> *data;

	switch (layer)
	{
		case SIL_LAYER:
			data = &SilhouetteData;
			break;

		case BG_LAYER:
			data = &BackgroundData;
			break;

		case GAME_LAYER:
			data = &GameData;
			break;

		case FG_LAYER:
			data = &ForegroundData;
			break;

		default:
			break;
	}

	int tiles_y = camera->frame.h / tileSize + 1;
	int start_tile_y = (camera->frame.y / tileSize);
	if (start_tile_y < 0) {
		start_tile_y = 0;
	}

	int tiles_x = (camera->frame.w / tileSize) + 1;
	int start_tile_x = (camera->frame.x / tileSize);
	if (start_tile_x < 0) {
		start_tile_x = 0;
	}

	std::vector<std::vector<int>>::iterator row_begin = data->begin() + start_tile_y;
	std::vector<std::vector<int>>::iterator row_end;

	if (start_tile_y + tiles_y < data->size()) {
		row_end = data->begin() + start_tile_y + tiles_y;
	} else {
		row_end = data->end();
	}

	for (row = row_begin; row != row_end; ++row) {
		std::vector<int>::iterator col_begin = row->begin() + start_tile_x;
		std::vector<int>::iterator col_end = row->end();
		if (start_tile_x + tiles_x < row->size()) {
			col_end = row->begin() + start_tile_x + tiles_x;
		}

		for (col = col_begin; col != col_end; ++col) {
			int X = col - row->begin();
			int Y = row - data->begin();
			if ((*col) != 0) {
				levelTileSheet->setIndex(*col-1);
				int frameX = (camera->frame.x % 2 == 0) ? camera->frame.x : camera->frame.x + 1;
				levelTileSheet->render(X*tileSize - frameX, Y*tileSize - camera->frame.y);
			}
		}
	}
}

// In pixels
int Level::getLevelWidth()
{
	return levelWidth*tileSize;
}

int Level::getLevelHeight()
{
	return levelHeight*tileSize;
}

int Level::getTile(int x, int y)
{
	if (y >= 0 &&
		x >= 0 &&
		y < GameData.size()*tileSize &&
		x < GameData[0].size()*tileSize)
	{
		return (GameData[y/tileSize][x/tileSize]);
	}

	return 0;
}

SDL_Rect Level::pointToTile(int x, int y) {
	int correction_x = x % tileSize;
	int correction_y = y % tileSize;

	int tile_x = x - correction_x;
	int tile_y = y - correction_y;

	SDL_Rect result = {tile_x, tile_y, tileSize, tileSize};

	return result;
}

std::string Level::getRightmostLevel() {
	if (rightExit->level.empty()) {
		return "";
	}

	return "levels/" + rightExit->level;
}

std::string Level::getLeftmostLevel() {
	if (leftExit->level.empty()) {
		return "";
	}

	return "levels/" + leftExit->level;
}

Exit *Level::getCurrentDoor() {
	if (currentDoor) {
		return currentDoor;
	}

	return nullptr;
}

SDL_Point Level::getRightSpawn() {
	return rightSpawn;
}

SDL_Point Level::getLeftSpawn() {
	return leftSpawn;
}

SDL_Point Level::getStartSpawn() {
	return startSpawn;
}

void Level::collides(MovingEntity *entity)
{
	Rectangle old_entity = entity->hitbox;
	Rectangle new_entity = entity->boundbox;
	new_entity.w = old_entity.w;
	new_entity.h = old_entity.h;

	// Get the area of tiles considered for collision
	SDL_Point min_tile_xy = {std::min(old_entity.TopLeft().x, new_entity.TopLeft().x),
							 std::min(old_entity.TopLeft().y, new_entity.TopLeft().y)};
	SDL_Point max_tile_xy = {std::max(old_entity.BottomRight().x, new_entity.BottomRight().x),
							 std::max(old_entity.BottomRight().y, new_entity.BottomRight().y)};

	int min_tile_x = (min_tile_xy.x / tileSize) - 1;
	int min_tile_y = (min_tile_xy.y / tileSize) - 1;
	int max_tile_x = (max_tile_xy.x / tileSize) + 1;
	int max_tile_y = (max_tile_xy.y / tileSize) + 1;

	SDL_Rect tmpbound = (SDL_Rect) new_entity;

	double target_movement = getLineLength(old_entity.x, old_entity.y, new_entity.x, new_entity.y);

	for (int y_tile = min_tile_y; y_tile <= max_tile_y; y_tile++) {
		for (int x_tile = min_tile_x; x_tile <= max_tile_x; x_tile++) {
			SDL_Rect tmp = {(x_tile * tileSize),
							(y_tile * tileSize),
							tileSize,
							tileSize};
			// SDL_Rect tmp = {y_tile, x_tile, tileSize + old_entity.w, tileSize + old_entity.h};
			// printf("tile[%d][%d]: x%d y%d w%d h%d\n", x_tile, y_tile, tmp.x, tmp.y, tmp.w, tmp.h);

			if (SDL_HasIntersection(&tmp, &tmpbound) &&
				getTile(x_tile * tileSize, y_tile * tileSize) != 0) {

				SDL_Rect result;
				SDL_IntersectRect(&tmp, &tmpbound, &result);
				printf("result w%d h%d\n", result.w, result.h);
				
				if (result.w > result.h) {
					entity->boundbox.y = tmp.y - entity->hitbox.h;
				} else {
					entity->boundbox.x -= (result.w > target_movement) ? target_movement : result.w;
				}

				float movement = getLineLength(old_entity.x, old_entity.y, entity->boundbox.x, entity->boundbox.y);
				printf("Movement %f/%f\n", movement, target_movement);
				target_movement -= movement;

				entity->boundbox.y -= target_movement;

			}
		}
	}
}


double Level::getLineLength(int x1, int y1, int x2, int y2) {
	// NOTE(jouni): We might need abs here?
	int x = x2 - x1;
	int y = y2 - y1;

	return sqrt(pow(x, 2) + pow(y, 2));
}

double Level::getLineLength(SDL_Point p1, SDL_Point p2) {
	int x = p2.x - p1.x;
	int y = p2.y - p2.y;

	return sqrt(pow(x, 2) + pow(y, 2));
}