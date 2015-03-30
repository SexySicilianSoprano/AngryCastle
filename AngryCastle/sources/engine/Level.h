#ifndef __LEVEL_H_DEFINED__
#define __LEVEL_H_DEFINED__

#include <vector>
#include "Window.h"
#include "Camera.h"
#include "PugiXML.h"
#include "Sprite.h"

#define SIL_LAYER	0	// SilhouetteLayer
#define BG_LAYER	1	// BackgroundLayer
#define GAME_LAYER	2	// GameLayer
#define FG_LAYER	3	// ForegroundLayer

#define LAYER_COUNT 4

class Level
{
	public:
		Level(Window *window, Camera *camera);
		~Level();

		void load(std::string level_name);
		void update();
		void render(int layer);

		int getTile(int x, int y);
		int pointToTile(int x);
		int getLevelWidth();

		std::string getRightmostLevel();
		std::string getLeftmostLevel();


		//bool collides(Entity *entity);

	private:
		Window *window;
		Camera *camera;

		pugi::xml_document levelDocument;
		pugi::xml_parse_result result;
		pugi::xml_node SilhouetteLayer, BackgroundLayer, GameLayer, ForegroundLayer;

		int levelWidth, levelHeight;
		int tileSize;

		Sprite *levelTileSheet;
		std::vector<std::vector<int>> SilhouetteData, BackgroundData, GameData, ForegroundData;
};

#endif //__LEVEL_H_DEFINED__