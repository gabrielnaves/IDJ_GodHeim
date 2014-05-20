/*
 * Thor.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#ifndef THOR_H_
#define THOR_H_

#include "../../engine/include/GameObject.h"

class Thor : public GameObject
{
  public:
	Thor();
	~Thor();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject& other);
	bool IsDead();
	bool Is(std::string type);

  private:
	int hp;
};

#endif /* THOR_H_ */
