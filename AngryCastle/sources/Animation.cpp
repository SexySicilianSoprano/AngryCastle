#include "Animation.h"

Animation::Animation(Window *window, std::string filename,
					 int width, int height, int start_frame,
					 int frame_count, int framerate):
	Sprite(window, filename, width, height),
	window(window),
	current_frame(0),
	current_frametime(0) {
	setFramerate(frametime);

	for (int frame = 0; frame < frame_count; ++frame) {
		frames.push_back(frame);
	}
}

Animation::~Animation() {
}

void Animation::addFrame(int frame_index) {
	// TODO(juha): Adding frames to the animation from the existing sprites.
}

void Animation::setFramerate(int framerate) {
	frametime = (1000 / framerate);
}

int Animation::getFramecount() {
	return frames.size();
}

int Animation::getCurrentFrame() {
	return current_frame;
}

void Animation::play(int times) {
	running = true;
	play_count = times;
}

void Animation::pause() {
	running = false;
}

void Animation::render(int x, int y) {
	current_frametime += window->getDelta();

	if (running && play_count != 0) {
		if (current_frametime > frametime) {
			if (current_frame >= (int)frames.size() -1) {
				current_frame = 0;
				play_count--;
			} else {
				current_frame++;
			}

			current_frametime = 0;
		}
	}

	Sprite::setIndex(current_frame);
	Sprite::render(x, y);
}