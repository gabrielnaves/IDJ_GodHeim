/*
 * Level1State.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#ifndef LEVEL1STATE_H_
#define LEVEL1STATE_H_

#include "../../../engine/include/Collision.h"
#include "../../../engine/include/Camera.h"
#include "../../../engine/include/State.h"
#include "../../../engine/include/Sprite.h"
#include "../../../engine/include/BlockTileSet.h"
#include "../../../engine/include/TileMap.h"
#include "../../../engine/include/MovementMap.h"
#include "../../characters/include/Barrier.h"
#include "../../objects/include/BrokenHouse.h"
#include "../../objects/include/Stairs.h"

class Level1State: public State
{
  public:
    Level1State();
    ~Level1State();

    void Update(float dt);
    void Render();

  private:
    void Input();
    void ChecksForCollisions();
    void ErasesDeadObjects();

    Sprite bg, rochas;
    BrokenHouse brokenHouse;
    BlockTileSet tileSet;
    TileMap tileMap;
};

#endif /* LEVEL1STATE_H_ */
