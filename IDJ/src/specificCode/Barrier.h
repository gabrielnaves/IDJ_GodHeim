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

#include "../engine/include/GameObject.h"
#include "characters/include/Thor.h"
#include "characters/include/Loki.h"

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

	static Barrier* barrier;

	void SetCorner();
  private:
	Point FindCenter();

	const float DIAMETER = 500;
};

#endif /* BARRIER_H_ */
