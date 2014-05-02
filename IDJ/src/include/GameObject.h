/*
 * GameObject.h
 *
 *  Created on: Mar 28, 2014
 *      Author: Gabriel Naves
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Rect.h"

/**
 * Base class for all objects in the game.
 */
class GameObject
{
  public:
	virtual ~GameObject() {}
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	Rect box;
	float rotation;
};

#endif /* GAMEOBJECT_H_ */
