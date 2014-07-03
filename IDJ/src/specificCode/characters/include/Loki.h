/*
 * Loki.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#ifndef LOKI_H_
#define LOKI_H_

#include "../../objects/include/Stairs.h"
#include "Character.h"
#include "Barrier.h"
#include "Bullet.h"

class Loki : public Character
{
  public:
	Loki(float x, float y, MovementMap& movMap);
	~Loki();

	bool Is(std::string type);
	static Loki *characterLoki;

  private:
	enum TransformState {LOKI, EAGLE};
	TransformState appearance, prevAppearance;
    int flappedWings;
	Timer shootCooldown; //a timer so Loki doesnt fire too much in little time
	Timer transformTime;

	void UpdateSprite();
	void UpdateVerticalState();
	void UpdatesStateOnTheFall();
	void Act();
	bool IndividualMovStateSelection();

	void SetAppearance(TransformState appearance);
	void Shoot();

	float TIMES_FLAPS_WINGS;
	//constants
	const float FIREBALL_SPEED = 400;
	const float FIREBALL_DISTANCE = 1000;
    const float COOLDOWN = 1;
    const float TRANSFORM_COOLDOWN = 0.5;
};

#endif /* LOKI_H_ */
