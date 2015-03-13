/**
 * Timer.h
 *
 * Description:
 * Timing functionality.
 *
 * Example:
 * Timer::start(); // Starts counting ticks.
 */

#ifndef __TIMER_H_DEFINED__
#define __TIMER_H_DEFINED__

#include "SDL.h"

class Timer {
public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	Uint32 getTicks();
	bool isStarted();
	bool isPaused();

private:
	Uint32 start_ticks;
	Uint32 paused_ticks;
	bool started;
	bool paused;
};

#endif