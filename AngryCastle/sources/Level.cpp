/**
 * Level.cpp
 *
 */

#include "Level.h"

Level::Level(Window *window):
	window(window),
	bg_scrolling_offset(0),
	camera(256, 240),
	background(window, "images//kaupunki_tausta.png") {
		camera.setSpeed(2);
}

Level::~Level() {
	// delete level_tile_sheet;
}

void Level::load(std::string level_name) {
	result = level_document.load_file(level_name.c_str());

	if (!result) {
		char msg [256];
		sprintf_s(msg, "loadLevel: Failed to load level "
					   "%s\n", level_name);
		throw msg;
		return;
	}

	// TODO(juha): Tilesize is normally taken from tilewidth, not tilesize.
	tile_size = atoi(level_document.child("map").attribute("tilesize").value());
	level_width = atoi(level_document.child("map").attribute("width").value());
	level_height = atoi(level_document.child("map").attribute("height").value());
	tile_node = level_document.child("map").child("layer").child("data");

	level_tile_sheet = new Sprite(window, "images//512x512_kaupunki_tileset.png",
		                          tile_size, tile_size);

	int iterator_count = 0;
	std::vector<int> level_row;
	std::vector<int> enemy_spawn_row;

	for (pugi::xml_node_iterator iterator = tile_node.begin();
		 iterator != tile_node.end();
		 ++iterator) {
		iterator_count++;
		int gid = atoi(iterator->attribute("gid").value());
		level_row.push_back(gid);

		if (iterator_count % level_width == 0) {
			level_data.push_back(level_row);
			level_row.clear();
		}
	}

	enemy_spawn = level_document.child("map").child("objectgroup");
	iterator_count = 0;

	for (pugi::xml_node_iterator iterator = enemy_spawn.begin();
		 iterator != enemy_spawn.end();
		 ++iterator) {
		level_trigger trigger;
		iterator_count++;

		trigger.spawn_tile = atoi(iterator->attribute("x").value());
		
		pugi::xml_node properties = iterator->child("properties");

		for(pugi::xml_node_iterator it = properties.begin();
			it != properties.end();
			++it) {
			if (strcmp(it->attribute("name").value(), "enemyCount") == 0) {
				trigger.enemy_count = atoi(it->attribute("value").value());
			}

			if (strcmp(it->attribute("name").value(), "enemyType") == 0) {
				trigger.enemy_type = it->attribute("value").value();
			}

			if (strcmp(it->attribute("name").value(), "spawnHeight") == 0) {
				trigger.spawn_height = atoi(it->attribute("value").value());
			}
		}

		triggers.push_back(trigger);
	}
}

void Level::render() {
	if (camera.getX() < level_width*tile_size) {
		for (std::vector<level_trigger>::iterator it = triggers.begin();
			 it != triggers.end();
			 ++it) {
				 if (camera.getX() >= it->spawn_tile) {
					 launchTrigger((*it));
					 triggers.erase(it);
					 break;
				 }
		}

		camera.update();
	}

	int background_width;
	background_width = background.getWidth();

	// Scroll the background backwards
	--bg_scrolling_offset;

	// If the background has moved its whole length
	// return it to its original position.
	if (bg_scrolling_offset < -background_width) {
		bg_scrolling_offset = 0;
	}

	background.render(bg_scrolling_offset, 0);
	background.render(bg_scrolling_offset + background_width, 0);

	std::vector<std::vector<int>>::iterator row;
	std::vector<int>::iterator col;

	for (row = level_data.begin(); row != level_data.end(); ++row) {
		for (col = row->begin(); col != row->end(); ++col) {
			int x = col - row->begin();
			int y = row - level_data.begin();
			level_tile_sheet->setIndex(*col-1);
			level_tile_sheet->render(x*tile_size - camera.getX(), y*tile_size);
		}
	}
}

int Level::getTile(int x, int y) {
	if (y >= 0 &&
		x >= 0 &&
		(unsigned int)y < level_data.size()*tile_size &&
		(unsigned int)x < level_data[0].size()*tile_size) {
			return (level_data[y/tile_size][(camera.getX()+x)/tile_size]);
	}

	return 0;
}

int Level::getWidth() {
	return level_width*tile_size;
}

Level::level_trigger Level::launchTrigger(level_trigger enemy_count) {
	return enemy_count;
}