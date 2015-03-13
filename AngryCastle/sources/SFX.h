/**
 * SFX.h
 *
 * Description:
 * For creating sounds.
 *
 * Example:
 * --
 */

#ifndef __SFX_H_DEFINED__
#define __SFX_H_DEFINED__

#include <vector>
#include "SDL.h"

class SFX {
public:
	SFX(std::string filepath);
	virtual ~SFX();
	bool play(int times=1);
	void pause();
	void unpause();
	void stop();
	bool isPlaying();
	int isPaused();
	int getVolume();
	int setVolume(int volume);
	static int getMaxVolume();
	static int setVolumeAll(int volume);
	static void stopAll();
	static void pauseAll();
	static void unpauseAll();

private:
	Mix_Chunk *sfx;
	std::string filepath;
	int channel;
	static std::vector<SFX*> all;
};

#endif