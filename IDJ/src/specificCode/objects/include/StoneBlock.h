/*
 * StoneBlock.h
 *
 *  Created on: Jul 6, 2014
 *      Author: icaro
 */

#ifndef STONEBLOCK_H_
#define STONEBLOCK_H_

#include <cmath>
#include "../../../Engine.h"
#include "../../characters/include/Loki.h"
#include "../../characters/include/Thor.h"
#include "../../items/include/ItemFlags.h"

class StoneBlock : public GameObject
{
  public:
	StoneBlock(std::string sprite,float x, float y);
	void Update(float dt);
    void Render();
    void NotifyCollision(GameObject& other);

    bool Is(std::string type);
  private:
    void CharactersStandOnBlock(Character *character);
    void Push();
    bool ShouldStand(Character *character);
    bool ShouldCollideLeftWall(Character *character, Rect prevChar);
    bool ShouldCollideRightWall(Character *character, Rect prevChar);
    void Stand(Character *character);
    void Blocks(Character *character);
    bool CloseTo(Rect character);
    Sprite sp;
    Rect prevLoki, prevThor;
};

#endif /* STONEBLOCK_H_ */
