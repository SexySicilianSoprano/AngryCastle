#ifndef __BASESTATE_H_DEFINED__
#define __BASESTATE_H_DEFINED__

#include "Window.h"

#define STATE_CONTINUE	0
#define STATE_QUIT		1

#define STATE_MENU		2
#define STATE_GAME		3

struct stateStatus {
	int status;
	bool prepend;
};

class BaseState {

	public:
		BaseState() {};
		~BaseState() {};

		virtual stateStatus update() = 0;
		virtual void render() = 0;

	protected:
};

#endif // __BASESTATE_H_DEFINED__