/**
 *
 * Camera.h
 * 
 * Kamera liikkuu ja tausta vaihtuu.
 * 
 * Esimerkki:
 *		Camera camera(256, 240);
 *		camera->speed(2);
 *
 *		int x = camera->getX();
 *		
 */

// Header guardit
#ifndef __CAMERA_H_DEFINED__
#define __CAMERA_H_DEFINED__

// Includet
#include "SDL.h"
#include "Entity.h"

class Camera {
	public:
		Camera(int width, int height);
		virtual ~Camera();

		SDL_Rect frame;

		void lock(Entity *entity);
		void update(int levelWidth, int levelHeight);

	private:
		Entity *locked_entity;
};

#endif // __CAMERA_H_DEFINED__