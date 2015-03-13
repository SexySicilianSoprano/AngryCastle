/**
 * Music.h
 *
 * Description:
 * For playing music.
 *
 * Example:
 * --
 */

#ifndef __MUSIC_H_DEFINED__
#define __MUSIC_H_DEFINED__

#include <vector>
#include "SDL.h"
#include <SDL_mixer.h>

class Music {
public:
	Music(std::string filepath);
	virtual ~Music();
	bool play(int times =- 1, int fade_in_ms = 0);
	void fadeOut(int ms);
	void stop();
	void pause();
	void unpause();
	void restart();
	void rewind();
	void setPosition(double seconds);
	bool isPlaying();
	bool isPaused();
	bool isFadingIn();
	bool isFadingOut();
	int setVolume(int volume);
	int getVolume();
	int getMaxVolume();

private:
	Mix_Music *music;
	std::string filepath;
};

#endif