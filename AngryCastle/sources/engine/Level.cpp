#include "Level.h"

Level::Level(Window *window, Camera *camera):
	window(window),
	camera(camera)
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

	// Get node which contains tileids
	tileNode = levelDocument.child("map").child("layer").child("data");

	// Load level tileset
	std::string tileSet = levelDocument.child("map").child("tileset").child("image").attribute("source").value();
	levelTileSheet = new Sprite(window, tileSet, tileSize, tileSize);

	int iteratorCount = 0;
	std::vector<int> levelRow;

	// Go through tile-nodes
	for(pugi::xml_node_iterator iterator = tileNode.begin();
		iterator != tileNode.end();
		++iterator)
	{
		iteratorCount++;

		// Add tile id to 
		int gid = atoi(iterator->attribute("gid").value());
		levelRow.push_back(gid);
		
		// NOTE(juha): Kun päästään kentän loppuun, vaihdetaan riviä.
		if (iteratorCount % levelWidth == 0)
		{
			levelData.push_back(levelRow);
			levelRow.clear();
		}
	}
}

void Level::update() {
	/*
	// NOTE(jouni&&karlos): Liikuttaa kameraa jos kenttä ei oo vielä loppunu
	if (camera.getX() < levelWidth*tileSize)
	{
		for (std::vector<levelTrigger>::iterator it = triggers.begin();
		it != triggers.end();
		++it) {
			if (camera.getX() >= it->spawnTile) {
				launchTrigger((*it));
				triggers.erase(it);
				break;
			}
		}
		camera.update();
	}
	*/
}

// TODO(jouni): Muuttujaksi kameran X
void Level::render()
{
	std::vector<std::vector<int>>::iterator row;
	std::vector<int>::iterator col;

	for (row = levelData.begin(); row != levelData.end(); ++row) {
		for (col = row->begin(); col != row->end(); ++col) {
			int X = col - row->begin();
			int Y = row - levelData.begin();
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

int Level::getTile(int x, int y)
{
	if (y >= 0 &&
		x >= 0 &&
		y < levelData.size()*tileSize &&
		x < levelData[0].size()*tileSize)
	{
		return (levelData[y/tileSize][(camera->frame.x + x)/tileSize]);
	}

	return 0;
}

int Level::pointToTile(int x) {
	return camera->frame.x + x / tileSize;
}

std::string Level::getRightmostLevel() {
	return "levels/lumbroff_01.tmx";
}

/*
bool Level::collides(Entity *entity)
{
	int hbX;
	int hbY;

	// Palauttaa hitboxin vasemman yläkulman tilen
	hbX = entity->hitbox.x;
	hbY = entity->hitbox.y;

	if(getTile(hbX, hbY) > 0)
	{
		return true;
	}

	// Palauttaa hitboxin oikean yläkulman tilen
	hbX = entity->hitbox.x + entity->hitbox.w;
	hbY = entity->hitbox.y;

	if(getTile(hbX, hbY) > 0){
		return true;
	}

	// Palauttaa hitboxin vasemman alakulman tilen
	hbX = entity->hitbox.x + entity->hitbox.w;
	hbY = entity->hitbox.y + entity->hitbox.h;

	if(getTile(hbX, hbY) > 0){
		return true;
	}

	// Palauttaa hitboxin oikean alakulman tilen
	hbX = entity->hitbox.x;
	hbY = entity->hitbox.y + entity->hitbox.h;

	if(getTile(hbX, hbY) > 0){
		return true;
	}
	
	return false;
}
*/