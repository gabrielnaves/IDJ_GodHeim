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
#include "../../../engine/include/Music.h"
#include "../../../engine/include/Sound.h"
#include "../../../engine/include/BlockTileSet.h"
#include "../../../engine/include/TileMap.h"
#include "../../../engine/include/MovementMap.h"
#include "../../characters/include/Barrier.h"
#include "../../objects/include/BrokenHouse.h"
#include "../../objects/include/Stairs.h"
#include "../../objects/include/Bridge.h"
#include "../../objects/include/Spikes.h"
#include "../../characters/include/Goat.h"

class Level1State : public State
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
    void EmplaceInitialObjects();
    void Follow(std::string object);

    Sprite bg, rochas;
    BlockTileSet tileSet;
    TileMap tileMap;
    MovementMap movementMap;
    BrokenHouse brokenHouse;
    Music outsideMusic, caveMusic;
};

#endif /* LEVEL1STATE_H_ */
