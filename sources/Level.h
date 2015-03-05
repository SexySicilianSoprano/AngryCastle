/**
 * Level.h
 *
 * Description:
 * For creating levels.
 *
 * Example:
 * --
 */

#ifndef __LEVEL_H_DEFINED__
#define __LEVEL_H_DEFINED__

#include "Window.h"
#include "Sprite.h"
#include "PugiXML.h"
#include "Camera.h"

class Level {
public:
	Level(Window *window);
	~Level();
	void load(std::string level_name);
	void render();
	int getTile(int x, int y);
	int getWidth();

	struct level_trigger {
		int spawn_tile;
		int enemy_count;
		std::string enemy_type;
		int spawn_height;
	};

private:
	pugi::xml_document level_document;
	pugi::xml_parse_result result;
	pugi::xml_node tile_node;
	pugi::xml_node enemy_spawn;

	int level_width;
	int level_height;
	int tile_size;

	Camera camera;

	Texture background;
	int bg_scrolling_offset;
	Window *window;
	Sprite *level_tile_sheet;
	std::vector<std::vector<int>> level_data;
	std::vector<level_trigger> triggers;

	level_trigger launchTrigger(level_trigger enemy_count);
};

#endif