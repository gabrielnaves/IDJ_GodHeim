/*
 * Level2State.h
 *
 *  Created on: Jun 17, 2014
 *      Author: Gabriel Naves
 */

#ifndef LEVEL2STATE_H_
#define LEVEL2STATE_H_

#include "../../../Engine.h"
#include "../../objects/include/LavaCircle.h"
#include "../../objects/include/Lava.h"

class Level2State : public State
{
  public:
    Level2State();
    ~Level2State();

    void Update(float dt);
    void Render();

  private:
    void Input();
    void EmplaceInitialObjects();

    GameObject* lavaCircle;
    Sprite bg1, bg2, tmpBlackBg;
    BlockTileSet tileSet;
    TileMap tileMap;
    MovementMap movementMap;
};

#endif /* LEVEL2STATE_H_ */
