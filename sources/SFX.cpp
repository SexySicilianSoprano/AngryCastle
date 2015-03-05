/**
 * SFX.cpp
 *
 */

#include "SFX.h"
#include "SDL_mixer.h"

std::vector<SFX*> SFX::all;

SFX::SFX(std::string filepath):
	sfx(nullptr),
	filepath(filepath),
	channel(0) {
		SFX::all.push_back(this);
		sfx = Mix_LoadWAV(filepath.c_str());

		if (!sfx) {
			printf("Mix_LoadWAV: Couldn't load SFX\nMixer error: %s\n", Mix_GetError());
		}
		else {
			printf("SFX::load '%s'\n", filepath.c_str());
		}
}

SFX::~SFX() {
	if (sfx) {
		Mix_FreeChunk(sfx);
	}
	
}

bool SFX::play(int times) {
	if (!sfx) {
		printf("Couldnt find Mix_Chunk\n");
		return false;
	}

	if (times > 0) {
		times--;
	}

	int chan = Mix_PlayChannel(-1, sfx, times);

	if (chan == -1) {
		printf("Mix_PlayChannel: Couldn't play SFX\nMixer error: %s\n", Mix_GetError());
		return false;
	}

	channel = chan;
	return true;
}

void SFX::pause() {
	if (Mix_GetChunk(channel) == sfx) {
		Mix_Pause(channel);
	}
}

void SFX::unpause() {
	if (Mix_GetChunk(channel) == sfx) {
		Mix_Resume(channel);
	}
}

void SFX::stop() {
	if (Mix_GetChunk(channel) == sfx) {
		Mix_HaltChannel(channel);
	}
}

bool SFX::isPlaying() {
	return Mix_Playing(channel) && !isPaused();
}

int SFX::isPaused() {
	return Mix_Paused(channel);
}

int SFX::getVolume() {
	return Mix_VolumeChunk(sfx, -1);
}

int SFX::setVolume(int volume) {
	return Mix_VolumeChunk(sfx, volume);
}

int SFX::setVolumeAll(int volume) {
	int previous = 0;

	for (std::vector<SFX*>::iterator it = SFX::all.begin();
	     it != SFX::all.end();
	     ++it) {
			 previous = Mix_VolumeChunk((*it)->sfx, volume);
	}

	return previous;
}

int SFX::getMaxVolume() {
	return MIX_MAX_VOLUME;
}

void SFX::stopAll() {
	Mix_HaltChannel(-1);
}

void SFX::pauseAll() {
	Mix_Pause(-1);
}

void SFX::unpauseAll() {
	Mix_Resume(-1);
}