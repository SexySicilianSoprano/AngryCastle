/**
 * 
 * Item.h
 */

#ifndef __ITEM_H_DEFINED__
#define __ITEM_H_DEFINED__

#include <string>

struct effect {
	
};

class Item
{
	public:
		Item();
		~Item();

		int type;
		int tier;

		std::string iconfile;
		std::string name;
		 

	private:
};

#endif //__HUD_H_DEFINED__