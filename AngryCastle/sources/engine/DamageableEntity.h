/*
 * DamageableEntity.h
 *
 * T‰m‰ luokka on yl‰luokka kaikille entityille, joita voi vahingoittaa,
 * eli, joilla on health pointit.
 *
 * Esimerkki:
 *		DamageableEntity damageableEntity = new DamageableEntity();
 *		damageableEntity->damage(100);
 */

#ifndef __DAMAGEABLEENTITY_H_DEFINED__
#define __DAMAGEABLEENTITY_H_DEFINED__

class DamageableEntity
{
public:
	DamageableEntity(int initialHitPoints);
	~DamageableEntity();

	// Parantaa entity‰ jonkin m‰‰r‰n
	void heal(int amount);

	// Aiheuttaa vahinkoa entityyn tietyn m‰‰r‰n
	void damage(int amount);

	bool isDead();

	float getHitpoints();

private:
	bool alive;
	float hitpoints;
};

#endif //__DAMAGEABLEENTITY_H_DEFINED__