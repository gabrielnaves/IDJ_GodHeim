/*
 * Loki.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#ifndef LOKI_H_
#define LOKI_H_

#include "../../engine/include/GameObject.h"
#include "../../engine/include/Sprite.h"


class Loki : public GameObject
{
  public:
	Loki();
	~Loki();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject& other);
	bool IsDead();
	bool Is(std::string type);

  private:
	int hp;
};

#endif /* LOKI_H_ */
