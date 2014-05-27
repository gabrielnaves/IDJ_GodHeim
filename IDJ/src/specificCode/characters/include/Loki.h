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
#include "../../../engine/include/Timer.h"

class Loki : public Character
{
  public:
	Loki(float x, float y, MovementMap movMap);
	~Loki();

	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void NotifyCollision(GameObject& other);
	static Loki *characterLoki;

  private:
	enum TransformState {LOKI, EAGLE};
	TransformState appearance;
	void Input();
	void Move(float dt);
	void UpdateSprite();
	void UpdateEagleSpeed(float dt);
	void UpdateVerticalState();

    const float MAX_FALLING_SPEED_EAGLE = 100;
    const float EAGLE_JUMP_SPEED = -250;
    const float EAGLE_AIR_RESISTANCE = 200;

    int flappedWings;
};

#endif /* LOKI_H_ */
