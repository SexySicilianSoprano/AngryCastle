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

SDL_Rect Level::collides(MovingEntity *entity)
{
#if 1

//	Retval
	Rectangle old_entity = entity->hitbox;
	Rectangle new_entity = entity->boundbox;

	// Get the area of tiles considered for collision
	SDL_Point min_tile_xy = {std::min(old_entity.TopLeft().x, new_entity.TopLeft().x),
							 std::min(old_entity.TopLeft().y, new_entity.TopLeft().y)};
	SDL_Point max_tile_xy = {std::max(old_entity.BottomRight().x, new_entity.BottomRight().x),
							 std::max(old_entity.BottomRight().y, new_entity.BottomRight().y)};

	// SDL_Rect min_tile = pointToTile(min_tile_xy.x, min_tile_xy.y);
	// SDL_Rect max_tile = pointToTile(max_tile_xy.x, max_tile_xy.y);
	int min_tile_x = (min_tile_xy.x / tileSize) - 1;
	int min_tile_y = (min_tile_xy.y / tileSize) - 1;
	int max_tile_x = (max_tile_xy.x / tileSize) + 1;
	int max_tile_y = (max_tile_xy.y / tileSize) + 1;

	SDL_Rect nul = {min_tile_x * tileSize, min_tile_y * tileSize, (max_tile_x * tileSize) - (min_tile_x  * tileSize), (max_tile_y * tileSize) - (min_tile_y  * tileSize)};

 	SDL_Point line_start = {old_entity.Center().x, old_entity.Center().y};
 	SDL_Point line_end   = {new_entity.Center().x, new_entity.Center().y};

 	printf("Start x%d y%d - End x%d y%d\n", line_start.x, line_start.y, line_end.x, line_end.y);

	SDL_Point *closest_intersection = new SDL_Point();
	std::vector<SDL_Point*> intersections;
	std::vector<float> distances;

	for (int y_tile = min_tile_y; y_tile <= max_tile_y; y_tile++) {
		for (int x_tile = min_tile_x; x_tile <= max_tile_x; x_tile++) {
			SDL_Rect tmp = {(x_tile * tileSize) - (old_entity.w/2),
							(y_tile * tileSize) - (old_entity.h/2),
							tileSize + old_entity.w,
							tileSize + old_entity.h};
			// SDL_Rect tmp = {y_tile, x_tile, tileSize + old_entity.w, tileSize + old_entity.h};
			// printf("tile[%d][%d]: x%d y%d w%d h%d\n", x_tile, y_tile, tmp.x, tmp.y, tmp.w, tmp.h);

			if (SDL_IntersectRectAndLine(&tmp, &line_start.x, &line_start.y,
										 &line_end.x, &line_end.y) &&
				getTile(x_tile * tileSize, y_tile * tileSize) != 0) {

				printf("New tile\n");
				Rectangle tmp2(tmp);
				SDL_Point* top_intersect    = getLineIntersection(line_start, line_end, tmp2.TopLeft(), tmp2.TopRight());
				SDL_Point* right_intersect  = getLineIntersection(line_start, line_end, tmp2.TopRight(), tmp2.BottomRight());
				SDL_Point* left_intersect   = getLineIntersection(line_start, line_end, tmp2.TopLeft(), tmp2.BottomLeft());
				SDL_Point* bottom_intersect = getLineIntersection(line_start, line_end, tmp2.BottomLeft(), tmp2.BottomRight());

				if (top_intersect) {
					distances.push_back(getLineLength(line_start.x, line_start.y, top_intersect->x, top_intersect->y));
					intersections.push_back(top_intersect);

					printf("Top intersect: x%d y%d - Length: %f\n", top_intersect->x, top_intersect->y,
						   getLineLength(line_start.x, line_start.y, top_intersect->x, top_intersect->y));
				}

				if (bottom_intersect) {
					distances.push_back(getLineLength(line_start.x, line_start.y, bottom_intersect->x, bottom_intersect->y));
					intersections.push_back(bottom_intersect);

					printf("Bottom intersect: x%d y%d - Length: %f\n", bottom_intersect->x, bottom_intersect->y,
						   getLineLength(line_start.x, line_start.y, bottom_intersect->x, bottom_intersect->y));
				}

				if (left_intersect) {
					distances.push_back(getLineLength(line_start.x, line_start.y, left_intersect->x, left_intersect->y));
					intersections.push_back(left_intersect);

					printf("Left intersect: x%d y%d - Length: %f\n", left_intersect->x, left_intersect->y,
						   getLineLength(line_start.x, line_start.y, left_intersect->x, left_intersect->y));
				}

				if (right_intersect) {
					distances.push_back(getLineLength(line_start.x, line_start.y, right_intersect->x, right_intersect->y));
					intersections.push_back(right_intersect);

					printf("Right intersect: x%d y%d - Length: %f\n", right_intersect->x, right_intersect->y,
						   getLineLength(line_start.x, line_start.y, right_intersect->x, right_intersect->y));
				}
			}
		}
	}

	std::vector<float>::iterator result = std::min_element(distances.begin(), distances.end());

	if (!intersections.empty()) {
		closest_intersection->x = intersections[std::distance(std::begin(distances), result)]->x;
		closest_intersection->y = intersections[std::distance(std::begin(distances), result)]->y;
	}

	if (closest_intersection->x > 0 && closest_intersection->y > 0) {
		entity->boundbox.y = closest_intersection->y - (old_entity.h/2) - 1;

		// if (line_start.y != line_end.y) {
			entity->boundbox.x = closest_intersection->x - (old_entity.w/2);
		// }
		entity->in_air = false;
		entity->velocity_y = 0;
	}


	// if (!SDL_RectEmpty(&closest_tile)) {
	//  	SDL_Point top_tile_start = {closest_tile.x, closest_tile.y};
	//  	SDL_Point top_tile_end   = {closest_tile.x + closest_tile.w, closest_tile.y};
	//  	SDL_Point* top_intersect = getLineIntersection(line_start, line_end, top_tile_start, top_tile_end);
	//  	if (top_intersect) {
	// 	 	float top_intersect_length = getLineLength(line_start.x, line_start.y, top_intersect->x, top_intersect->y);
	// 	 	printf("Top intersect length: %f\n", top_intersect_length);
	//  	}

	//  	SDL_Point right_side_start = {closest_tile.x, closest_tile.y};
	//  	SDL_Point right_side_end   = {closest_tile.x, closest_tile.y + closest_tile.h};
	//  	SDL_Point* right_side_intersect = getLineIntersection(line_start, line_end, right_side_start, right_side_end);

	// 	if (right_side_intersect) {
	// 	 	float right_intersect_length = getLineLength(line_start.x, line_start.y, right_side_intersect->x, right_side_intersect->y);
	// 	 	printf("Right intersect length: %f\n", right_intersect_length);
	//  	}

	//  	if (right_side_intersect) {
	//  		printf("Intersection: x%d y%d", right_side_intersect->x, right_side_intersect->y);

	//  		entity->boundbox.x = right_side_intersect->x - (old_entity.w/2);
	//  	}

	//  	if (top_intersect) {
	// 	 	printf("Itersection: x%d y%d\n", top_intersect->x, top_intersect->y - 1);

	// 	 	entity->boundbox.x = top_intersect->x - (old_entity.w/2);
	// 	 	entity->boundbox.y = top_intersect->y - (old_entity.h/2);
	//  	}

	//  	// if (old_x) {
	// 		// entity->boundbox.y = closest_tile.y - (old_y * new_x) / old_x; //closest_tile.y - (old_entity.h/2);
	// 		// printf("Something y: %d\n", (old_y * new_x) / old_x);
	//  	// } else {
	//  	// 	entity->boundbox.y = closest_tile.y - (old_entity.h/2);
	//  	// }

	// 	entity->in_air = false;
	// 	entity->velocity_y = 0;
	// }

	return nul;

#else
	SDL_Rect hitbox = (SDL_Rect) entity->hitbox;
	SDL_Rect result;
	std::vector<SDL_Point> tiles;

	SDL_Point top_right_tile = {hitbox.x / tileSize, hitbox.y / tileSize};
	SDL_Point bottom_right_tile = {(hitbox.x + hitbox.w) / tileSize,
								   (hitbox.y + hitbox.h) / tileSize};

	// Number of tiles entity overlaps vertically
	int tiles_x = bottom_right_tile.x - top_right_tile.x;
	// Number of tiles entity overlaps horizontally
	int tiles_y = bottom_right_tile.y - top_right_tile.y;

	// Get all tiles entity overlaps
	for (int i = 0; i <= tiles_y; i++) {
		for (int j = 0; j <= tiles_x; j++) {
			SDL_Point tmp = {hitbox.x + (j * tileSize), hitbox.y + (i *tileSize)};
			tiles.push_back(tmp);
		}
	}

	printf("w%d h%d\n", hitbox.w, hitbox.h);

	// Collision correction
	for (std::vector<SDL_Point>::iterator it = tiles.begin();
		 it != tiles.end();
		 ++it) {

		if (getTile(it->x, it->y) != 0) {
			SDL_Rect tile = pointToTile(it->x, it->y);

			if (SDL_IntersectRect(&hitbox, &tile, &result)) {
				if (result.h > result.w) {
					if (hitbox.x < tile.x) {
						hitbox.x 		 -= result.w;
					} else {
						hitbox.x 		 += result.w;
					}
				} else {
					hitbox.y 		 	-= result.h;
					entity->velocity_y	= 0;
					entity->in_air		= false;
				}
			}
		}
	}
#endif
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

float Level::getLineAngle(int x1, int y1, int x2, int y2) {
	return (atan2(y2 - y1, x2 - x1) * 180) / M_PI;
}

SDL_Point* Level::getLineIntersection(SDL_Point p1, SDL_Point p2, SDL_Point p3, SDL_Point p4) {
	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return NULL;

	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

	// Check if the x and y coordinates are within both lines
	if ( x < std::min(x1, x2) || x > std::max(x1, x2) ||
	x < std::min(x3, x4) || x > std::max(x3, x4) ) return NULL;
	if ( y < std::min(y1, y2) || y > std::max(y1, y2) ||
	y < std::min(y3, y4) || y > std::max(y3, y4) ) return NULL;

	// Return the point of intersection
	SDL_Point* ret = new SDL_Point();
	ret->x = x;
	ret->y = y;
	return ret;
}