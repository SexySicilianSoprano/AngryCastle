/**
 * Animation.h
 *
 * Description:
 * For creating animations.
 *
 * Example:
 * 
 */

#ifndef __ANIMATION_H_DEFINED__
#define __ANIMATION_H_DEFINED__

#include <vector>
#include "SDL.h"
#include "Sprite.h"

#define INFINITE_LOOP -1

class Animation : public Sprite
{
public:
	Animation(Window *window, std::string filename, int width, int height,
		      int start_frame, int frame_count, int framerate);
	virtual ~Animation();
	void addFrame(int frame_index);
	void setFramerate(int framerate);
	int getFramecount();
	int getCurrentFrame();
	void play(int times);
	void pause();
	void render(int x, int y);
	Sprite *animated;

private:
	Window *window;
	std::vector<int> frames;
	int play_count, frametime, current_frame, current_frametime;
	bool running;
};

#endif