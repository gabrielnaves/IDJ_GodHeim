/*
 * Barrier.h
 *
 *  Created on: May 22, 2014
 *      Author: icaro
 *
 * Description: An object that keeps Thor and Loki from spliting up too much.
 *
 */

#ifndef BARRIER_H_
#define BARRIER_H_

#include "../../../engine/include/GameObject.h"
#include "Thor.h"
#include "Loki.h"

class Barrier : public GameObject
{
  public:
	Barrier();
	virtual ~Barrier();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject& other);
	bool IsDead();
	bool Is(std::string type);
	bool CollidesWith(Character *character);

	static Barrier* barrier;

	Point GetCorner();
	const float DIAMETER = 500;
  private:
	Point FindCenter();
};

#endif /* BARRIER_H_ */
