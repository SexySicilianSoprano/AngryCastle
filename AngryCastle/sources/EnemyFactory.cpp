#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(Window *window, EntityCollection<Projectile> *projectiles, SFX *sound):
	window(window),
	projectiles(projectiles),
	sound(sound)
{
	// Drone definition
	drone.animation = new Animation(window, "graphics//drone.png", 16, 9, 0, 1, 1);
	drone.dying		= new Animation(window, "graphics//16x16_explosion.png", 16, 16, 0, 10, 12); 
	drone.hitbox.w  = 16;
	drone.hitbox.h  = 9;
	drone.hitpoints = 1;
	// Jet definition
	jet.animation = new Animation(window, "graphics//kaupunki_fighter_jet.png", 32, 14, 0, 3, 2);
	jet.dying	  = new Animation(window, "graphics//player_dead.png", 32, 32, 0, 10, 12); 
	jet.hitbox.w  = 32;
	jet.hitbox.h  = 14;
	jet.hitpoints = 1;
}

EnemyFactory::~EnemyFactory() {}

Enemy EnemyFactory::spawn(std::string type, int spawnHeight) {

	if (type.compare("drone")) {
		return Enemy(drone.animation, drone.dying, drone.hitbox, drone.hitpoints, sound);
	}
		
	if (type.compare("jet")) {
		return Enemy(jet.animation, drone.dying, jet.hitbox, jet.hitpoints, sound);
	}

	SDL_Rect empty = {0, 0, 0, 0};

	return Enemy(nullptr, nullptr, empty, -1, nullptr);
}