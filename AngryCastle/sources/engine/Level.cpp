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
{ }

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
			SDL_Rect hitbox = {0, 0, 0, 0};
			Entity entity(0, 0, 10, 10, hitbox);
			entity.setPosition(npc_x, npc_y);
			collection->push(entity);
		}

		if (type.compare("enemySpawn") == 0) {
			std::string type   = iterator->child("properties").find_child_by_attribute("name", "enemyType").attribute("value").value();

			int npc_x = atoi(iterator->attribute("x").value());
			int npc_y = atoi(iterator->attribute("y").value());

			// NOTE(jouni): **Factory creates entity of given type**
			// int x, int y, int w, int h, SDL_Rect hitbox_offset
			SDL_Rect hitbox = {0, 0, 0, 0};
			Entity entity(0, 0, 20, 20, hitbox);
			entity.setPosition(npc_x, npc_y);
			collection->push(entity);
		}

		if (type.compare("item") == 0) {
			std::string type   = iterator->child("properties").find_child_by_attribute("name", "itemType").attribute("value").value();

			int npc_x = atoi(iterator->attribute("x").value());
			int npc_y = atoi(iterator->attribute("y").value());

			// NOTE(jouni): **Factory creates entity of given type**
			// int x, int y, int w, int h, SDL_Rect hitbox_offset
			SDL_Rect hitbox = {0, 0, 0, 0};
			Entity entity(0, 0, 5, 5, hitbox);
			entity.setPosition(npc_x, npc_y);
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
			SDL_Rect entity_area  = {entity->getX(),
									 entity->getY(),
									 entity->getW(),
									 entity->getH()};
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

	std::vector<int>::iterator col_begin;
	std::vector<int>::iterator col_end;

	for (row = row_begin; row != row_end; ++row) {
		col_begin = row->begin() + start_tile_x;
		if (start_tile_x + tiles_x < row->size()) {
			col_end = row->begin() + start_tile_x + tiles_x;
		} else {
			col_end = row->end();
		}

		for (col = col_begin; col != col_end; ++col) {
			int X = col - row->begin();
			int Y = row - data->begin();
			levelTileSheet->setIndex(*col-1);
			levelTileSheet->render(X*tileSize - camera->frame.x, Y*tileSize - camera->frame.y);
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

SDL_Rect Level::collides(Entity *entity)
{

	SDL_Rect player_hitbox = entity->getHitbox();
	SDL_Rect collidetile = {0,0,0,0};
	SDL_Rect result;
	int tile1 = 0;
	int tile2 = 0;

	// Entity moving right
	if (entity->desiredX > entity->getX()) {
		// Right side
		tile1 = getTile(player_hitbox.x + player_hitbox.w, player_hitbox.y);
		tile2 = getTile(player_hitbox.x + player_hitbox.w, player_hitbox.y + player_hitbox.h);

		if (tile1) {
 			collidetile = pointToTile(player_hitbox.x + player_hitbox.w, player_hitbox.y);
			
			if (SDL_IntersectRect(&player_hitbox, &collidetile, &result)) {
				if (result.h > result.w) {
					player_hitbox.x  -= result.w;
					entity->desiredX -= result.w;
				} else {
					player_hitbox.y  -= result.h;
					entity->desiredY -= result.h;
				}
			}
		} else if (tile2) {
			collidetile = pointToTile(player_hitbox.x + player_hitbox.w, player_hitbox.y + player_hitbox.h);

			if (SDL_IntersectRect(&player_hitbox, &collidetile, &result)) {
				if (result.h > result.w) {
					player_hitbox.x  -= result.w;
					entity->desiredX -= result.w;
				} else {
					player_hitbox.y  -= result.h;
					entity->desiredY -= result.h;
				}
			}
		}
	// Entity moving left
	} 
	
	if(entity->desiredX < entity->getX()) {
		// Left side
		tile1 = getTile(player_hitbox.x, player_hitbox.y);
		tile2 = getTile(player_hitbox.x, player_hitbox.y + player_hitbox.h);


		if (tile1) {
 			collidetile = pointToTile(player_hitbox.x, player_hitbox.y);
			
			if (SDL_IntersectRect(&player_hitbox, &collidetile, &result)) {
				player_hitbox.x += result.w;
				entity->desiredX += result.w;
			}
		} else if (tile2) {
			collidetile = pointToTile(player_hitbox.x, player_hitbox.y + player_hitbox.h);

			if (SDL_IntersectRect(&player_hitbox, &collidetile, &result)) {
				if (result.h > result.w) {
					player_hitbox.x  += result.w;
					entity->desiredX += result.w;
				} else {
					player_hitbox.y  -= result.h;
					entity->desiredY -= result.h;
				}
			}
		}
	}

	// Bottom 
	tile1 = getTile(player_hitbox.x + 1,  player_hitbox.y + player_hitbox.h);
	tile2 = getTile(player_hitbox.x + player_hitbox.w - 1, player_hitbox.y + player_hitbox.h);

	if (tile1) {
		collidetile = pointToTile(player_hitbox.x, player_hitbox.y + player_hitbox.h);
		if (SDL_IntersectRect(&player_hitbox, &collidetile, &result)) {
			if (result.h > result.w) {
				player_hitbox.x  -= result.w;
				entity->desiredX -= result.w;
			} else {
				player_hitbox.y  -= result.h;
				entity->desiredY -= result.h;
			}
		}
	} else if(tile2) {
		collidetile = pointToTile(player_hitbox.x + player_hitbox.w, player_hitbox.y + player_hitbox.h);
		
		if (SDL_IntersectRect(&player_hitbox, &collidetile, &result)) {
			if (result.h > result.w) {
				player_hitbox.x  -= result.w;
				entity->desiredX -= result.w;
			} else {
				player_hitbox.y  -= result.h;
				entity->desiredY -= result.h;
			}
		}
	}

	if(tile1 || tile2) {
		entity->velocity_y = 0;
		entity->in_air = false;
	} else {
		entity->in_air = true;
	}

	
	
	// Bottom right
	/*
	tile = getTile(player_hitbox.x + player_hitbox.w, player_hitbox.y + player_hitbox.h);

	if (tile != 0) {
		collidetile = pointToTile(player_hitbox.x + player_hitbox.w, player_hitbox.y + player_hitbox.h);

		if (SDL_IntersectRect(&player_hitbox, &collidetile, &result)) {
  			entity->desiredX -= result.w;
		}
	}*/

	return collidetile;
	/*
	if (tile != 0) {
		SDL_Rect tilepos = pointToTile(player_hitbox.x, player_hitbox.y + player_hitbox.h);

		if (player_hitbox.y + player_hitbox.h <= tilepos.y) {
			player_hitbox.y = tilepos.y + player_hitbox.h;
		}

		if (player_hitbox.y >= tilepos.y + tilepos.h) {
			return true
		}

		if (player_hitbox.x + player_hitbox.w <= tilepos.x) {
			return true;
		}

		if (player_hitbox.x >= tilepos.x + tilepos.w) {
			return true;
		}
		//return true;
	}
	*/
	//return false;


	/*
	// Entity TOP-LEFT
	tile = getTile(player_hitbox.x, player_hitbox.y);
	if (tile != 0) {
		SDL_Rect tilepos = pointToTile(player_hitbox.x, player_hitbox.y);
		SDL_Rect result;

		SDL_IntersectRect(&player_hitbox, &tilepos, &result);

		entity->desiredX = tilepos.x + tilepos.w - entity->hitbox_offset.x;
		entity->desiredY = entity->getY();
		collides = true;
	}

	// Entity TOP-RIGHT
	tile = getTile(player_hitbox.x + player_hitbox.w, player_hitbox.y);
	if (tile != 0) {
		SDL_Rect tilepos = pointToTile(player_hitbox.x + player_hitbox.w, player_hitbox.y);
		SDL_Rect result;

		SDL_IntersectRect(&player_hitbox, &tilepos, &result);

		entity->desiredX = tilepos.x - (entity->hitbox_offset.x + entity->hitbox_offset.w);
		entity->desiredY = entity->getY();
		collides = true;
	}
	*/
	// Entity BOTTOM-LEFT
	//tile = getTile(player_hitbox.x, player_hitbox.y + player_hitbox.h);
	//if (tile != 0) {
		//SDL_Rect tilepos = pointToTile(player_hitbox.x, player_hitbox.y + player_hitbox.h);
		//SDL_Rect tilepos = pointToTile(player_hitbox.x, player_hitbox.y + player_hitbox.h);
		//SDL_Rect result;

		//SDL_IntersectRect(&player_hitbox, &tilepos, &result);
		/*
		printf("Tilepos>\tx%d y%d w%d h%d\n", tilepos.x, tilepos.y, tilepos.w, tilepos.h);
		printf("Result>\t\tx%d y%d w%d h%d\n", result.x, result.y, result.w, result.h);
		printf("Playerpos>\tx%d y%d w%d h%d\n", entity->getX(), entity->getY(), entity->getW(), entity->getH());
		printf("Hitbox>\t\tx%d y%d w%d h%d\n", player_hitbox.x, player_hitbox.y, player_hitbox.w, player_hitbox.h);
		printf("Desired pos>\tx%d y%d w%d h%d\n", entity->desiredX, entity->desiredY, entity->getW(), entity->getH());
		*/
		/* NOTE(jouni):
			Substract colliding tile Y-position by entity hitbox to get 

						  Colliding tile
						  Y-position					Hitbox bottom left
						   _________	____________________________________________________*/
		//entity->desiredY = tilepos.y - ((player_hitbox.x - entity->getX()) + player_hitbox.h);
		//entity->desiredY = tilepos.y - (entity->getX() + player_hitbox.h);
		//printf("New dpos>\tx%d y%d w%d h%d\n", entity->desiredX, entity->desiredY, entity->getW(), entity->getH());
		//collides = true;


	//}
	
	// Entity BOTTOM-RIGHT
	/*
	tile = getTile(player_hitbox.x + player_hitbox.w, player_hitbox.y + player_hitbox.h);
	if (tile != 0) {
		SDL_Rect tilepos = pointToTile(player_hitbox.x + player_hitbox.w, player_hitbox.y + player_hitbox.h);
		SDL_Rect result;

		SDL_IntersectRect(&player_hitbox, &tilepos, &result);
		entity->desiredY = tilepos.y - ((player_hitbox.x - entity->getX()) + player_hitbox.h);
		collides = true;
	}
	*/
	//return collides;
}