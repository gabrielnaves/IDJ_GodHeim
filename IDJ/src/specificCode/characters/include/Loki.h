/*
 * Loki.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#ifndef LOKI_H_
#define LOKI_H_

#include "Character.h"
#include "Barrier.h"
#include "Bullet.h"
#include "../../objects/include/Stairs.h"
#include "../../../engine/include/Timer.h"

class Loki : public Character
{
  public:
	Loki(float x, float y, MovementMap& movMap);
	~Loki();

	void Update(float dt);
	bool Is(std::string type);
	void NotifyCollision(GameObject& other);
    void ReleasesStairs();
    void HoldStairs();
	static Loki *characterLoki;

  private:
	enum TransformState {LOKI, EAGLE};
	TransformState appearance;
    int flappedWings;
	Timer shootCooldown; //a timer so Loki doesnt fire too much in little time

	void Input();
	void Move(float dt);
	void UpdateSprite(float dt);
	void UpdateVerticalState();
	void UpdatesStateOnTheFall();
	void Act();

	void UpdateEagleSpeed(float dt);
	void Shoot();

	float TIMES_FLAPS_WINGS;
	//constants
	const float FIREBALL_SPEED = 400;
	const float FIREBALL_DISTANCE = 1000;
    const float MAX_FALLING_SPEED_EAGLE = 100;
    const float EAGLE_JUMP_SPEED = -300;
    const float EAGLE_AIR_RESISTANCE = 200;
    const float COOLDOWN = 1;
};

#endif /* LOKI_H_ */
