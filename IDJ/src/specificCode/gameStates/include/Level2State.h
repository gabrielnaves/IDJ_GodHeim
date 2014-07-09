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
#include "../../characters/include/ChainedDragon.h"
#include "../../characters/include/Skeleton.h"
#include "../../objects/include/FloatingBlock.h"
#include "../../objects/include/LavaCircle.h"
#include "../../objects/include/Lava.h"
#include "../../objects/include/Meteor.h"
#include "../../objects/include/Portal.h"
#include "StateData.h"
#include "EndState.h"
#include "Credits.h"

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
    void CorrectStaticPointers();
    void NextLevel();
    bool StageClear();

    GameObject* lavaCircle;
    Sprite bg1, bg2, tmpBlackBg;
    BlockTileSet tileSet;
    TileMap tileMap;
    MovementMap movementMap;
    Music music;
    Timer endGame;
    bool changedMusic, end;
};

#endif /* LEVEL2STATE_H_ */
