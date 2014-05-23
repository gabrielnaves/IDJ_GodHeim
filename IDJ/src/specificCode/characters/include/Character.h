/*
 * Character.h
 *
 *  Created on: May 23, 2014
 *      Author: icaro
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "../../../engine/include/InputManager.h"
#include "../../../engine/include/GameObject.h"
#include "../../../engine/include/Sprite.h"
#include "../../../engine/include/Camera.h"
#include <cmath>

class Character : public GameObject
{
  public:
	virtual ~Character() {}
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool Is(std::string type) = 0;

	virtual void NotifyCollision(GameObject& other) = 0;
	bool IsDead();

  protected:
	enum State {STANDING, WALKING, JUMPING};
	int hp;
	Sprite tempCharacterSp;

	State state;
	int horizontal;
	int vertical;

	const float vel = 200;

	void Input();
	virtual void Move(float dt) = 0;
	void Walk(float dt);
	void Jump(float dt);
	bool HasReachedBarrier(float dx, float dy);
};

#endif /* CHARACTER_H_ */
