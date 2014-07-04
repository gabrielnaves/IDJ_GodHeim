/*
 * GameObject.h
 *
 *  Created on: Mar 28, 2014
 *      Author: Gabriel Naves
 *
 *	Description: Sets all the characteristics of an object
 *
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Rect.h"
#include <string>

class GameObject
{
  public:
	virtual ~GameObject() {}
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void NotifyCollision(GameObject& other) {};
	virtual bool IsDead() {return(false);}
	virtual bool Is(std::string type) = 0;
	virtual void Activate() {}
	Rect box;
	float rotation;
};

#endif /* GAMEOBJECT_H_ */
