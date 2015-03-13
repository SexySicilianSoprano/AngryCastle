/**
 * GameState.h
 *
 * Description:
 * State where the game is happening.
 *
 * Example:
 * --
 */

#ifndef __GAMESTATE_H_DEFINED__
#define __GAMESTATE_H_DEFINED__

#include "StateManager.h"
#include "State.h"
#include "Player.h"
#include "Level.h"

class GameState : public State {
public:
	void init(Window *window);
	void cleanup();
	void pause();
	void resume();
	void handleEventys(StateManager *manager);
	void update(StateManager *manager);
	void render(StateManager *manager);

	static GameState *instance() {
		return &game_state;
	}

protected:
	GameState(Window *window) :
		level(window)
	{}
	~GameState() {}

private:
	static GameState game_state;
	Level level;
};

#endif