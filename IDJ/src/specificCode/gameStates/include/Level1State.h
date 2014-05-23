/*
 * Level1State.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#ifndef LEVEL1STATE_H_
#define LEVEL1STATE_H_

#include "../../../engine/include/Camera.h"
#include "../../../engine/include/State.h"
#include "../../../engine/include/Sprite.h"
#include "../../characters/include/Loki.h"
#include "../../characters/include/Thor.h"
#include "../../../engine/include/BlockTileSet.h"
#include "../../../engine/include/TileMap.h"
#include "../../../engine/include/MovementMap.h"

class Level1State: public State
{
  public:
	Level1State();
	~Level1State();

	void Update(float dt);
	void Render();

  private:
	void Input();

	Sprite bg, tempBlackBackground;
	BlockTileSet tileSet;
	TileMap tileMap;
};

#endif /* LEVEL1STATE_H_ */
