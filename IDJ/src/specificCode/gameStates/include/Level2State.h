/*
 * Level2State.h
 *
 *  Created on: Jun 17, 2014
 *      Author: Gabriel Naves
 */

#ifndef LEVEL2STATE_H_
#define LEVEL2STATE_H_

#include "../../../Engine.h"
#include "../../characters/include/Barrier.h"
#include "../../objects/include/LavaCircle.h"
#include "../../objects/include/Lava.h"
#include "../../objects/include/Meteor.h"
#include "StateData.h"
#include "EndState.h"

class Level2State : public State
{
  public:
    Level2State();
    ~Level2State();

    void Update(float dt);
    void Render();

  private:
    void Input();
    void ChecksForCollisions();
    void ErasesDeadObjects();
    void EmplaceInitialObjects();
    void Follow(std::string object);
    void SelectMusic();
    void EndGame(float dt);
    void NextLevel();
    bool StageClear();

    GameObject* lavaCircle;
    Sprite bg1, bg2, tmpBlackBg;
    BlockTileSet tileSet;
    TileMap tileMap;
    MovementMap movementMap;
    Music *music;
    Timer endGame;
};

#endif /* LEVEL2STATE_H_ */
