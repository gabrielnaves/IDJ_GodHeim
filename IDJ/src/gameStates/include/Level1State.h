/*
 * Level1State.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#ifndef LEVEL1STATE_H_
#define LEVEL1STATE_H_

#include "../../engine/include/State.h"
#include "../../engine/include/Sprite.h"
#include "../../characters/include/Loki.h"

class Level1State: public State
{
  public:
	Level1State();
	~Level1State();

	void Update(float dt);
	void Render();

  private:
	void Input();

	Sprite bg;
};

#endif /* LEVEL1STATE_H_ */
