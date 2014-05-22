/*
 * Loki.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#ifndef LOKI_H_
#define LOKI_H_

#include "../../../engine/include/InputManager.h"
#include "../../../engine/include/GameObject.h"
#include "../../../engine/include/Sprite.h"
#include "../../../engine/include/Camera.h"
#include "../../Barrier.h"
#include <cmath>

class Loki : public GameObject
{
  public:
	Loki(float x, float y);
	~Loki();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject& other);
	bool IsDead();
	bool Is(std::string type);
	static Loki *characterLoki;

  private:
	int hp;
	Sprite tempLoki;

	int horizontal;
	int vertical;

	const float vel = 200;

	void Input();
	void Move(float dt);
};

#endif /* LOKI_H_ */
