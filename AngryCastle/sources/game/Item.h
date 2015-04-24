/**
 * 
 * Item.h
 */

#ifndef __ITEM_H_DEFINED__
#define __ITEM_H_DEFINED__

#include <string>
#include "../engine/Texture.h"

struct attributes {
	int life;
	int mana;
	int sanity;

	// In milliseconds
	int overtime;

	bool equipable;
};

class Item
{
	public:
		Item(std::string name, std::string icon, attributes attris);
		~Item();		 

		std::string name;
		std::string icon;
		attributes attris;
	private:
};

#endif //__HUD_H_DEFINED__