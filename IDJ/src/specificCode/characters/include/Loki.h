/*
 * Loki.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#ifndef LOKI_H_
#define LOKI_H_

#include "Character.h"

class Loki : public Character
{
  public:
	Loki(float x, float y);
	~Loki();

	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void NotifyCollision(GameObject& other);
	static Loki *characterLoki;

  private:
	void Input();
	void Move(float dt);
};

#endif /* LOKI_H_ */
