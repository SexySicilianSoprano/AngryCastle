#ifndef __LEVEL_H_DEFINED__
#define __LEVEL_H_DEFINED__

#include <vector>
#include "Window.h"
#include "Camera.h"
#include "PugiXML.h"
#include "Sprite.h"

class Level
{
	public:
		Level(Window *window, Camera *camera);
		~Level();

		void load(std::string level_name);
		void update();
		void render();

		int getTile(int x, int y);
		int pointToTile(int x);
		int getLevelWidth();

		std::string getRightmostLevel();

		//bool collides(Entity *entity);

	private:
		Window *window;
		Camera *camera;

		pugi::xml_document levelDocument;
		pugi::xml_parse_result result;
		pugi::xml_node tileNode;
		pugi::xml_node enemySpawn;

		int levelWidth, levelHeight;
		int tileSize;

		Sprite *levelTileSheet;
		std::vector<std::vector<int>> levelData;
};

#endif //__LEVEL_H_DEFINED__