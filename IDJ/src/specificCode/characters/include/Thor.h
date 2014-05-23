/*
 * Thor.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#ifndef THOR_H_
#define THOR_H_

#include "Character.h"

class Thor : public Character
{
  public:
	Thor(float x, float y, MovementMap movementMap);
	~Thor();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	static Thor *characterThor;

  private:
	MovementMap movementMap;
	void Input();
	void Move(float dt);
};

#endif /* THOR_H_ */
