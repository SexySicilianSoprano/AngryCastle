/**
 * AI.h
 *
 * Description:
 * For assigning artificial intelligence to enemies.
 *
 * Example:
 * --
 */

#ifndef __AI_H_DEFINED__
#define __AI_H_DEFINED__

#include <vector>
#include "Enemy.h"

class AI {
public:
	AI(Enemy *enemy);
	void linearPattern();
	void sinePattern();
	void update();

private:
	Enemy *enemy;

	enum DIRECTION {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	int index;
	int chilltime;
	std::vector<int> pattern;
};

#endif