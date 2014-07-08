/*
 * FloatingBlock.h
 *
 *  Created on: Jul 7, 2014
 *      Author: arthur
 */

#ifndef FLOATINGBLOCK_H_
#define FLOATINGBLOCK_H_

#include "../../../Engine.h"
#include "../../characters/include/Loki.h"
#include "../../characters/include/Thor.h"

enum FloatingBlockState{ FORWARD, BACKWARD, FWDSTOP, BACKSTOP };

class FloatingBlock: public GameObject
{
  public:
	FloatingBlock(std::string sprite, int x, int y, FloatingBlockState state,
	              float angle, float vel = 100, float distance = 300, float wait = 4);
	void Update(float dt);
	void Move(float dt);
	void UpdateState();
	void Render();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool IsDead();
	bool IsOnTop(GameObject* character);
  private:
	Rect prevThorPos, prevLokiPos, prevBlockPos;
	Sprite block;
	FloatingBlockState state;
	Timer timer;
	float alreadyMoved, movAngle;
	bool thorStanding, lokiStanding;

	float VEL, DISTANCE, WAITTIME;
};



#endif /* FLOATINGBLOCK_H_ */
