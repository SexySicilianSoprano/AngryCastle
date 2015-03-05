/**
 * Music.cpp
 *
 */

#include "Music.h"

Music::Music(std::string filepath):
	music(nullptr),
	filepath(filepath) {
		music = Mix_LoadMUS(filepath.c_str());
		if (!music) {
			printf("Audio error! Here it is: %s", Mix_GetError());
			SDL_Delay(5000);
		}
}

Music::~Music() {
    if (music) {
	    Mix_FreeMusic(music);
	}
}

bool Music::play(int times, int fade_in_ms) {
	if (!music) {
        return false;
	}

    if (Mix_FadeInMusic(music, times, fade_in_ms)) {
	    printf("Mix_FadeInMusic: Couldn't play music on %s", filepath);
	    return false;
    }

    return true;
}

void Music::fadeOut(int ms) {
	Mix_FadeOutMusic(ms);
}

void Music::stop() {
	Mix_HaltMusic();
}

void Music::pause() {
	Mix_PauseMusic();
}

void Music::unpause() {
	Mix_ResumeMusic();
}

void Music::restart() {
    stop();
    play();
}

void Music::rewind() {
	Mix_RewindMusic();
}

void Music::setPosition(double seconds) {
	rewind();
	if (Mix_SetMusicPosition(seconds) == -1) {
		printf("Mix_SetMusicPosition: Couldn't do that: %s", std::string(Mix_GetError()));
	}
}

bool Music::isPlaying() {
	return (Mix_PlayingMusic() && !isPaused());
}

bool Music::isPaused() {
	if (Mix_PausedMusic() == 0) {
		return false;
	} else {
		return true;
	}
}

bool Music::isFadingIn() {
	return (Mix_FadingMusic() == MIX_FADING_IN);
}

bool Music::isFadingOut() {
	return (Mix_FadingMusic() == MIX_FADING_OUT);
}

int Music::setVolume(int volume) {
	if (volume > MIX_MAX_VOLUME) {
		printf("Mix_VolumeMusic: Tried to overflow volume");
	}

	return Mix_VolumeMusic(volume);
}

int Music::getVolume() {
	return Mix_VolumeMusic(-1);
}

int Music::getMaxVolume() {
	return MIX_MAX_VOLUME;
}