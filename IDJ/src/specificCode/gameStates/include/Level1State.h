/*
 * Level1State.h
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 *              Icaro Mota
 */

#ifndef LEVEL1STATE_H_
#define LEVEL1STATE_H_

#include "../../../Engine.h"
#include "Level2State.h"
#include "../../characters/include/Barrier.h"
#include "../../objects/include/BrokenHouseFront.h"
#include "../../objects/include/BrokenHouseBack.h"
#include "../../objects/include/Stairs.h"
#include "../../objects/include/Rope.h"
#include "../../objects/include/Switch.h"
#include "../../objects/include/Bridge.h"
#include "../../objects/include/Spikes.h"
#include "../../objects/include/Plants.h"
#include "../../objects/include/PlantBarrier.h"
#include "../../objects/include/Rock.h"
#include "../../characters/include/Goat.h"
#include "../../characters/include/Wolf.h"
#include "../../characters/include/HpBar.h"
#include "StateData.h"
#include "EndState.h"

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
    void UpdateMusic(float dt);
    void CheckMusic(float lowerX, float upperX, float lowerY, float upperY);
    void SelectMusic();
    void EndGame(float dt);

    Sprite bg, rochas;
    BlockTileSet tileSet;
    TileMap tileMap;
    MovementMap movementMap;
    Music *outsideMusic, *caveMusic;
    Timer endGame;

    bool musicPlaying;
};

#endif /* LEVEL1STATE_H_ */
