/**
 * Camera.h
 *
 * Description:
 * For creating cameras.
 *
 * Example:
 * Camera camera(256, 240);
 * camera->speed(2);
 * int x = camera->getX();
 */

#ifndef __CAMERA_H_DEFINED__
#define __CAMERA_H_DEFINED__

#include "SDL.h"

class Camera {
public:
	Camera(int width, int height);
	virtual ~Camera();
	void update();
	void setSpeed(int speed);
	int getSpeed();
	int getX();

private:
	SDL_Rect frame;
	int speed;
};

#endif