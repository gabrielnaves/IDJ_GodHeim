/*
 * Meteor.h
 *
 *  Created on: Jul 7, 2014
 *      Author: icaro
 */

#ifndef METEOR_H_
#define METEOR_H_

#include "../../../Engine.h"
#include "../../characters/include/Thor.h"
#include "../../characters/include/Loki.h"

namespace MeteorNamespace
{
	const float FALLING_SPEED = 10;
	enum State {FALLING, MELTING};
}

class Meteor : public GameObject
{
  public:
	Meteor(float x, float y, float X, float Y);
	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject& other);
	bool IsDead();
	bool Is(std::string type);
  private:
	void SetState(MeteorNamespace::State newState);
	Sprite sp;
	MeteorNamespace::State state, prevState;
	Timer explosion;
	bool dead;
};

#endif /* METEOR_H_ */
