/**
 * Projectile.cpp
 *
 */

#include "Projectile.h"

Projectile::Projectile(Window *window):
	window(window),
	bullet_texture(window, "images//ammus_sprite.png", 5, 5) {

}

Projectile::~Projectile() {

}

void Projectile::spawn(int type, int x, int y, int radian) {
	SDL_Rect hitbox = {1, 1, 2, 2};
	MovingEntity entity(&bullet_texture, hitbox);
	entity.setX(x);
	entity.setY(y);
	entity.setSpeed(20);
	bullet tmp = {entity, type, radian};
	container.push_back(tmp);
}

void Projectile::update() {
	for (std::vector<bullet>::iterator it = container.begin();
		 it != container.end();
		 ++it) {
			 int radian = it->radian;
			 int x = it->entity.getX();
			 int y = it->entity.getY();
			 int velocity_x = (int)(it->entity.getSpeed() * cos(radian));
			 int velocity_y = (int)(it->entity.getSpeed() * sin(radian));

			 it->entity.setX(x + velocity_x);
			 it->entity.setY(y + velocity_y);
	}
}

void Projectile::render() {
	for (std::vector<bullet>::iterator it = container.begin();
		 it != container.end();
		 ++it) {

			 it->entity.render();
	}
}