/*
 * Thor.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#ifndef THOR_H_
#define THOR_H_

#include "../../../engine/include/InputManager.h"
#include "../../../engine/include/GameObject.h"
#include "../../../engine/include/Sprite.h"
#include "../../../engine/include/Camera.h"

class Thor : public GameObject
{
  public:
	Thor(float x, float y);
	~Thor();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject& other);
	bool IsDead();
	bool Is(std::string type);
	static Thor *characterThor;

  private:
	int hp;
	Sprite tempThor;

	int horizontal;
	int vertical;

	const float vel = 200;

	void Input();
	void Move(float dt);
};

#endif /* THOR_H_ */
